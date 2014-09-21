// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "NOTC/shotgunprojectile.h"

#include "scene/sceneRenderState.h"
#include "scene/sceneManager.h"
#include "lighting/lightInfo.h"
#include "lighting/lightManager.h"
#include "console/consoleTypes.h"
#include "console/typeValidators.h"
#include "core/resourceManager.h"
#include "core/stream/bitStream.h"
#include "T3D/fx/explosion.h"
#include "T3D/shapeBase.h"
#include "ts/tsShapeInstance.h"
#include "sfx/sfxTrack.h"
#include "sfx/sfxSource.h"
#include "sfx/sfxSystem.h"
#include "sfx/sfxTypes.h"
#include "math/mathUtils.h"
#include "math/mathIO.h"
#include "sim/netConnection.h"
#include "T3D/fx/particleEmitter.h"
#include "T3D/fx/splash.h"
#include "T3D/physics/physicsPlugin.h"
#include "T3D/physics/physicsWorld.h"
#include "gfx/gfxTransformSaver.h"
#include "T3D/containerQuery.h"
#include "T3D/decal/decalManager.h"
#include "T3D/decal/decalData.h"
#include "T3D/lightDescription.h"
#include "console/engineAPI.h"
#include "T3D/gameBase/gameConnection.h"
#include "NOTC/fx/multiNodeLaserBeam.h"

static MRandomLCG sRandom(0x1);

//--------------------------------------------------------------------------
//

IMPLEMENT_CO_DATABLOCK_V1(ShotgunProjectileData);

ShotgunProjectileData::ShotgunProjectileData()
{
	noFake = false;

	energyDrain = 0;

	numBullets = 10;
	bulletDistMode = 0;

	range = 1000.0f;

	muzzleSpreadRadius = 0.0f;
	referenceSpreadRadius = 0.0f;
	referenceSpreadDistance = 0.0f;
}

//--------------------------------------------------------------------------

void ShotgunProjectileData::initPersistFields()
{
	Parent::initPersistFields();

	addField("noFake",                  TypeBool, Offset(noFake, ShotgunProjectileData));
	addField("energyDrain",             TypeS32,  Offset(energyDrain, ShotgunProjectileData));
	addField("numBullets",              TypeS32,  Offset(numBullets, ShotgunProjectileData));
	addField("bulletDistMode",          TypeS32,  Offset(bulletDistMode, ShotgunProjectileData));
	addField("range",                   TypeF32,  Offset(range, ShotgunProjectileData));
	addField("muzzleSpreadRadius",	   TypeF32,  Offset(muzzleSpreadRadius, ShotgunProjectileData));
	addField("referenceSpreadRadius",	TypeF32,  Offset(referenceSpreadRadius, ShotgunProjectileData));
	addField("referenceSpreadDistance", TypeF32,  Offset(referenceSpreadDistance, ShotgunProjectileData));
}

//--------------------------------------------------------------------------

bool ShotgunProjectileData::onAdd()
{
   if(!Parent::onAdd())
      return false;

   return true;
}


bool ShotgunProjectileData::preload(bool server, String &errorStr)
{
   if (Parent::preload(server, errorStr) == false)
      return false;

   return true;
}

//--------------------------------------------------------------------------

void ShotgunProjectileData::packData(BitStream* stream)
{
   Parent::packData(stream);

   stream->writeFlag(noFake);

   stream->write(energyDrain);

   stream->write(numBullets);
   stream->write(bulletDistMode);

   stream->write(range);

   stream->write(muzzleSpreadRadius);
	stream->write(referenceSpreadRadius);
	stream->write(referenceSpreadDistance);
}

void ShotgunProjectileData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);

   noFake = stream->readFlag();

   stream->read(&energyDrain);

   stream->read(&numBullets);
   stream->read(&bulletDistMode);

   stream->read(&range);

   stream->read(&muzzleSpreadRadius);
	stream->read(&referenceSpreadRadius);
	stream->read(&referenceSpreadDistance);
}

//--------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(ShotgunProjectileTracer);

ShotgunProjectileTracer::ShotgunProjectileTracer(const Point3F* impactPos)
{
	mNetFlags.clear();
	mNetFlags.set(IsGhost);

	if(impactPos)
		mImpactPos.set(*impactPos);
	mAtImpactPos = false;
}

ShotgunProjectileTracer::~ShotgunProjectileTracer()
{

}

bool ShotgunProjectileTracer::onAdd()
{
	AssertFatal(isClientObject(), "ShotgunProjectileTracer on the server? - Someone fucked up!");

	if(mDataBlock->muzzleVelocity <= 10)
	{
		mCurrVelocity = (mImpactPos - mCurrPosition) / mDataBlock->muzzleVelocity;
		mCurrVelocity *= TickMs;
	}

	mInitialPosition = mCurrPosition;
	mInitialVelocity = mCurrVelocity;

	mCurrDeltaBase = mCurrPosition;
	mCurrBackDelta = -mCurrVelocity;

	if(!Parent::onAdd())
		return false;	
    
	return true;
}

bool ShotgunProjectileTracer::onNewDataBlock(GameBaseData* dptr, bool reload)
{
	mDataBlock = dynamic_cast<ShotgunProjectileData*>(dptr);
	if(!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
		return false;

	return true;
}

void ShotgunProjectileTracer::processTick(const Move* move)
{
	AssertFatal(isClientObject(), "ShotgunProjectileTracer on the server? - Someone fucked up!");

#if 0
	mNumTicks++;
#endif

	mCurrTick++;

	if(mAtImpactPos)
		this->deleteObject();
	return;

	// HACK HACK HACK
	if(mDataBlock->muzzleVelocity > 9000)
	{
      this->missedEnemiesCheck(mInitialPosition, mImpactPos);
		this->addLaserTrailNode(mInitialPosition, false);
		this->addLaserTrailNode(mImpactPos, false);

#if 0
		for(S32 i = 0; i < NUM_LASERTRAILS; i++)
		{
			if( mLaserTrailList[i] != NULL )
			{
				mLaserTrailList[i]->setSceneObjectColorization(this->getSceneObjectColorization());
				if(mDataBlock->smoothLaserTrail)
					mLaserTrailList[i]->smooth();
				if(mDataBlock->laserTrailFlagsList[i] & 1)
					mLaserTrailList[i]->smoothReverseDist(mDataBlock->range);
				if(mDataBlock->laserTrailFlagsList[i] & 2)
					mLaserTrailList[i]->smooth();
				if(mDataBlock->laserTrailFlagsList[i] & 4)
					mLaserTrailList[i]->smoothDist(2);
			}
		}
#endif

#if 0
		if(mDataBlock->laserTail != NULL)
		{
			LaserBeam* beam = new LaserBeam();
			beam->setSceneObjectColorization(this->getSceneObjectColorization());
			beam->onNewDataBlock(mDataBlock->laserTail);
			if(!beam->registerObject())
			{
				Con::warnf( ConsoleLogEntry::General, "Could not register laserTail for class: %s", mDataBlock->getName() );
				delete beam;
			}  
			else
			{
				beam->setRender(true);
				F32 r = sRandom.randF();
				Point3F v = (mImpactPos - mInitialPosition)*r;
				Point3F vel = v; vel.normalize(); vel *= mDataBlock->muzzleVelocity;
				beam->makeDisappear(mInitialPosition, mInitialPosition + v,
					vel, mDataBlock->laserTailLen);
			}
		}

#endif

		this->deleteObject();
		return;
	}


	if(mCurrTick >= mDataBlock->lifetime)
	{
		deleteObject();
		return;
	}
	
	F32 timeLeft;
	RayInfo rInfo;
	Point3F oldPosition;
	Point3F newPosition;

	oldPosition = mCurrPosition;

	newPosition = oldPosition + mCurrVelocity * TickSec;

	F32 oldDist = (oldPosition-mImpactPos).len();
	F32 newDist = (newPosition-mImpactPos).len();
	if(newDist > oldDist) // going away from target?
		newPosition = mImpactPos;

	mCurrDeltaBase = newPosition;
	mCurrBackDelta = mCurrPosition - newPosition;

   this->emitParticles(oldPosition, newPosition, mCurrVelocity, TickMs);
   this->missedEnemiesCheck(oldPosition, newPosition);

#if 0

	//emitParticles(mCurrPosition, newPosition, mCurrVelocity, TickMs);

	// update laser trail...
	if( mEmissionCount == 0 )
	{
		addLaserTrailNode(mInitialPosition,false);

		for( U8 i = 0; i < mNumBouncePoints; i++ )
		{
			//Con::printf("processTick(): (client) adding bouncePoint %u: %f %f %f",i,mBouncePoint[i].x,mBouncePoint[i].y,mBouncePoint[i].z);
			addLaserTrailNode(mBouncePoint[i].pos, false);
			createBounceExplosion(mBouncePoint[i].pos, mBouncePoint[i].norm, mBouncePoint[i].decal);
		}
	}

	if( mFxLight != NULL )
		mFxLight->setPosition(mCurrDeltaBase);

	addLaserTrailNode(newPosition,false);

	mEmissionCount++;     
#endif

	if(newPosition == mImpactPos)
	{
		this->deleteObject();
		return;
	}

	mCurrPosition = newPosition;

	MatrixF xform(true);
	xform.setColumn(3, mCurrPosition);
	setTransform(xform);
}

void ShotgunProjectileTracer::advanceTime(F32 dt)
{
	Parent::advanceTime(dt);

	if(mAtImpactPos)
		return;

	this->simulate(dt);
	this->updateSound();
}

void ShotgunProjectileTracer::interpolateTick(F32 delta)
{
	// ShotgunProjectileTracers use advanceTime() to
	// advance their simulation (instead of ticks).
}

void ShotgunProjectileTracer::simulate(F32 dt)
{
	F32 timeLeft;
	RayInfo rInfo;
	Point3F oldPosition;
	Point3F newPosition;

	oldPosition = mCurrPosition;

   if(oldPosition == mInitialPosition)
      this->addLaserTrailNode(mInitialPosition, false);

	newPosition = oldPosition + mCurrVelocity * dt;

	F32 oldDist = (oldPosition-mImpactPos).len();
	F32 newDist = (newPosition-mImpactPos).len();
	if(newDist > oldDist) // going away from target?
	{
		newPosition = mImpactPos;
		mAtImpactPos = true;
	}

	mCurrDeltaBase = newPosition;
	mCurrBackDelta = mCurrPosition - newPosition;

   if(mEmissionCount == 0)
      this->addLaserTrailNode(mInitialPosition, false);

	this->emitParticles(oldPosition, newPosition, mCurrVelocity, dt*1000);
   this->missedEnemiesCheck(oldPosition, newPosition);
   this->addLaserTrailNode(newPosition, true);

   mEmissionCount++;

	mCurrPosition = newPosition;

   Point3F dir = mCurrVelocity;
   if(dir.isZero())
      dir.set(0,0,1);
   else
      dir.normalize();

   MatrixF xform(true);
	xform = MathUtils::createOrientFromDir(dir);
   xform.setPosition(mCurrPosition);
   setTransform(xform);
}

//--------------------------------------------------------------------------

ShotgunHit::ShotgunHit()
{
	object        = NULL;
	numImpacts    = 0;
}

ShotgunHit::ShotgunHit(const ShotgunHit& hit)
{
	object          = hit.object;
	objectPos       = hit.objectPos;
	numImpacts      = hit.numImpacts;
	impactCenterVec = hit.impactCenterVec;
	impactVecs      = hit.impactVecs;
	impactNormals   = hit.impactNormals;
}

ShotgunHit::~ShotgunHit()
{

}

void ShotgunHit::pack(NetConnection* con, BitStream* stream)
{
	// send object id or object pos if the object does not exist anymore
	if(stream->writeFlag(object.isNull()))
	{
		mathWrite(*stream, objectPos);
	}
	else
	{
		S32 ghostIndex = -1;
		if(stream->writeFlag(object->isClientObject()))
			ghostIndex = object->getNetIndex();
		else
			ghostIndex = con->getGhostIndex(object);

		if(stream->writeFlag(ghostIndex != -1))
			stream->writeRangedU32(U32(ghostIndex), 0, NetConnection::MaxGhostCount);
		else
			mathWrite(*stream, objectPos);
	}

	stream->write(numImpacts);
	mathWrite(*stream, impactCenterVec);
	for(U32 i = 0; i < numImpacts; i ++)
	{
		mathWrite(*stream, impactVecs[i]);
		mathWrite(*stream, impactNormals[i]);
	}
}

void ShotgunHit::unpack(NetConnection* con, BitStream* stream)
{
	if(stream->readFlag())
	{
		mathRead(*stream, &objectPos);
	}
	else
	{
		bool onServer = stream->readFlag();
		
		if(stream->readFlag())
		{
			U32 objectId = stream->readRangedU32(0, NetConnection::MaxGhostCount);
			if(onServer)
			{
				NetObject* pObj = con->resolveObjectFromGhostIndex(objectId);
				object = dynamic_cast<SceneObject*>(pObj);
			}
			else
			{
				NetObject* pObj = con->resolveGhost(objectId);
				object = dynamic_cast<SceneObject*>(pObj);
			}

			if(object)
				objectPos = object->getPosition();
		}
		else
			mathRead(*stream, &objectPos);
	}

	stream->read(&numImpacts);
	mathRead(*stream, &impactCenterVec);
	for(U32 i = 0; i < numImpacts; i ++)
	{
		Point3F impactVec, impactNormal;
		mathRead(*stream, &impactVec);
		mathRead(*stream, &impactNormal);
		impactVecs.push_back(impactVec);
		impactNormals.push_back(impactNormal);
	}
}

//--------------------------------------------------------------------------

IMPLEMENT_CO_NETOBJECT_V1(ShotgunProjectile);

ShotgunProjectile::ShotgunProjectile(bool onClient, bool findHits)
{
	mFindHits = findHits;

	mHitsSource = NULL;
	
	mNetFlags.clear();
	if(onClient)
	{
		mNetFlags.set(IsGhost);
	}
	else
	{
		mNetFlags.set(Ghostable);
	}
}

ShotgunProjectile::~ShotgunProjectile()
{
	U32 n = mHits.size();
	while(n--)
		delete mHits[n];
}

void ShotgunProjectile::onDeleteNotify(SimObject* obj)
{
	Parent::onDeleteNotify(obj);
}

//--------------------------------------------------------------------------

void ShotgunProjectile::initPersistFields()
{
   Parent::initPersistFields();
}

void ShotgunProjectile::consoleInit()
{
	Parent::consoleInit();
}


//--------------------------------------------------------------------------

class ObjectDeleteEvent : public SimEvent
{
public:
   void process(SimObject *object)
   {
      object->deleteObject();
   }
};

bool ShotgunProjectile::onAdd()
{
	if(!Parent::onAdd())
		return false;	

	setProcessTick(false); 	// no need to process ticks

	if(mFindHits)
	{
		this->findHits();
		if(this->isClientObject())
			this->transmitHitsToServer();
	}

	this->processHits();

	if(isClientObject())
	{
		if(mFindHits)
		{
			this->deleteObject();
			return true;
		}
		else
		{
			mHasExploded = true;
		}
	}
	else
	{
		// Need valid transform for scoping.
		Point3F dir = mCurrVelocity; dir.normalize();
		MatrixF mat = MathUtils::createOrientFromDir(dir);
		mat.setPosition(mCurrPosition);
		this->setTransform(mat);

		// Delete us after we've had some time to ghost.
		Sim::postEvent(this, new ObjectDeleteEvent, Sim::getCurrentTime() + DeleteWaitTime);		
	}

	return true;
}


void ShotgunProjectile::onRemove()
{
	Parent::onRemove();
}


bool ShotgunProjectile::onNewDataBlock(GameBaseData* dptr, bool reload)
{
	mDataBlock = dynamic_cast<ShotgunProjectileData*>( dptr );
	if(!mDataBlock || !Parent::onNewDataBlock(dptr, reload))
		return false;

	return true;
}


//----------------------------------------------------------------------------

void ShotgunProjectile::processTick(const Move* move)
{
	AssertFatal(isClientObject(), "ShotgunProjectile::processTick() being called? - Someone fucked up!");
	//mNumTicks++;
	//mCurrTick++;
	//if(isServerObject() && mCurrTick >= mDataBlock->lifetime)
	//	deleteObject();
}


void ShotgunProjectile::advanceTime(F32 dt)
{
   Parent::advanceTime(dt);
}

void ShotgunProjectile::interpolateTick(F32 delta)
{
   Parent::interpolateTick(delta);
}

//--------------------------------------------------------------------------

U32 ShotgunProjectile::packUpdate(NetConnection* con, U32 mask, BitStream* stream)
{
	U32 retMask = Parent::packUpdate(con, mask, stream);

	// Transmit hits...
	// Note: Don't send hits back to their source.
	if(stream->writeFlag((mask & GameBase::InitialUpdateMask) && con != mHitsSource))
	{
		U32 n = mHits.size();
		stream->write(n);
		while(n--)
			mHits[n]->pack(con, stream);
	}

	return retMask;
}

void ShotgunProjectile::unpackUpdate(NetConnection* con, BitStream* stream)
{
	Parent::unpackUpdate(con, stream);

	// Read hits?
	if(stream->readFlag())
	{
		U32 n; stream->read(&n);
		while(n--)
		{
			ShotgunHit* newHit = new ShotgunHit();
			newHit->unpack(con, stream);
			mHits.push_back(newHit);
		}
	}
}

//--------------------------------------------------------------------------

void ShotgunProjectile::addHits(NetConnection* client, const ShotgunHits& hits)
{
	mHitsSource = client;

	U32 n = hits.size();
	while(n--)
		mHits.push_back(new ShotgunHit(*hits[n]));
}

void ShotgunProjectile::findHits()
{
	mSourceObject->disableCollision();

	Point3F muzzlePoint = mCurrPosition;

	Point3F dir = mCurrVelocity; dir.normalize();
	MatrixF transform = MathUtils::createOrientFromDir(dir);

	Point3F zv; transform.getColumn(2, &zv);
	zv.normalize();

	Point3F startEdge = muzzlePoint 
		+ zv * mDataBlock->muzzleSpreadRadius;
	Point3F refEdge = muzzlePoint + dir * mDataBlock->referenceSpreadDistance
		+ zv * mDataBlock->referenceSpreadRadius;
	Point3F vec = refEdge - startEdge; vec.normalize();
	Point3F endEdge = startEdge + vec * mDataBlock->range;

	Point3F startCenter = muzzlePoint;
	Point3F endCenter = muzzlePoint + dir * mDataBlock->range;

	//
	// collect hits...
	//
	int totalImpacts = 0;
	Vector<Point3F> misses;
	if(mDataBlock->bulletDistMode == 0)
	{
		for(int i=0; i < mDataBlock->numBullets; i++)
		{
			Point3F startClockVec = startEdge - startCenter;
			Point3F endClockVec = endEdge - endCenter;

			MatrixF rotmat(EulerF(0, 6.28 * sRandom.randF(), 0));

			rotmat.mulV(startClockVec);
			rotmat.mulV(endClockVec);

			Point3F startVec = startClockVec;
			transform.mulV(startVec);

			Point3F endVec = endClockVec;
			transform.mulV(endVec);

			F32 r = sRandom.randF();

			Point3F start = startCenter + startVec * r;
			Point3F end = endCenter + endVec * r;

			RayInfo rInfo;
			bool collision = getContainer()->castRay(start, end, csmDynamicCollisionMask | csmStaticCollisionMask, mDataBlock->collisionMask, &rInfo);
			if(collision)
			{
				ShotgunHit* hit = NULL;
				for(int k=0; k<mHits.size(); k++)
				{
					if(mHits[k]->object == rInfo.object)
					{
						hit = mHits[k];
						break;
					}
				}

				if(hit == NULL)
				{
					hit = new ShotgunHit();
					hit->object = rInfo.object;
					hit->objectPos = hit->object->getPosition();
					hit->numImpacts = 0;
					mHits.push_back(hit);
				}

				hit->numImpacts++;
				Point3F impactVec = rInfo.point - hit->objectPos;
				hit->impactCenterVec += impactVec;
				hit->impactCenterVec /= 2;
				hit->impactVecs.push_back(impactVec);
				hit->impactNormals.push_back(rInfo.normal);

				totalImpacts++;
			}
			else
			{
				misses.push_back(end);
			}
		}
	}
	else
	{
		int numEdges = 40;
		int numSegments = 20;
		Point3F startClockVec = startEdge - startCenter;
		Point3F endClockVec = endEdge - endCenter;
		MatrixF rotmat(EulerF(0, 6.28 / numEdges, 0));
		for(int i=0; i < numEdges; i++)
		{
			rotmat.mulV(startClockVec);
			rotmat.mulV(endClockVec);

			Point3F startVec = startClockVec;
			transform.mulV(startVec);

			Point3F endVec = endClockVec;
			transform.mulV(endVec);

			Point3F startVecSeg = startVec / numSegments;
			Point3F endVecSeg = endVec / numSegments;

			startVec = startVecSeg;
			endVec = endVecSeg;

			for(int j = 0; j < numSegments; j++)
			{
				Point3F start = startCenter + startVec;
				Point3F end = endCenter + endVec;

				RayInfo rInfo;
				bool collision = getContainer()->castRay(start, end, csmDynamicCollisionMask | csmStaticCollisionMask, mDataBlock->collisionMask, &rInfo);
				if(collision)
				{
					ShotgunHit* hit = NULL;
					for(int k=0; k<mHits.size(); k++)
					{
						if(mHits[k]->object == rInfo.object)
						{
							hit = mHits[k];
							break;
						}
					}

					if(hit == NULL)
					{
						hit = new ShotgunHit();
						hit->object = rInfo.object;
						hit->objectPos = hit->object->getPosition();
						hit->numImpacts = 0;
						mHits.push_back(hit);
					}

					hit->numImpacts++;
					Point3F impactVec = rInfo.point - hit->objectPos;
					hit->impactCenterVec += impactVec;
					hit->impactCenterVec /= 2;
					hit->impactVecs.push_back(impactVec);
					hit->impactNormals.push_back(rInfo.normal);
				}
				else
				{
					misses.push_back(end);
				}

				startVec += startVecSeg;
				endVec += endVecSeg;
			}
		}

		// reduce number of impacts per hit according to the number
		// of bullets that the shotgun is supposed to fire...
		int totalBullets = numEdges * numSegments;
		int n = mHits.size();
		while(n--)
		{
			ShotgunHit* hit = mHits[n];
			//Con::printf("Number of actual impacts: %i of %i", hit->numImpacts, totalBullets);
			hit->numImpacts = F32(hit->numImpacts) / (totalBullets / mDataBlock->numBullets);
			hit->numImpacts = mClamp(hit->numImpacts + 1, 1, mDataBlock->numBullets);
			totalImpacts += hit->numImpacts;
			//Con::printf("Number of bullet impacts: %i of %i", hit->numImpacts, mDataBlock->numBullets);

			Vector<Point3F> newImpactVecs, newImpactNormals;
			for(int i = 0; i < hit->numImpacts; i++)
			{
				U32 idx = sRandom.randI(0, hit->impactVecs.size()-1);
				newImpactVecs.push_back(hit->impactVecs[idx]);
				newImpactNormals.push_back(hit->impactNormals[idx]);
			}
			hit->impactVecs = newImpactVecs;
			hit->impactNormals = newImpactNormals;
		}
	}

	// create a hit for the bullets that didn't hit anything
	int numMisses = mDataBlock->numBullets - totalImpacts;
	if(numMisses > 0)
	{
		ShotgunHit* newHit = new ShotgunHit();
		newHit->object = NULL;
		newHit->objectPos.set(0, 0, 0);
		newHit->impactCenterVec.set(0, 0, 0);
		newHit->numImpacts = numMisses;

		while(numMisses--)
		{
			Point3F impactVec;
			if(mDataBlock->bulletDistMode == 0)
				impactVec = misses[numMisses];
			else
				impactVec = misses[sRandom.randI(0, misses.size()-1)];
			newHit->impactCenterVec += impactVec;
			newHit->impactCenterVec /= 2;
			newHit->impactVecs.push_back(impactVec);
			newHit->impactNormals.push_back(Point3F(0, 0, 1));
		}

		mHits.push_back(newHit);
	}

	mSourceObject->enableCollision();
}

void ShotgunProjectile::processHits()
{
	if(isServerObject())
		this->serverProcessHits();
	else
		this->clientProcessHits();
}

void ShotgunProjectile::serverProcessHits()
{
	Point3F muzzlePoint = mCurrPosition;

	int n = mHits.size();
	while(n--)
	{
		ShotgunHit* hit = mHits[n];

		Point3F objectPos;
		if(hit->object.isNull())
			objectPos = hit->objectPos;
		else
			objectPos = hit->object->getPosition();

		for(int i = 0; i < hit->numImpacts; i++)
		{
			Point3F impactVec = hit->impactVecs[i];
			Point3F impactNormal = hit->impactNormals[i];

			Point3F impactPos = objectPos + impactVec;

#if 0
			mTraveledDistance = (impactPos-mCurrPosition).len();
#endif
			Parent::onCollision(impactPos, impactNormal, hit->object);
		}
	}
}

void ShotgunProjectile::clientProcessHits()
{
	Point3F muzzlePoint = mCurrPosition;

	int n = mHits.size();
	while(n--)
	{
		ShotgunHit* hit = mHits[n];

		Point3F objectPos;
		if(hit->object.isNull())
			objectPos = hit->objectPos;
		else
			objectPos = hit->object->getPosition();

		// eyecandy stuff...
		for(int i = 0; i < hit->numImpacts; i++)
		{
			Point3F impactVec = hit->impactVecs[i];
			Point3F impactNormal = hit->impactNormals[i];
			Point3F impactPos = objectPos + impactVec;

         this->missedEnemiesCheck(muzzlePoint, impactPos);

         if(false /*mDataBlock->muzzleVelocity > 0*/)
         {
			   Point3F velocity = impactPos - muzzlePoint;
			   F32 dist = velocity.len();
			   velocity.normalize(); 
			   //if(mDataBlock->spread == 0.0 && !hit->object.isNull())
			   //	velocity *= dist / (mDataBlock->lifetime * (F32(TickMs) / 1000.0f));
			   //else
				   velocity *= mDataBlock->muzzleVelocity;

			   ShotgunProjectileTracer* prj = new ShotgunProjectileTracer(&impactPos);
			   prj->mCurrPosition     = muzzlePoint;
			   prj->mCurrVelocity     = velocity;
			   prj->mSourceObject     = mSourceObject;
			   prj->mSourceObjectSlot = mSourceObjectSlot;

			   prj->setTeamId(this->getTeamId());
            prj->setPalette(this->getPalette());
			   prj->onNewDataBlock(mDataBlock, false);
			   if(!prj->registerObject())
			   {
				   Con::warnf(ConsoleLogEntry::General, "Could not register shotgun tracer projectile for image: %s", mDataBlock->getName());
				   delete prj;
				   prj = NULL;
			   }

			   if(hit->object.isNull())
			   {
   #if 0
				   prj->disableLaserTrail(1);
   #endif
				   continue;
			   }
         }

         for(S32 i = 0; i < ProjectileData::NumLaserTrails; i++)
         {
            if( mDataBlock->laserTrail[i] )
            {
               MultiNodeLaserBeam* trail = new MultiNodeLaserBeam();
               trail->setPalette(this->getPalette());
               trail->onNewDataBlock(mDataBlock->laserTrail[i], false);
               if(!trail->registerObject())
               {
                  Con::warnf( ConsoleLogEntry::General, "Could not register laserTrail %d for class: %s",i, mDataBlock->getName() );
                  delete trail;
               }
               else
               {
                  trail->setRender(true);
                  trail->addNodes(muzzlePoint);
                  trail->addNodes(impactPos);
                  if(mDataBlock->laserTrailFlags[i] & 1)
                     trail->smooth();
                  if(mDataBlock->laserTrailFlags[i] & 2)
                     trail->smoothDist(2);
                  if(mDataBlock->laserTrailFlags[i] & 4)
                     trail->smoothReverseDist(mDataBlock->range);
                  trail->fade();
                  trail->deleteOnFadeout();
               }
            }
         }

			SceneObject* sObj = hit->object.operator->();
#if 0
			if( sObj->getType() & Projectile::csmDynamicCollisionMask )
			{
				if( ((ShapeBase*)sObj)->getTeamId() == mTeamId )
				{
					mExplosionType = Projectile::HitTeammateExplosion;
					prj->disableLaserTrail(1);
				}
				else
				{
					mExplosionType = Projectile::HitEnemyExplosion;
					prj->disableLaserTrail(0);
				}
			}
			else
			{
				mExplosionType = Projectile::StandardExplosion;
				prj->disableLaserTrail(1);
			}
#endif
			
			ExplosionData* datablock = mDataBlock->explosion;

#if 0
			if( mExplosionType == HitEnemyExplosion && mDataBlock->hitEnemyExplosion != NULL )
				datablock = mDataBlock->hitEnemyExplosion;
			else if( mExplosionType == HitTeammateExplosion && mDataBlock->hitTeammateExplosion != NULL )
				datablock = mDataBlock->hitTeammateExplosion;
#endif

			if(datablock != NULL)
			{
				Explosion* pExplosion = new Explosion;
				pExplosion->setPalette(this->getPalette());
				pExplosion->onNewDataBlock(datablock, false);

				Point3F expPos = impactPos + impactNormal*0.1;
				
				MatrixF xform(true);
				xform.setPosition(expPos);
				pExplosion->setTransform(xform);
				pExplosion->setInitialState(expPos, impactNormal);
				pExplosion->setCollideType(hit->object ? hit->object->getTypeMask() : 0);
				if (pExplosion->registerObject() == false)
				{
					Con::errorf(ConsoleLogEntry::General, "ShotgunProjectile(%s)::explode: couldn't register explosion",
								mDataBlock->getName() );
					delete pExplosion;
					pExplosion = NULL;
				}

				if(mDataBlock->decal && hit->object
				&& !(hit->object->getTypeMask() & Projectile::csmDynamicCollisionMask)
				&& (hit->object->getTypeMask() & Projectile::csmStaticCollisionMask))
				{
					DecalInstance* dinst = gDecalManager->addDecal(impactPos, impactNormal, 0.0f, mDataBlock->decal );
					if(dinst)
						dinst->mPalette = this->getPalette();
				}
			}
		}
	}
}

void ShotgunProjectile::transmitHitsToServer()
{
	ShotgunFireEvent* event = new ShotgunFireEvent();
	event->datablock  = mDataBlock;
	event->source     = mSourceObject;
	event->sourceId   = mSourceObject->getNetIndex();
	event->sourceSlot = mSourceObjectSlot;
	event->muzzlePoint = mCurrPosition;
	event->muzzleVector = mCurrVelocity;

	U32 n = mHits.size();
	while(n--)
		event->hits.push_back(new ShotgunHit(*mHits[n]));

	GameConnection::getConnectionToServer()->postNetEvent(event);
}

//--------------------------------------------------------------------------

IMPLEMENT_CO_SERVEREVENT_V1(ShotgunFireEvent);

ShotgunFireEvent::ShotgunFireEvent()
{
	//mGuaranteeType = NetEvent::Guaranteed; // FIXME

	datablock = NULL;
	source = NULL;
	sourceId = -1;
	sourceSlot = -1;
}

ShotgunFireEvent::~ShotgunFireEvent()
{
	U32 n = hits.size();
	while(n--)
		delete hits[n];
}

void ShotgunFireEvent::pack(NetConnection* conn, BitStream* bstream)
{
	if(!bstream->writeFlag(datablock))
		return;

	// datablock
	bstream->writeRangedU32(datablock->getId(), DataBlockObjectIdFirst, DataBlockObjectIdLast);

	// source
	if(bstream->writeFlag(sourceId != -1))
		bstream->writeRangedU32(U32(sourceId), 0, NetConnection::MaxGhostCount);

	// source slot
	bstream->writeSignedInt(sourceSlot,4);

	// muzzle point & vector
	mathWrite(*bstream, muzzlePoint);
	mathWrite(*bstream, muzzleVector);

	// hits
	U32 n = hits.size();
	bstream->write(n);
	while(n--)
		hits[n]->pack(conn, bstream);
}

void ShotgunFireEvent::unpack(NetConnection* conn, BitStream* bstream)
{
	if(!bstream->readFlag())
		return;

	// datablock
	SimObject* ptr = NULL;
	U32 id = bstream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
	if(id != 0 && (ptr = Sim::findObject(id)))
		datablock = dynamic_cast<ShotgunProjectileData*>(ptr);

	// source
	if(bstream->readFlag())
	{
		sourceId = bstream->readRangedU32(0, NetConnection::MaxGhostCount);
		if(sourceId != -1)
		{
			NetObject* pObj = conn->resolveObjectFromGhostIndex(sourceId);
			source = dynamic_cast<ShapeBase*>(pObj);
		}
	}

	// source slot
	sourceSlot = bstream->readSignedInt(4);

	// muzzle point & vector
	mathRead(*bstream, &muzzlePoint);
	mathRead(*bstream, &muzzleVector);

	// hits
	U32 n; bstream->read(&n);
	while(n--)
	{
		ShotgunHit* newHit = new ShotgunHit();
		newHit->unpack(conn, bstream);
		hits.push_back(newHit);
	}
}

void ShotgunFireEvent::write(NetConnection* conn, BitStream* bstream)
{
	this->pack(conn, bstream);
}

void ShotgunFireEvent::process(NetConnection* conn)
{
	if(!datablock)
		return;

	if(!source)
		return;

	source->clientFiredShotgun(
		conn,
		sourceSlot,
		hits,
		datablock,
		muzzlePoint,
		muzzleVector
	);
}
