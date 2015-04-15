// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "NOTC/etherform.h"

#include "math/mMath.h"
#include "core/stream/bitStream.h"
#include "T3D/fx/cameraFXMgr.h"
#include "T3D/gameBase/gameConnection.h"
#include "math/mathIO.h"
#include "gui/worldEditor/editor.h"
#include "console/engineAPI.h"
#include "console/consoleTypes.h"
#include "console/engineAPI.h"
#include "math/mathUtils.h"
#include "math/mTransform.h"
#include "collision/extrudedPolyList.h"
#include "collision/clippedPolyList.h"
#include "collision/earlyOutPolyList.h"
#include "T3D/trigger.h"
#include "T3D/physicalZone.h"
#include "T3D/fx/particleEmitter.h"
#include "T3D/item.h"
#include "ts/tsShapeInstance.h"
#include "NOTC/tacticalzone.h"
#include "NOTC/fx/multiNodeLaserBeam.h"

#define MaxPitch 1.3962
#define EtherformRadius    0.05;

// Movement constants
static U32 sMoveRetryCount = 5;
static F32 sNormalElasticity = 0.01f;
static F32 sTractionDistance = 0.03f;

// Client prediction
static F32 sMinWarpTicks = 0.5f;        // Fraction of tick at which instant warp occures
static S32 sMaxWarpTicks = 3;          // Max warp duration in ticks
static S32 sMaxPredictionTicks = 30;   // Number of ticks to predict

//
static U32 sCollisionMoveMask =  TerrainObjectType       |
                                 WaterObjectType         | 
                                 PlayerObjectType        |
                                 StaticShapeObjectType   | 
                                 VehicleObjectType       |
                                 PhysicalZoneObjectType;

static U32 sServerCollisionContactMask = sCollisionMoveMask      |
                                         ItemObjectType          |
                                         TriggerObjectType       |
                                         TacticalZoneObjectType  |
                                         CorpseObjectType;

static U32 sClientCollisionContactMask = sCollisionMoveMask      |
                                         TriggerObjectType;

//----------------------------------------------------------------------------

IMPLEMENT_CO_DATABLOCK_V1(EtherformData);

EtherformData::EtherformData()
{
	boxSize.set(1.0f, 1.0f, 1.0f);

	accelerationForce = 200;

	dMemset( laserTrailList, 0, sizeof( laserTrailList ) );
	dMemset( laserTrailIdList, 0, sizeof( laserTrailIdList ) );

   for (S32 j = 0; j < MaxJetEmitters; j++)
      jetEmitter[j] = 0;
   minTrailSpeed = 1;
}

bool EtherformData::onAdd()
{
   if(!Parent::onAdd())
      return false;

   return true;
}

bool EtherformData::preload(bool server, String &errorStr)
{
   if (!Parent::preload(server, errorStr))
      return false;

   // Resolve objects transmitted from server.
   if(!server)
	{
		for( S32 i=0; i<NUM_ETHERFORM_LASERTRAILS; i++ )
		{
			if( !laserTrailList[i] && laserTrailIdList[i] != 0 )
			{
				if( Sim::findObject( laserTrailIdList[i], laserTrailList[i] ) == false)
				{
					Con::errorf( ConsoleLogEntry::General, "EtherformData::onAdd: Invalid packet, bad datablockId(laserTrails): 0x%x", laserTrailIdList[i] );
				}
			}
		}

		for (S32 j = 0; j < MaxJetEmitters; j++)
		{
			U32 id = (U32)jetEmitter[j];
			if(id)
				if(Sim::findObject(id,jetEmitter[j]) == false)
					Con::errorf( ConsoleLogEntry::General, "EtherformData::onAdd: Invalid packet, bad datablockId(particleTrail): 0x%x", id );
		}
   }

   return true;
}

void EtherformData::packData(BitStream* stream)
{
   Parent::packData(stream);

   stream->write(boxSize.x);
   stream->write(boxSize.y);
   stream->write(boxSize.z);

   stream->write(accelerationForce);

   for( S32 i=0; i<NUM_ETHERFORM_LASERTRAILS; i++ )
   {
      if( stream->writeFlag( laserTrailList[i] != NULL ) )
      {
         stream->writeRangedU32( laserTrailList[i]->getId(), DataBlockObjectIdFirst,  DataBlockObjectIdLast );
      }
   }

   for (S32 j = 0; j < MaxJetEmitters; j++)
   {
      if (stream->writeFlag(jetEmitter[j]))
      {
         SimObjectId writtenId = packed ? SimObjectId(jetEmitter[j]) : jetEmitter[j]->getId();
         stream->writeRangedU32(writtenId, DataBlockObjectIdFirst,DataBlockObjectIdLast);
      }
   }
   stream->write(minTrailSpeed);
}

void EtherformData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);

   stream->read(&boxSize.x);
   stream->read(&boxSize.y);
   stream->read(&boxSize.z);

   stream->read(&accelerationForce);

   for( S32 i=0; i<NUM_ETHERFORM_LASERTRAILS; i++ )
   {
      if( stream->readFlag() )
      {
         laserTrailIdList[i] = stream->readRangedU32( DataBlockObjectIdFirst, DataBlockObjectIdLast );
      }
   }

   for (S32 j = 0; j < MaxJetEmitters; j++) {
      jetEmitter[j] = NULL;
      if (stream->readFlag())
         jetEmitter[j] = (ParticleEmitterData*)stream->readRangedU32(DataBlockObjectIdFirst,
                                                                     DataBlockObjectIdLast);
   }
   stream->read(&minTrailSpeed);
}

void EtherformData::initPersistFields()
{
	Parent::initPersistFields();

	addField("boundingBox", TypePoint3F, Offset(boxSize, EtherformData));
	addField("accelerationForce", TypeF32, Offset(accelerationForce, EtherformData));
	addField("laserTrail", TYPEID<MultiNodeLaserBeamData>(), Offset(laserTrailList, EtherformData), NUM_ETHERFORM_LASERTRAILS );
   addField("particleTrail", TYPEID<ParticleEmitterData>(), Offset(jetEmitter[TrailEmitter], EtherformData));
   addField("minTrailSpeed", TypeF32, Offset(minTrailSpeed, EtherformData));
}

//-----------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(Etherform);

Etherform::Etherform()
{
	//mTypeMask |= EtherformObjectType;
	delta.pos.set(0.0f,0.0f,0.0f);
	delta.rot.set(0.0f,0.0f,0.0f);
	delta.rotOffset.set(0.0f,0.0f,0.0f);
	delta.warpOffset.set(0.0f,0.0f,0.0f);
	delta.posVec.set(0.0f,0.0f,0.0f);
	delta.rotVec.set(0.0f,0.0f,0.0f);
	delta.warpTicks = 0;
	delta.dt = 1.0f;
	delta.move = NullMove;
	mPredictionCount = sMaxPredictionTicks;

	mRot.set(0, 0, 0);
	mVelocity.set(0.0f, 0.0f, 0.0f);

	dMemset( mLaserTrailList, 0, sizeof( mLaserTrailList ) );

   for (S32 j = 0; j < EtherformData::MaxJetEmitters; j++)
      mJetEmitter[j] = 0;

	mConvex.init(this);
	mWorkingQueryBox.minExtents.set(-1e9f, -1e9f, -1e9f);
	mWorkingQueryBox.maxExtents.set(-1e9f, -1e9f, -1e9f);
}

Etherform::~Etherform()
{
}

//----------------------------------------------------------------------------

bool Etherform::onAdd()
{
	if(!Parent::onAdd())
		return false;

	if(isClientObject())
	{
		mCameraTargetPos = this->getPosition();
		mCameraPos = mCameraTargetPos;
	}

	addToScene();
	scriptOnAdd();

	return true;
}

void Etherform::onRemove()
{
	for( S32 i = 0; i < NUM_ETHERFORM_LASERTRAILS; i++ )
	{
		if(mLaserTrailList[i])
		{
			mLaserTrailList[i]->deleteOnFadeout();
			mLaserTrailList[i] = NULL;
		}
	}

	scriptOnRemove();
	removeFromScene();

	Parent::onRemove();
}

void Etherform::onDeleteNotify(SimObject *obj)
{
   Parent::onDeleteNotify(obj);
}

void Etherform::onScaleChanged()
{
   const Point3F& scale = getScale();
   mScaledBox = mObjBox;
   mScaledBox.minExtents.convolve( scale );
   mScaledBox.maxExtents.convolve( scale );
}

//----------------------------------------------------------------------------

void Etherform::processTick(const Move* move)
{
   Parent::processTick(move);

   // Warp to catch up to server?
   if(delta.warpTicks > 0)
   {
		delta.warpTicks--;

		// Set new pos.
		getTransform().getColumn(3,&delta.pos);
		delta.pos += delta.warpOffset;
		delta.rot += delta.rotOffset;
		this->setPosition(delta.pos,delta.rot);
		this->setRenderPosition(delta.pos,delta.rot);

		// Backstepping
		delta.posVec.x = -delta.warpOffset.x;
		delta.posVec.y = -delta.warpOffset.y;
		delta.posVec.z = -delta.warpOffset.z;
		delta.rotVec.x = -delta.rotOffset.x;
		delta.rotVec.y = -delta.rotOffset.y;
		delta.rotVec.z = -delta.rotOffset.z;
	}
	else
	{
		// If there is no move, the we're either an
		// unattached etherform on the server, or another etherform's
		// client ghost.
		if(!move)
		{
			if(isGhost())
			{
				// If we haven't run out of prediction time,
				// predict using the last known move.
				if (mPredictionCount-- <= 0)
					return;

				move = &delta.move;
			}
			else
				move = &NullMove;
		}

		if(isServerObject() || (didRenderLastRender() || getControllingClient()))
		{
			delta.move = *move;

         if(isMounted())
         {
            // If we're mounted then do not perform any collision checks
            // and clear our previous working list.
            mConvex.clearWorkingList();
         }
         else
         {
            this->updateWorkingCollisionSet();
         }

			this->updateVelocity(move);
         VectorF contactNormal(0,0,0);
         this->findContact(&contactNormal );
			this->updatePos();
		}
	}

	// Add node to lasertrails.
	if(this->isClientObject())
	{
		GameConnection* conn = GameConnection::getConnectionToServer();
		if(conn && this == conn->getControlObject())
		{
			if(move->sendCount == 0)
				this->addLaserTrailNode(this->getPosition());
		}
		else
			this->addLaserTrailNode(this->getPosition());
	}
}


void Etherform::interpolateTick(F32 dt)
{
	Parent::interpolateTick(dt);

	if(dt != 0.0f)
	{
		Point3F pos = delta.pos + delta.posVec * dt;
		Point3F rot = delta.rot + delta.rotVec * dt;

		this->setRenderPosition(pos, rot, dt);

		// update laser trails...
		for( S32 i=0; i < NUM_ETHERFORM_LASERTRAILS; i++ )
		{
			if(mLaserTrailList[i])
				mLaserTrailList[i]->setLastNodePos(pos);
		}

		// apply camera effects - is this the best place? - bramage
		GameConnection* connection = GameConnection::getConnectionToServer();
		if(connection->isFirstPerson())
		{
			GameBase* obj = connection->getControlObject();
			if( obj == this )
			{
				MatrixF curTrans = this->getRenderTransform();
				curTrans.mul( gCamFXMgr.getTrans() );
				Parent::setRenderTransform( curTrans );
			}
		}
	}
	else
	{
		this->setRenderPosition(delta.pos, delta.rot, 0);
	}

	// Save last interpolation delta value.
	delta.dt = dt;
}

void Etherform::advanceTime(F32 delta)
{
	Parent::advanceTime(delta);

	this->updateTrailEmitter(delta);

	this->updateCameraPos(delta);
}

bool Etherform::onNewDataBlock(GameBaseData* dptr, bool reload)
{
	mDataBlock = dynamic_cast<EtherformData*>(dptr);
	if (!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
		return false;

	// set up bounding box...
	mObjBox.maxExtents.x = mDataBlock->boxSize.x * 0.5f;
	mObjBox.maxExtents.y = mDataBlock->boxSize.y * 0.5f;
	mObjBox.maxExtents.z = mDataBlock->boxSize.z * 0.5f;
	mObjBox.minExtents.x = -mObjBox.maxExtents.x;
	mObjBox.minExtents.y = -mObjBox.maxExtents.y;
	mObjBox.minExtents.z = -mObjBox.maxExtents.z;
	this->resetWorldBox();

	// Setup the box for our convex object...
	mObjBox.getCenter(&mConvex.mCenter);
	mConvex.mSize.x = mObjBox.len_x() / 2.0f;
	mConvex.mSize.y = mObjBox.len_y() / 2.0f;
	mConvex.mSize.z = mObjBox.len_z() / 2.0f;

	// Initialize our scaled attributes as well
	this->onScaleChanged();

	this->scriptOnNewDataBlock();

	return true;
}

//----------------------------------------------------------------------------

void Etherform::setPosition(const Point3F& pos,const Point3F& rot)
{
   MatrixF xRot, zRot;
   xRot.set(EulerF(rot.x, 0, 0));
   zRot.set(EulerF(0, 0, rot.z));
   MatrixF temp;
   temp.mul(zRot, xRot);
   temp.setColumn(3, pos);
   Parent::setTransform(temp);
   mRot = rot;
}

void Etherform::setRenderPosition(const Point3F& pos, const Point3F& rot, F32 dt)
{
   MatrixF xRot, zRot;
   xRot.set(EulerF(rot.x, 0, 0));
   zRot.set(EulerF(0, 0, rot.z));
   MatrixF temp;
   temp.mul(zRot, xRot);
   temp.setColumn(3, pos);
   Parent::setRenderTransform(temp);
}

//----------------------------------------------------------------------------

Point3F Etherform::_move( const F32 travelTime, Collision *outCol )
{
   // Try and move to new pos
   F32 totalMotion  = 0.0f;
   
   // TODO: not used?
   //F32 initialSpeed = mVelocity.len();

   Point3F start;
   Point3F initialPosition;
   getTransform().getColumn(3,&start);
   initialPosition = start;

   static CollisionList collisionList;
   static CollisionList physZoneCollisionList;

   collisionList.clear();
   physZoneCollisionList.clear();

   MatrixF collisionMatrix(true);
   collisionMatrix.setColumn(3, start);

   VectorF firstNormal(0.0f, 0.0f, 0.0f);
   F32 time = travelTime;
   U32 count = 0;

   static Polyhedron sBoxPolyhedron;
   static ExtrudedPolyList sExtrudedPolyList;
   static ExtrudedPolyList sPhysZonePolyList;

   for (; count < sMoveRetryCount; count++) {
      F32 speed = mVelocity.len();
      if(!speed)
         break;

      Point3F end = start + mVelocity * time;
      Point3F distance = end - start;

      if (mFabs(distance.x) < mObjBox.len_x() &&
          mFabs(distance.y) < mObjBox.len_y() &&
          mFabs(distance.z) < mObjBox.len_z())
      {
         // We can potentially early out of this.  If there are no polys in the clipped polylist at our
         //  end position, then we can bail, and just set start = end;
         Box3F wBox = mScaledBox;
         wBox.minExtents += end;
         wBox.maxExtents += end;

         static EarlyOutPolyList eaPolyList;
         eaPolyList.clear();
         eaPolyList.mNormal.set(0.0f, 0.0f, 0.0f);
         eaPolyList.mPlaneList.clear();
         eaPolyList.mPlaneList.setSize(6);
         eaPolyList.mPlaneList[0].set(wBox.minExtents,VectorF(-1.0f, 0.0f, 0.0f));
         eaPolyList.mPlaneList[1].set(wBox.maxExtents,VectorF(0.0f, 1.0f, 0.0f));
         eaPolyList.mPlaneList[2].set(wBox.maxExtents,VectorF(1.0f, 0.0f, 0.0f));
         eaPolyList.mPlaneList[3].set(wBox.minExtents,VectorF(0.0f, -1.0f, 0.0f));
         eaPolyList.mPlaneList[4].set(wBox.minExtents,VectorF(0.0f, 0.0f, -1.0f));
         eaPolyList.mPlaneList[5].set(wBox.maxExtents,VectorF(0.0f, 0.0f, 1.0f));

         // Build list from convex states here...
         CollisionWorkingList& rList = mConvex.getWorkingList();
         CollisionWorkingList* pList = rList.wLink.mNext;
         while (pList != &rList) {
            Convex* pConvex = pList->mConvex;
            if (pConvex->getObject()->getTypeMask() & sCollisionMoveMask) {
               Box3F convexBox = pConvex->getBoundingBox();
               if (wBox.isOverlapped(convexBox))
               {
                  // No need to separate out the physical zones here, we want those
                  //  to cause a fallthrough as well...
                  pConvex->getPolyList(&eaPolyList);
               }
            }
            pList = pList->wLink.mNext;
         }

         if (eaPolyList.isEmpty())
         {
            totalMotion += (end - start).len();
            start = end;
            break;
         }
      }

      collisionMatrix.setColumn(3, start);
      sBoxPolyhedron.buildBox(collisionMatrix, mScaledBox, true);

      // Setup the bounding box for the extrudedPolyList
      Box3F plistBox = mScaledBox;
      collisionMatrix.mul(plistBox);
      Point3F oldMin = plistBox.minExtents;
      Point3F oldMax = plistBox.maxExtents;
      plistBox.minExtents.setMin(oldMin + (mVelocity * time) - Point3F(0.1f, 0.1f, 0.1f));
      plistBox.maxExtents.setMax(oldMax + (mVelocity * time) + Point3F(0.1f, 0.1f, 0.1f));

      // Build extruded polyList...
      VectorF vector = end - start;
      sExtrudedPolyList.extrude(sBoxPolyhedron,vector);
      sExtrudedPolyList.setVelocity(mVelocity);
      sExtrudedPolyList.setCollisionList(&collisionList);

      sPhysZonePolyList.extrude(sBoxPolyhedron,vector);
      sPhysZonePolyList.setVelocity(mVelocity);
      sPhysZonePolyList.setCollisionList(&physZoneCollisionList);

      // Build list from convex states here...
      CollisionWorkingList& rList = mConvex.getWorkingList();
      CollisionWorkingList* pList = rList.wLink.mNext;
      while (pList != &rList) {
         Convex* pConvex = pList->mConvex;
         if (pConvex->getObject()->getTypeMask() & sCollisionMoveMask) {
            Box3F convexBox = pConvex->getBoundingBox();
            if (plistBox.isOverlapped(convexBox))
            {
               if (pConvex->getObject()->getTypeMask() & PhysicalZoneObjectType)
                  pConvex->getPolyList(&sPhysZonePolyList);
               else
                  pConvex->getPolyList(&sExtrudedPolyList);
            }
         }
         pList = pList->wLink.mNext;
      }

      // Take into account any physical zones...
      for (U32 j = 0; j < physZoneCollisionList.getCount(); j++) 
      {
         AssertFatal(dynamic_cast<PhysicalZone*>(physZoneCollisionList[j].object), "Bad phys zone!");
         const PhysicalZone* pZone = (PhysicalZone*)physZoneCollisionList[j].object;
         if (pZone->isActive())
            mVelocity *= pZone->getVelocityMod();
      }

      if (collisionList.getCount() != 0 && collisionList.getTime() < 1.0f) 
      {
         // Set to collision point
         F32 velLen = mVelocity.len();

         F32 dt = time * getMin(collisionList.getTime(), 1.0f);
         start += mVelocity * dt;
         time -= dt;

         totalMotion += velLen * dt;

         // Back off...
         if ( velLen > 0.f ) {
            F32 newT = getMin(0.01f / velLen, dt);
            start -= mVelocity * newT;
            totalMotion -= velLen * newT;
         }

         // Pick the surface most parallel to the face that was hit.
         const Collision *collision = &collisionList[0];
         const Collision *cp = collision + 1;
         const Collision *ep = collision + collisionList.getCount();
         for (; cp != ep; cp++)
         {
            if (cp->faceDot > collision->faceDot)
               collision = cp;
         }

         F32 bd = -mDot(mVelocity, collision->normal);

         // Copy this collision out so
         // we can use it to do impacts
         // and query collision.
         *outCol = *collision;

         // Subtract out velocity
         VectorF dv = collision->normal * (bd + sNormalElasticity);
         mVelocity += dv;
         if (count == 0)
         {
            firstNormal = collision->normal;
         }
         else
         {
            if (count == 1)
            {
               // Re-orient velocity along the crease.
               if (mDot(dv,firstNormal) < 0.0f &&
                   mDot(collision->normal,firstNormal) < 0.0f)
               {
                  VectorF nv;
                  mCross(collision->normal,firstNormal,&nv);
                  F32 nvl = nv.len();
                  if (nvl)
                  {
                     if (mDot(nv,mVelocity) < 0.0f)
                        nvl = -nvl;
                     nv *= mVelocity.len() / nvl;
                     mVelocity = nv;
                  }
               }
            }
         }
      }
      else
      {
         totalMotion += (end - start).len();
         start = end;
         break;
      }
   }

   if (count == sMoveRetryCount)
   {
      // Failed to move
      start = initialPosition;
      mVelocity.set(0.0f, 0.0f, 0.0f);
   }

   return start;
}

void Etherform::_handleCollision( const Collision &collision )
{
   // Track collisions
   if(!isGhost() 
	&& collision.object 
	&& collision.object != mContactInfo.contactObject)
	{
		queueCollision( collision.object, mVelocity - collision.object->getVelocity());
	}
}

void Etherform::_findContact( SceneObject **contactObject, 
                           VectorF *contactNormal, 
                           Vector<SceneObject*> *outOverlapObjects )
{
   Point3F pos;
   getTransform().getColumn(3,&pos);

   Box3F wBox;
   Point3F exp(0,0,sTractionDistance);
   wBox.minExtents = pos + mScaledBox.minExtents - exp;
   wBox.maxExtents.x = pos.x + mScaledBox.maxExtents.x;
   wBox.maxExtents.y = pos.y + mScaledBox.maxExtents.y;
   wBox.maxExtents.z = pos.z + mScaledBox.minExtents.z + sTractionDistance;

   static ClippedPolyList polyList;
   polyList.clear();
   polyList.doConstruct();
   polyList.mNormal.set(0.0f, 0.0f, 0.0f);
   polyList.setInterestNormal(Point3F(0.0f, 0.0f, -1.0f));

   polyList.mPlaneList.setSize(6);
   polyList.mPlaneList[0].setYZ(wBox.minExtents, -1.0f);
   polyList.mPlaneList[1].setXZ(wBox.maxExtents, 1.0f);
   polyList.mPlaneList[2].setYZ(wBox.maxExtents, 1.0f);
   polyList.mPlaneList[3].setXZ(wBox.minExtents, -1.0f);
   polyList.mPlaneList[4].setXY(wBox.minExtents, -1.0f);
   polyList.mPlaneList[5].setXY(wBox.maxExtents, 1.0f);
   Box3F plistBox = wBox;

   // Expand build box as it will be used to collide with items.
   // PickupRadius will be at least the size of the box.
   F32 pd = 0;
   wBox.minExtents.x -= pd; wBox.minExtents.y -= pd;
   wBox.maxExtents.x += pd; wBox.maxExtents.y += pd;
   wBox.maxExtents.z = pos.z + mScaledBox.maxExtents.z;

   // Build list from convex states here...
   CollisionWorkingList& rList = mConvex.getWorkingList();
   CollisionWorkingList* pList = rList.wLink.mNext;
   while (pList != &rList)
   {
      Convex* pConvex = pList->mConvex;

      U32 objectMask = pConvex->getObject()->getTypeMask();
      
      if (  ( objectMask & sCollisionMoveMask ) &&
            !( objectMask & PhysicalZoneObjectType ) )
      {
         Box3F convexBox = pConvex->getBoundingBox();
         if (plistBox.isOverlapped(convexBox))
            pConvex->getPolyList(&polyList);
      }
      else
         outOverlapObjects->push_back( pConvex->getObject() );

      pList = pList->wLink.mNext;
   }

   if (!polyList.isEmpty())
   {
      // Pick flattest surface
      F32 bestVd = -1.0f;
      ClippedPolyList::Poly* poly = polyList.mPolyList.begin();
      ClippedPolyList::Poly* end = polyList.mPolyList.end();
      for (; poly != end; poly++)
      {
         F32 vd = poly->plane.z;       // i.e.  mDot(Point3F(0,0,1), poly->plane);
         if (vd > bestVd)
         {
            bestVd = vd;
            *contactObject = poly->object;
            *contactNormal = poly->plane;
         }
      }
   }
}

void Etherform::findContact(VectorF *contactNormal)
{
   SceneObject *contactObject = NULL;

   Vector<SceneObject*> overlapObjects;
   _findContact(&contactObject, contactNormal, &overlapObjects );

   // Check for triggers, corpses and items.
   const U32 filterMask = isGhost() ? sClientCollisionContactMask : sServerCollisionContactMask;
   for ( U32 i=0; i < overlapObjects.size(); i++ )
   {
      SceneObject *obj = overlapObjects[i];
      U32 objectMask = obj->getTypeMask();

      if ( !( objectMask & filterMask ) )
         continue;

      // Check: triggers, tactical zones, corpses and items...
      //
      if (objectMask & TriggerObjectType)
      {
         Trigger* pTrigger = static_cast<Trigger*>( obj );
         pTrigger->potentialEnterObject(this);
      }
      else if (objectMask & TacticalZoneObjectType)
      {
         TacticalZone* pZone = static_cast<TacticalZone*>( obj );
         pZone->potentialEnterObject(this);
      }
      else if (objectMask & CorpseObjectType)
      {
         // If we've overlapped the worldbounding boxes, then that's it...
         if ( getWorldBox().isOverlapped( obj->getWorldBox() ) )
         {
            ShapeBase* col = static_cast<ShapeBase*>( obj );
            queueCollision(col,getVelocity() - col->getVelocity());
         }
      }
      else if (objectMask & ItemObjectType)
      {
         // If we've overlapped the worldbounding boxes, then that's it...
         Item* item = static_cast<Item*>( obj );
         if (  getWorldBox().isOverlapped(item->getWorldBox()) &&
               item->getCollisionObject() != this && 
               !item->isHidden() )
            queueCollision(item,getVelocity() - item->getVelocity());
      }
   }

   mContactInfo.clear();
   mContactInfo.contacted = contactObject != NULL;
   mContactInfo.contactObject = contactObject;

   if(mContactInfo.contacted)
      mContactInfo.contactNormal = *contactNormal;
}

void Etherform::addLaserTrailNode(const Point3F& pos)
{
	if( isServerObject() )
		return;

	for(S32 i = 0; i < NUM_ETHERFORM_LASERTRAILS; i++)
	{
		if( mLaserTrailList[i] == NULL )
		{
			// set up laserTrail...
			if( mDataBlock->laserTrailList[i] )
			{
				mLaserTrailList[i] = new MultiNodeLaserBeam();
				mLaserTrailList[i]->setPalette(this->getPalette());
				mLaserTrailList[i]->onNewDataBlock(mDataBlock->laserTrailList[i], false);
				if( !mLaserTrailList[i]->registerObject() )
				{
					Con::warnf( ConsoleLogEntry::General, "Could not register laserTrail %d for class: %s",i, mDataBlock->getName() );
					delete mLaserTrailList[i];
					mLaserTrailList[i] = NULL;
				}
				else
				{
					mLaserTrailList[i]->addNodes(pos);
					mLaserTrailList[i]->setRender(true);
					mLaserTrailList[i]->fade();
				}
			}
		}
		else
		{
			mLaserTrailList[i]->addNodes(pos);
		}
	}
}

//----------------------------------------------------------------------------

void Etherform::updateTrailEmitter(F32 dt)
{
	if(mDamageState == Destroyed)
		return;

	if(!mDataBlock->jetEmitter[EtherformData::TrailEmitter])
		return;

	ParticleEmitter* emitter = mJetEmitter[EtherformData::TrailEmitter];

	// Particle trail emitter
   F32 speed = this->getVelocity().len();
	if(speed > mDataBlock->minTrailSpeed)
	{
		if(!bool(emitter))
		{
			emitter = new ParticleEmitter;
			emitter->onNewDataBlock(mDataBlock->jetEmitter[EtherformData::TrailEmitter], false);
			emitter->registerObject();
			mJetEmitter[EtherformData::TrailEmitter] = emitter;
		}
		MatrixF mat = this->getRenderTransform();
		Point3F pos,axis;
		//mat.getColumn(1,&axis);
		axis = this->getVelocity(); axis.normalize();
		mat.getColumn(3,&pos);
		emitter->emitParticles(pos,true,axis,getVelocity(),(U32)(dt * 1000));
   }
	else
	{
		if(bool(emitter))
		{
			emitter->deleteWhenEmpty();
			mJetEmitter[EtherformData::TrailEmitter] = 0;
		}
	}
}

//----------------------------------------------------------------------------

void Etherform::updateWorkingCollisionSet()
{
   // First, we need to adjust our velocity for possible acceleration.  It is assumed
   // that we will never accelerate more than 20 m/s for gravity, plus 10 m/s for
   // jetting, and an equivalent 10 m/s for jumping.  We also assume that the
   // working list is updated on a Tick basis, which means we only expand our
   // box by the possible movement in that tick.
   Point3F scaledVelocity = mVelocity * TickSec;
   F32 len    = scaledVelocity.len();
   F32 newLen = len + (10.0f * TickSec);

   // Check to see if it is actually necessary to construct the new working list,
   // or if we can use the cached version from the last query.  We use the x
   // component of the min member of the mWorkingQueryBox, which is lame, but
   // it works ok.
   bool updateSet = false;

   Box3F convexBox = mConvex.getBoundingBox(getTransform(), getScale());
   F32 l = (newLen * 1.1f) + 0.1f;  // from Convex::updateWorkingList
   const Point3F  lPoint( l, l, l );
   convexBox.minExtents -= lPoint;
   convexBox.maxExtents += lPoint;

   // Check containment
   if (mWorkingQueryBox.minExtents.x != -1e9f)
   {
      if (mWorkingQueryBox.isContained(convexBox) == false)
         // Needed region is outside the cached region.  Update it.
         updateSet = true;
   }
   else
   {
      // Must update
      updateSet = true;
   }
   
   // Actually perform the query, if necessary
   if (updateSet == true)
   {
      const Point3F  twolPoint( 2.0f * l, 2.0f * l, 2.0f * l );
      mWorkingQueryBox = convexBox;
      mWorkingQueryBox.minExtents -= twolPoint;
      mWorkingQueryBox.maxExtents += twolPoint;

      disableCollision();
      mConvex.updateWorkingList(mWorkingQueryBox,
         isGhost() ? sClientCollisionContactMask : sServerCollisionContactMask);
      enableCollision();
   }
}

void Etherform::updateVelocity(const Move* move)
{
	Point3F vec,pos;
	if(move) 
	{       
		//Prevent interpolating the wrong way round a circle.
		if(mRot.z > M_PI_F)
		 mRot.z -= M_2PI_F;
		if(mRot.z < -M_PI_F)
		 mRot.z += M_2PI_F;

		// Update orientation
		delta.rotVec = mRot;
		mObjToWorld.getColumn(3,&delta.posVec);

		mRot.x += move->pitch;
		if(mRot.x > MaxPitch)
		 mRot.x = MaxPitch;
		else if(mRot.x < -MaxPitch)
		 mRot.x = -MaxPitch;

		mRot.z += move->yaw;

		Point3F acc(0, 0, 0);

		int faster = 1;
		/*
		if(move->trigger[0])
		faster *= 2;
		if(move->trigger[1])
		faster *= 4;
		*/

		F32 scale = mDataBlock->accelerationForce * faster;

		mObjToWorld.getColumn(3,&pos);
		// sideways...
		mObjToWorld.getColumn(0,&vec);
		acc += vec * move->x * TickSec * scale;
		// forward/backward...
		mObjToWorld.getColumn(1,&vec);
		acc += vec * move->y * TickSec * scale;
		// up/down...
		mObjToWorld.getColumn(2,&vec);
		acc += vec * move->trigger[2] * TickSec * scale;
		vec.neg();
		acc += vec * move->trigger[6] * TickSec * scale;

		// Ignore force from physical zones...
		// acc += (mAppliedForce / mMass) * TickSec;

		mVelocity += acc;
		mVelocity -= mVelocity * mDrag * TickSec; // drag

		setMaskBits(MoveMask);
	}
}

bool Etherform::updatePos(const F32 travelTime)
{
   PROFILE_SCOPE(Etherform_UpdatePos);
   getTransform().getColumn(3, &delta.posVec);

   // When mounted to another object, only Z rotation used.
   if(isMounted()) 
	{
      mVelocity = mMount.object->getVelocity();
      setPosition(Point3F(0.0f, 0.0f, 0.0f), mRot);
      setMaskBits(MoveMask);
      return true;
   }

   Point3F newPos;

   Collision col;
   dMemset(&col, 0, sizeof(col));

   // DEBUG:
   //Point3F savedVelocity = mVelocity;

   if(mVelocity.isZero())
      newPos = delta.posVec;
   else
      newPos = _move(travelTime, &col);
   
   _handleCollision(col);

   // DEBUG:
   //if ( isClientObject() )
   //   Con::printf( "(client) vel: %g %g %g", mVelocity.x, mVelocity.y, mVelocity.z );
   //else
   //   Con::printf( "(server) vel: %g %g %g", mVelocity.x, mVelocity.y, mVelocity.z );

   // Set new position
	// If on the client, calc delta for backstepping
	if(isClientObject()) 
	{
		delta.pos = newPos;
		delta.rot = mRot;
		delta.posVec = delta.posVec - delta.pos;
		delta.rotVec = delta.rotVec - delta.rot;
		delta.dt = 1.0f;
	}

   this->setPosition(newPos, mRot);
   this->setMaskBits(MoveMask);
   this->updateContainer();

   if (!isGhost())  
   {
      // Collisions are only queued on the server and can be
      // generated by either updateMove or updatePos
      notifyCollision();

      // Do mission area callbacks on the server as well
      //checkMissionArea();
   }

   // Check the total distance moved.  If it is more than 1000th of the velocity, then
   //  we moved a fair amount...
   //if (totalMotion >= (0.001f * initialSpeed))
      return true;
   //else
      //return false;
}

//----------------------------------------------------------------------------

void Etherform::updateCameraPos(F32 delta)
{
	//
	// Update 3rd person camera position.
	//

	F32 min,max;
	Point3F offset;
	MatrixF rot;
	this->getCameraParameters(&min,&max,&offset,&rot);

	Point3F vec = mCameraTargetPos - mCameraPos;
	F32    dist = vec.len();

	if(dist == 0)
	{
		// Catch camera position up to its target position.
		mCameraPos = mCameraTargetPos;
	}
	else if(dist > max)
	{
		// Catch camera up to max allowed dist from target position.
		vec.normalize(); vec.neg();
		mCameraPos = mCameraTargetPos + vec * max;
	}
	else
	{
		// Move camera pos towards its target pos.
#if 0
		F32 speed = mDataBlock->accelerationForce;
		speed *= 1 - (1/vec.lenSquared());

		vec.normalize();
		mCameraPos += vec * speed * delta;
#else
		//F32 speedScale = this->getVelocity().len() / mDataBlock->accelerationForce;
		F32 speedScale = 4; //mDataBlock->accelerationForce / 2;
		F32 distScale = 1 - (1/vec.lenSquared());
		vec *= speedScale * distScale * delta;
		if(vec.len() > dist)
			mCameraPos = mCameraTargetPos;
		else
			mCameraPos += vec;
#endif
	}
}

//----------------------------------------------------------------------------

Point3F Etherform::getVelocity() const
{
   return mVelocity;
}

void Etherform::setVelocity(const VectorF& vel)
{
   mVelocity = vel;
   this->setMaskBits(MoveMask);
}

void Etherform::applyImpulse(const Point3F&, const VectorF& vec)
{
   // Etherforms ignore angular velocity
   VectorF vel;
   vel.x = vec.x / mMass;
   vel.y = vec.y / mMass;
   vel.z = vec.z / mMass;
   this->setVelocity(mVelocity + vel);
}

//----------------------------------------------------------------------------

void Etherform::writePacketData(GameConnection *connection, BitStream *bstream)
{
	Parent::writePacketData(connection, bstream);

	Point3F pos;
	mObjToWorld.getColumn(3,&pos);
	bstream->setCompressionPoint(pos);
	mathWrite(*bstream, pos);

	bstream->write(mRot.x);
	bstream->write(mRot.z);

	bstream->write(mVelocity.x);
	bstream->write(mVelocity.y);
	bstream->write(mVelocity.z);
}

void Etherform::readPacketData(GameConnection *connection, BitStream *bstream)
{
	Parent::readPacketData(connection, bstream);

	Point3F pos, rot;

	mathRead(*bstream, &pos);
	bstream->setCompressionPoint(pos);

	bstream->read(&rot.x);
	bstream->read(&rot.z);

	bstream->read(&mVelocity.x);
	bstream->read(&mVelocity.y);
	bstream->read(&mVelocity.z);

	delta.pos = pos;
	delta.rot = rot;

	this->setPosition(pos,rot);
}

U32 Etherform::packUpdate(NetConnection *con, U32 mask, BitStream *bstream)
{
   Parent::packUpdate(con,mask,bstream);

   // The rest of the data is part of the control object packet update.
   // If we're controlled by this client, we don't need to send it.
   if(bstream->writeFlag(getControllingClient() == con && !(mask & InitialUpdateMask)))
      return 0;

   if (bstream->writeFlag(mask & MoveMask))
   {
      Point3F pos;
      mObjToWorld.getColumn(3,&pos);
      bstream->write(pos.x);
      bstream->write(pos.y);
      bstream->write(pos.z);

      bstream->write(mRot.x);
      bstream->write(mRot.z);

      F32 len = mVelocity.len();
      if(bstream->writeFlag(len > 0.02f))
      {
         Point3F outVel = mVelocity;
         outVel *= 1.0f/len;
         bstream->writeNormalVector(outVel, 10);
         len *= 32.0f;  // 5 bits of fraction
         if(len > 8191)
            len = 8191;
         bstream->writeInt((S32)len, 13);
      }

      delta.move.pack(bstream);
      bstream->writeFlag(!(mask & NoWarpMask));
   }

   return 0;
}

void Etherform::unpackUpdate(NetConnection *con, BitStream *bstream)
{
   Parent::unpackUpdate(con,bstream);

   // controlled by the client?
   if(bstream->readFlag())
      return;

   if (bstream->readFlag())
   {
      Point3F pos,rot;
      bstream->read(&pos.x);
      bstream->read(&pos.y);
      bstream->read(&pos.z);

      bstream->read(&rot.x);
      bstream->read(&rot.z);

      F32 speed = mVelocity.len();
      if(bstream->readFlag())
      {
         bstream->readNormalVector(&mVelocity, 10);
         mVelocity *= bstream->readInt(13) / 32.0f;
      }
      else
      {
         mVelocity.set(0.0f, 0.0f, 0.0f);
      }

	  delta.move.unpack(bstream);

      if(bstream->readFlag() && isProperlyAdded())
      {
         // Determine number of ticks to warp based on the average
         // of the client and server velocities.
         delta.warpOffset = pos - delta.pos;
         F32 as = (speed + mVelocity.len()) * 0.5f * TickSec;
         F32 dt = (as > 0.00001f) ? delta.warpOffset.len() / as: sMaxWarpTicks;
         delta.warpTicks = (S32)((dt > sMinWarpTicks) ? getMax(mFloor(dt + 0.5f), 1.0f) : 0.0f);

         if(delta.warpTicks)
		 {
            // Setup the warp to start on the next tick.
            if(delta.warpTicks > sMaxWarpTicks)
               delta.warpTicks = sMaxWarpTicks;

            delta.warpOffset /= delta.warpTicks;
            delta.rotOffset = rot - delta.rot;
            delta.rotOffset /= delta.warpTicks;
         }
         else {
            // Going to skip the warp, server and client are real close.
            // Adjust the frame interpolation to move smoothly to the
            // new position within the current tick.
            if (delta.dt == 0.0f) {
               delta.posVec.set(0.0f, 0.0f, 0.0f);
               delta.rotVec.set(0.0f, 0.0f, 0.0f);
            }
            else {
               Point3F cp = delta.pos + delta.posVec * delta.dt;
			   Point3F cr = delta.rot + delta.rotVec * delta.dt;
               F32 dti = 1.0f / delta.dt;
               delta.posVec = (cp - pos) * dti;
			   delta.rotVec = (cr - rot) * dti;
            }

            delta.pos = pos;
            delta.rot = rot;

            this->setPosition(pos,rot);
         }
      }
      else {
         // Set the etherform to the server position
         delta.pos = pos;
         delta.rot = rot;
         delta.posVec.set(0.0f, 0.0f, 0.0f);
         delta.rotVec.set(0.0f, 0.0f, 0.0f);
         delta.warpTicks = 0;
         delta.dt = 0.0f;
         this->setPosition(pos, rot);
      }
   }
}


//----------------------------------------------------------------------------

void Etherform::initPersistFields()
{
   Parent::initPersistFields();
}

void Etherform::consoleInit()
{
   Con::addVariable("Etherform::minWarpTicks", TypeF32, &sMinWarpTicks);
   Con::addVariable("Etherform::maxWarpTicks", TypeS32, &sMaxWarpTicks);
   Con::addVariable("Etherform::maxPredictionTicks", TypeS32, &sMaxPredictionTicks);   
}

Point3F &Etherform::getPosition()
{
   static Point3F position;
   mObjToWorld.getColumn(3, &position);
   return position;
}

ConsoleMethod( Etherform, getPosition, const char *, 2, 2, "()"
              "Get the position of the object.\n\n"
              "@returns A string of form \"x y z\".")
{
   static char buffer[100];

   Point3F& pos = object->getPosition();
   dSprintf(buffer, sizeof(buffer),"%g %g %g",pos.x,pos.y,pos.z);
   return buffer;
}

//----------------------------------------------------------------------------

void Etherform::setPosition(const Point3F& pos, const Point3F& rot, MatrixF *mat)
{
   MatrixF xRot, zRot;
   xRot.set(EulerF(rot.x, 0, 0));
   zRot.set(EulerF(0, 0, rot.z));
   mat->mul(zRot, xRot);
   mat->setColumn(3,pos);
   mRot = rot;
}

void Etherform::setTransform(const MatrixF& mat)
{
   // This method should never be called on the client.

   // This currently converts all rotation in the mat into
   // rotations around the z and x axis.
   Point3F pos,vec;
   mat.getColumn(1,&vec);
   mat.getColumn(3,&pos);
   Point3F rot(-mAtan2(vec.z, mSqrt(vec.x*vec.x + vec.y*vec.y)),0,-mAtan2(-vec.x,vec.y));
   this->setPosition(pos,rot);

   this->setMaskBits(MoveMask | NoWarpMask); // don't warp to new transform on clients
}

/* 
void Etherform::setRenderTransform(const MatrixF& mat)
{
   // This method should never be called on the client.

   // This currently converts all rotation in the mat into
   // rotations around the z and x axis.
   Point3F pos,vec;
   mat.getColumn(1,&vec);
   mat.getColumn(3,&pos);
   Point3F rot(-mAtan(vec.z, mSqrt(vec.x*vec.x + vec.y*vec.y)),0,-mAtan(-vec.x,vec.y));
   setRenderPosition(pos,rot);
}
*/

void Etherform::getCameraTransform(F32* pos, MatrixF* mat)
{
	// Returns camera to world space transform
	// Handles first person / third person camera position

	if(isServerObject() && mShapeInstance)
		mShapeInstance->animateNodeSubtrees(true);

	if(*pos != 0)
	{
		this->updateCameraPos(0);

		F32 min,max;
		Point3F offset;
		MatrixF eye,rot;
		this->getCameraParameters(&min,&max,&offset,&rot);
		this->getRenderEyeTransform(&eye);

		Point3F rpos = this->getRenderPosition();
		mat->mul(eye,rot);		
		mat->setColumn(3, rpos + (mCameraPos-rpos) * *pos);

		//
		// Update camera target pos...
		//

		// Use the eye transform to orient the camera
		VectorF vp,vec;
		vp.x = vp.z = 0; vp.y = -min;
		eye.mulV(vp,&vec);

		Point3F sp = this->getRenderPosition();
		Point3F ep;
		if(mDataBlock->cameraNode != -1)
		{
			mShapeInstance->mNodeTransforms[mDataBlock->cameraNode].getColumn(3,&ep);

			// Scale the camera position before applying the transform
			const Point3F& scale = getScale();
			ep.convolve( scale );

			this->getRenderTransform().mulP(ep);
		}
		else
		{
			this->getRenderTransform().getColumn(3, &ep);
		}
		ep += vec + offset;

		this->disableCollision();
		if(this->isMounted())
			this->getObjectMount()->disableCollision();

		RayInfo collision;
		U32 colMask = (0xFFFFFFFF & ~(WaterObjectType | GameBaseObjectType | DefaultObjectType));
		if(mContainer->castRay(sp, ep, colMask, &collision))
		{
			ep = collision.point + collision.normal;
		}
		else
		{
			const Point3F vecs[6] = {
				Point3F(  1,  0,  0 ),
				Point3F( -1,  0,  0 ),
				Point3F(  0,  1,  0 ),
				Point3F(  0, -1,  0 ),
				Point3F(  0,  0,  1 ),
				Point3F(  0,  0, -1 )
			};

			for(int i = 0; i < 6; i++)
			{
				Point3F test = ep + vecs[i] * 0.1;
				if(mContainer->castRay(ep, test, colMask, &collision))
					ep += collision.normal * ((1-collision.t));
			}
		}

		mCameraTargetPos = ep;

		if(this->isMounted())
			this->getObjectMount()->enableCollision();
		this->enableCollision();
	}
	else
	{
		getRenderEyeTransform(mat);
	}
}
