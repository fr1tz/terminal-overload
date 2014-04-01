// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#include "dgl/dgl.h"
#include "sceneGraph/sceneState.h"
#include "sceneGraph/sceneGraph.h"
#include "console/consoleTypes.h"
#include "console/typeValidators.h"
#include "audio/audioDataBlock.h"
#include "core/bitStream.h"
#include "game/fx/explosion.h"
#include "game/shapeBase.h"
#include "game/player.h"
#include "ts/tsShapeInstance.h"
#include "game/nortdisc.h"
#include "audio/audio.h"
#include "math/mathUtils.h"
#include "math/mathIO.h"
#include "sim/netConnection.h"
#include "game/fx/particleEngine.h"
#include "game/fx/laserBeam.h"
#include "game/fx/fxLight.h"
#include "game/deflector.h"
#include "sim/decalManager.h"
#include "game/gameConnection.h"

IMPLEMENT_CO_DATABLOCK_V1(NortDiscData);
IMPLEMENT_CO_NETOBJECT_V1(NortDisc);

//--------------------------------------------------------------------------

//#define NORTDISC_DEBUG

#ifdef TORQUE_DEBUG
# ifdef NORTDISC_DEBUG
#  define DEBUG(x) (Con::errorf x)
# else
#  define DEBUG(x)
# endif
#else
# define DEBUG(x)
#endif

//--------------------------------------------------------------------------

namespace {
	MRandomLCG sgRandom(0x1);
}

//--------------------------------------------------------------------------

IMPLEMENT_CO_CLIENTEVENT_V1(CreateExplosionEvent);

CreateExplosionEvent::CreateExplosionEvent()
{
	mGuaranteeType = Guaranteed;

	mData = NULL;
}

CreateExplosionEvent::CreateExplosionEvent(ExplosionData* data,
	const Point3F& p, const Point3F &n)
{
	mData = data;
	mPos = p;
	mNorm = n;
}

void CreateExplosionEvent::pack(NetConnection* conn, BitStream* bstream)
{
	if(bstream->writeFlag(mData))
	{
		bstream->writeRangedU32(mData->getId(), DataBlockObjectIdFirst, DataBlockObjectIdLast);
		mathWrite(*bstream, mPos);
		mathWrite(*bstream, mNorm);
	}
}

void CreateExplosionEvent::unpack(NetConnection* conn, BitStream* bstream)
{
	if(bstream->readFlag())
	{
		SimObject* ptr = NULL;
		U32 id = bstream->readRangedU32(DataBlockObjectIdFirst, DataBlockObjectIdLast);
		if(id != 0 && (ptr = Sim::findObject(id)))
			mData = dynamic_cast<ExplosionData*>(ptr);

		mathRead(*bstream, &mPos);
		mathRead(*bstream, &mNorm);
	}
}

void CreateExplosionEvent::write(NetConnection* conn, BitStream* bstream)
{
	this->pack(conn,bstream);
}

void CreateExplosionEvent::process(NetConnection* conn)
{
	if(!mData)
		return;

	Explosion* pExplosion = new Explosion;
	pExplosion->onNewDataBlock(mData);
   if( pExplosion )
   {
      MatrixF xform(true);
      xform.setPosition(mPos);
      pExplosion->setTransform(xform);
      pExplosion->setInitialState(mPos, mNorm);
      if (pExplosion->registerObject() == false)
      {
         Con::errorf(ConsoleLogEntry::General, "CreateExplosionEvent(): couldn't register explosion (%s)",
                     mData->getName() );
         delete pExplosion;
         pExplosion = NULL;
      }
   }
}

//--------------------------------------------------------------------------

//IMPLEMENT_CO_SERVEREVENT_V1(NortDiscHitEvent);
//
//NortDiscHitEvent::NortDiscHitEvent()
//{
//	mGuaranteeType = Guaranteed;
//
//	mObjId = mDiscId = -1;
//	mDeflected = false;
//}
//
//
//NortDiscHitEvent::NortDiscHitEvent(const RayInfo& rInfo, U32 objId, 
//						U32 discId, const Point3F& vec, bool deflected)
//{
//	mInfo.point  = rInfo.point;
//	mInfo.normal = rInfo.normal;
//	mInfo.t      = rInfo.t;
//	mObjId = objId;
//	mDiscId = discId;
//	mVec = vec;
//	mDeflected = deflected;
//}
//
//void NortDiscHitEvent::pack(NetConnection* conn, BitStream* bstream)
//{
//	mathWrite(*bstream, mInfo.point);
//	mathWrite(*bstream, mInfo.normal);
//	bstream->write(mInfo.t);
//	bstream->writeRangedU32(mObjId, 0, NetConnection::MaxGhostCount);
//	bstream->writeRangedU32(mDiscId, 0, NetConnection::MaxGhostCount);
//	mathWrite(*bstream, mVec);
//	bstream->writeFlag(mDeflected);
//}
//
//void NortDiscHitEvent::unpack(NetConnection* conn, BitStream* bstream)
//{
//	mathRead(*bstream, &mInfo.point);
//	mathRead(*bstream, &mInfo.normal);
//	bstream->read(&mInfo.t);
//	mObjId  = bstream->readRangedU32(0, NetConnection::MaxGhostCount);
//	mDiscId = bstream->readRangedU32(0, NetConnection::MaxGhostCount);
//	mathRead(*bstream, &mVec);
//	mDeflected = bstream->readFlag();
//}
//
//void NortDiscHitEvent::write(NetConnection* conn, BitStream* bstream)
//{
//	this->pack(conn,bstream);
//}
//
//void NortDiscHitEvent::process(NetConnection* conn)
//{
//	// TODO: implement more anti-cheating checks
//
//	GameConnection* gameconn = dynamic_cast<GameConnection*>(conn);
//	if(!gameconn) return;
//
//	NortDisc* disc = NULL;
//	ShapeBase* shape = NULL;
//
//	NetObject* netObj = conn->resolveObjectFromGhostIndex((S32)mObjId);
//	shape = dynamic_cast<ShapeBase*>(netObj);
//	if(!shape) return;
//
//	netObj = conn->resolveObjectFromGhostIndex((S32)mDiscId);
//	disc = dynamic_cast<NortDisc*>(netObj);
//	if(!disc) return;
//
//	mInfo.object = shape;
//
//	// a client is only allowed "to speak"
//	// for his own control object...
//	if( shape != gameconn->getControlObject() )
//		return;		
//
//	if(mDeflected)
//	{
//		// we currently trust our clients 100%...
//		DEBUG(("NortDiscHitEvent: disc has been deflected"));
//	}
//	else
//	{
//		DEBUG(("NortDiscHitEvent: disc has not been deflected"));
//	}
//
//	disc->processNortDiscHitEvent(conn,shape,mInfo,mVec,mDeflected);
//}

//--------------------------------------------------------------------------
//
NortDiscData::NortDiscData()
{
	maxVelocity = muzzleVelocity;
	acceleration = 0;
	startVertical = false;
}

//--------------------------------------------------------------------------

IMPLEMENT_CONSOLETYPE(NortDiscData)
IMPLEMENT_GETDATATYPE(NortDiscData)
IMPLEMENT_SETDATATYPE(NortDiscData)

void NortDiscData::initPersistFields()
{
   Parent::initPersistFields();

   addNamedFieldV(maxVelocity, TypeF32, NortDiscData, new FRangeValidator(0, 10000));
   addNamedFieldV(acceleration, TypeF32, NortDiscData, new FRangeValidator(0, 10000));

   addNamedField(startVertical, TypeBool, NortDiscData);
}

//--------------------------------------------------------------------------

bool NortDiscData::onAdd()
{
   if(!Parent::onAdd())
      return false;

   return true;
}


bool NortDiscData::preload(bool server, char errorBuffer[256])
{
   if (Parent::preload(server, errorBuffer) == false)
      return false;

   return true;
}

//--------------------------------------------------------------------------

void NortDiscData::packData(BitStream* stream)
{
   Parent::packData(stream);

   stream->write(maxVelocity);
   stream->write(acceleration);

   stream->writeFlag(startVertical);
}

void NortDiscData::unpackData(BitStream* stream)
{
   Parent::unpackData(stream);

   stream->read(&maxVelocity);
   stream->read(&acceleration);

   startVertical = stream->readFlag();
}


//--------------------------------------------------------------------------

NortDisc::NortDisc()
{
	mState = Attacking;

	mInitialTarget = NULL;
	mInitialTargetExists = false;

	mSpinTargetPos.set(0, 0, 0);
}

NortDisc::~NortDisc()
{

}

void NortDisc::onDeleteNotify(SimObject* obj)
{
	Parent::onDeleteNotify(obj);

	if(obj == mInitialTarget)
	{
		mInitialTargetExists = false;
		this->onTargetLost();
	}
}

//--------------------------------------------------------------------------

void NortDisc::initPersistFields()
{
   Parent::initPersistFields();
}

void NortDisc::consoleInit()
{
	Parent::consoleInit();

	Con::setIntVariable("$NortDisc::Attacking",Attacking);
	Con::setIntVariable("$NortDisc::Returning",Returning);
	Con::setIntVariable("$NortDisc::Deflected",Deflected);
}


//--------------------------------------------------------------------------

bool NortDisc::onAdd()
{
   if(!Parent::onAdd())
      return false;

	// disc starts parallel to horizon by default...
	MatrixF mat = MathUtils::createOrientFromDir(mCurrVelocity);
	mat.setPosition(mCurrPosition);
	this->setTransform(mat);

	if(mDataBlock->startVertical)
	{
		MatrixF rot(EulerF(0, M_PI_F / 2, 0));
		mat.mul(mat, rot);
		this->setTransform(mat);
	}

	// pretty big (currently hardcoded) bounding box
	// to make targeting a disc possible...
	mObjBox.min = Point3F(-2,-2,-2);
	mObjBox.max = Point3F(2,2,2);
	resetWorldBox();
      
   return true;
}


void NortDisc::onRemove()
{

   Parent::onRemove();
}


bool NortDisc::onNewDataBlock(GameBaseData* dptr)
{
   mDataBlock = dynamic_cast<NortDiscData*>(dptr);
   if (!mDataBlock || !Parent::onNewDataBlock(dptr))
      return false;

   return true;
}

//----------------------------------------------------------------------------

bool NortDisc::castRay(const Point3F &start, const Point3F &end, RayInfo* info)
{
   // Collision disabled when hidden or deflected.
   if(mCollisionsDisabled || mHidden || mState == Deflected)
      return false;

   // Collide against bounding box. Need at least this for the editor.
   F32 st,et,fst = 0,fet = 1;
   F32 *bmin = &mObjBox.min.x;
   F32 *bmax = &mObjBox.max.x;
   F32 const *si = &start.x;
   F32 const *ei = &end.x;

   for (int i = 0; i < 3; i++) {
      if (*si < *ei) {
         if (*si > *bmax || *ei < *bmin)
            return false;
         F32 di = *ei - *si;
         st = (*si < *bmin)? (*bmin - *si) / di: 0;
         et = (*ei > *bmax)? (*bmax - *si) / di: 1;
      }
      else {
         if (*ei > *bmax || *si < *bmin)
            return false;
         F32 di = *ei - *si;
         st = (*si > *bmax)? (*bmax - *si) / di: 0;
         et = (*ei < *bmin)? (*bmin - *si) / di: 1;
      }
      if (st > fst) fst = st;
      if (et < fet) fet = et;
      if (fet < fst)
         return false;
      bmin++; bmax++;
      si++; ei++;
   }

   info->normal = start - end;
   info->normal.normalizeSafe();
   getTransform().mulV( info->normal );

   info->t = fst;
   info->object = this;
   info->point.interpolate(start,end,fst);
   info->material = 0;
   return true;
}

//----------------------------------------------------------------------------

class ObjectDeleteEvent : public SimEvent
{
public:
   void process(SimObject *obj)
   {
      obj->deleteObject();
   }
};

void NortDisc::processTick(const Move* move)
{
   //Parent::processTick(move);

   mCurrTick++;

   // See if we can get out of here the easy way ...
	if( isServerObject() && mCurrTick >= mDataBlock->lifetime )
	{
      deleteObject();
      return;
	}

	// since deflected discs are harmless eyecandy, they just linger 
	// on the server waiting for the end of their lifetime to come...
	if(isServerObject() && mState == Deflected)
		return;

	//
	// ... otherwise, we have to do some simulation work...
	//


	if(mState == Attacking && mInitialTargetExists)		
	{
		U32 targetType = mInitialTarget->getType();
		if(targetType & ProjectileObjectType)
		{
			if(((NortDisc*)mInitialTarget)->mState == Deflected)
				this->onTargetLost();
		}
		else if(targetType & ShapeBaseObjectType)
		{
			if(((ShapeBase*)mInitialTarget)->getDamageState() != ShapeBase::Enabled)
				this->onTargetLost();
		}
	}

	if(mHidden)
		return;

	F32 timeLeft;
	RayInfo rInfo;
	Point3F oldPosition;
	Point3F newPosition;

	oldPosition = mCurrPosition;

	// acceleration...
	F32 currSpeed = mCurrVelocity.len();
	F32 newSpeed = currSpeed + mDataBlock->acceleration;
	newSpeed = mClampF(newSpeed, 0, mDataBlock->maxVelocity);
	mCurrVelocity.normalize();
	mCurrVelocity *= newSpeed;

	// ballistic?...
	if(mDataBlock->isBallistic)
	  mCurrVelocity.z -= 9.81 * mDataBlock->gravityMod * (F32(TickMs) / 1000.0f);

	F32 oldYaw, oldPitch;
	F32 newYaw, newPitch;

	MathUtils::getAnglesFromVector(mCurrVelocity,oldYaw,oldPitch);

	// target-tracking?
	if( mState == Deflected )
	{
		// spin around...
		this->updateSpin();
	}
	else if( mTarget && mDataBlock->maxTrackingAbility > 0 )
		updateTargetTracking();

	MathUtils::getAnglesFromVector(mCurrVelocity,newYaw,newPitch);
	//Con::errorf("old: %f %f \t new: %f %f",oldYaw,oldPitch,newYaw,newPitch);

	newPosition = oldPosition + mCurrVelocity * (F32(TickMs) / 1000.0f);

	timeLeft = 1.0;

	//
	// check for bounce, collision, etc...
	//

	// don't collide with ourself...
	this->disableCollision();

	// never collide with source object when attacking...
	bool noCollisionWithSource = mSourceObject && mState == Attacking;
	if(noCollisionWithSource)
		mSourceObject->disableCollision();

	// never collide with initial target when returning or deflected...
	bool noCollisionWithInitialTarget = mInitialTargetExists && mState != Attacking;
	if(noCollisionWithInitialTarget)
		mInitialTarget->disableCollision();

   // Determine if the projectile is going to hit any object between the previous
   // position and the new position. This code is executed both on the server
   // and on the client (for prediction purposes). It is possible that the server
   // will have registered a collision while the client prediction has not. If this
   // happens the client will be corrected in the next packet update.
	bool collision = this->findCollision(oldPosition, newPosition, &rInfo);
	if(collision)
	{
		mLastCollisionPos = rInfo.point;

		mTraveledDistance += (rInfo.point-oldPosition).len();

		// returned to source?
		if(mState == Returning && rInfo.object == mTarget)
		{
			this->enableCollision();

			if(noCollisionWithSource)
				mSourceObject->enableCollision();

			if(noCollisionWithInitialTarget)
				mInitialTarget->enableCollision();

			if(isServerObject())
			{
				DEBUG(("NortDisc: server: disc retourned to source @ %u",Platform::getVirtualMilliseconds()));
				this->deleteObject();
			}
			else
			{
				DEBUG(("NortDisc: client: disc retourned to source @ %u",Platform::getVirtualMilliseconds()));
				mHidden = true;
			}

			return;
		}

		bool bounce = true;
		bool bounceExplosion = false;

		if( rInfo.object->getType() & csmStaticCollisionMask )
			bounceExplosion = true;

		// check if we hit a ShapeBase...
		ShapeBase* hitShape = NULL;
		if(rInfo.object->getType() & ShapeBaseObjectType)
			hitShape = (ShapeBase*)rInfo.object;

		// check if we hit another disc...
		NortDisc* hitDisc = NULL;
		if(rInfo.object->getType() & ProjectileObjectType)
			hitDisc = dynamic_cast<NortDisc*>(rInfo.object);

		// if we hit another disc...
		if(hitDisc)
		{
			this->hit(hitDisc, rInfo);
			bounce = false; // this->hit() already took care of our bouncing...
		}
		else if(hitShape) // hit shape...
		{
			if(isClientObject() && mState == Deflected)
			{
				// create bounce explosion...
				bounceExplosion = true;
			}
			else
			{
				this->hit(hitShape, rInfo);
				bounce = false; // this->hit() already took care of our bouncing...
			}
		}

		if( mDataBlock->numBounces != 0 && mBounceCount >= mDataBlock->numBounces )
		{
			this->explode(rInfo.point, rInfo.normal, rInfo.object->getType(), true);

			MatrixF xform(true);
			xform.setColumn(3, rInfo.point);
			setTransform(xform);
			mCurrPosition    = rInfo.point;
			mCurrVelocity    = Point3F(0, 0, 0);
		}
		else if(bounce)
		{
			// let's bounce...
			newPosition = this->bounce(rInfo,mCurrVelocity,bounceExplosion);

			//
			if(mState == Deflected)
			{
				Point3F randVec;
				randVec.x = sgRandom.randF( -1.0, 1.0 );
				randVec.y = sgRandom.randF( -1.0, 1.0 );
				randVec.z = sgRandom.randF(  0.0, 1.0 );
				randVec.normalize();
				randVec *= 10;

				mSpinTargetPos = mCurrPosition + randVec;
			}
		}
	}
	else // no collision...
	{
		mTraveledDistance += (newPosition-oldPosition).len();

		// check if we've missed our target...
		if(mTarget)
		{
			if(this->isServerObject() && this->missedObject(mTarget, oldPosition, newPosition))
				Con::executef(mDataBlock, 2, "onMissedTarget", scriptThis());
		}
	}

	this->enableCollision();

	if(noCollisionWithSource)
		mSourceObject->enableCollision();

	if(noCollisionWithInitialTarget)
		mInitialTarget->enableCollision();

   mCurrDeltaBase = newPosition;
	mCurrBackDelta = mCurrPosition - newPosition;

   if(isClientObject())
   {
	   // if this is the first particle emission, start the particles \
      // at the creation point to make sure the player sees the particles beginning at the \
      // gun's muzzle point... -mg
		if( mEmissionCount == 0 )
			emitParticles(mInitialPosition, newPosition, mCurrVelocity, TickMs);
		else
			emitParticles(mCurrPosition, newPosition, mCurrVelocity, TickMs);

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
   }

   mCurrPosition = newPosition;

	//
	// compute new transformation matrix...
	//

	if(isClientObject())
	{

		enum Roll { Left, Right } rollDir;

		MatrixF mat = this->getTransform();

		Point3F xv,yv,zv;

		yv = mCurrVelocity; yv.normalize();
		mat.getColumn(0,&xv); xv.normalize();

		F32 xv_yaw,xv_pitch;
		MathUtils::getAnglesFromVector(xv,xv_yaw,xv_pitch);

		//DEBUG(("NortDisc: xv_pitch: %f",xv_pitch));

		F32 roll = 0;
		F32 diff = mFabs(newYaw-oldYaw);
		if(diff < 0.05)
		{
			//DEBUG(("NortDisc: steered straight ahead"));

			// roll back to horizon...
			if(xv_pitch > 0)
				rollDir = Right;
			else
				rollDir = Left;

			F32 pitchAbs = mFabs(xv_pitch);
			if(pitchAbs < 0.1)
				roll = pitchAbs;
			else
				roll = 0.1;
		}
		else
		{
			if(newYaw - oldYaw > 0)
			{
				//DEBUG(("NortDisc: steered right"));
				rollDir = Right;
			}
			else
			{
				//DEBUG(("NortDisc: steered left"));
				rollDir = Left;
			}

			roll = diff;
		}

		if(rollDir == Left)
		{
			//DEBUG(("NortDisc: rolling left"));
			xv_pitch += roll;
		}
		else
		{
			//DEBUG(("NortDisc: rolling right"));
			xv_pitch -= roll;
		}

		MathUtils::getVectorFromAngles(xv,xv_yaw,xv_pitch);

		mCross(xv,yv,&zv); zv.normalize();
		mCross(yv,zv,&xv); xv.normalize();

		mat.setColumn(0,xv);
		mat.setColumn(1,yv);
		mat.setColumn(2,zv);
		mat.setPosition(mCurrPosition);

		this->setTransform(mat);

	}
	else // on the server
	{
		// server only cares about position...
		MatrixF xform(true);
		xform.setColumn(3, mCurrPosition);
		setTransform(xform);
	}
}

//--------------------------------------------------------------------------

bool
NortDisc::findCollision(const Point3F &start, const Point3F &end, RayInfo* info)
{
	U32 colMask = csmStaticCollisionMask | csmDynamicCollisionMask;

	if(mState == Attacking)
		colMask |= ProjectileObjectType;

	bool collision = getContainer()->castRay(start, end, colMask, info);
	if(collision)
	{
		/*
		if(info->object->getType() & DeflectorObjectType)
		{
			Deflector* deflector = (Deflector*)info->object;
			DeflectorData* deflectorData = (DeflectorData*)deflector->getDataBlock();

			if(!deflector->isActive() || mDataBlock->penetrateDeflectorLevel >= deflectorData->level)
			{
				DEBUG(("%s: ignoring deflector and trying again...", isGhost() ? "CLNT" : "SRVR"));

				deflector->disableCollision();
				collision = findCollision(start, end, info);
				deflector->enableCollision();
			}
		}
		else*/ if(info->object->getType() & ProjectileObjectType)
		{
			Projectile* prj = (Projectile*)info->object;

			if(prj != mInitialTarget)
			{
				DEBUG(("%s: ignoring non-target disc and trying again...", isGhost() ? "CLNT" : "SRVR"));

				prj->disableCollision();
				collision = findCollision(start, end, info);
				prj->enableCollision();
			}
		}
	}

	return collision;
}

void
NortDisc::updateSpin()
{
	mCurrTrackingAbility++;
	if(mCurrTrackingAbility >= 20)
	{
		mCurrTrackingAbility = 10;

		Point3F randVec;
		randVec.x = sgRandom.randF( -1.0, 1.0 );
		randVec.y = sgRandom.randF( -1.0, 1.0 );
		randVec.z = sgRandom.randF( -1.0, 1.0 );
		randVec.normalize();
		randVec *= 10;

		mSpinTargetPos = mCurrPosition + randVec;
	}

	Point3F targetPos, targetDir;
	F32 speed = mCurrVelocity.len();

	targetPos = mSpinTargetPos;
	targetDir = targetPos - mCurrPosition;
	targetDir.normalize();
	targetDir *= mCurrTrackingAbility;
	targetDir += mCurrVelocity;
	targetDir.normalize();

	mCurrVelocity = targetDir;
	mCurrVelocity *= speed; 
}

void
NortDisc::setTarget(GameBase* target)
{
	if(target)
	{
		if(mInitialTarget == NULL)
		{
			mInitialTarget = target;
			mInitialTargetExists = true;
			this->deleteNotify(mInitialTarget);
		}
	}

	Parent::setTarget(target);
}

Point3F
NortDisc::bounce(const RayInfo& rInfo, const Point3F& vec, bool bounceExp)
{
	if( isServerObject() )
	{
		setMaskBits(MovementMask);

		// no need to add new bouncePoints if the important ones have been sent already...
		if( !mBouncePointsSent && mNumBouncePoints < 10 )
		{
			mNumBouncePoints++;
			mBouncePoint[mNumBouncePoints-1].pos = rInfo.point;
			mBouncePoint[mNumBouncePoints-1].norm = rInfo.normal;
			mBouncePoint[mNumBouncePoints-1].decal = (
				!(rInfo.object->getType() & Projectile::csmDynamicCollisionMask)
				&& (rInfo.object->getType() & Projectile::csmStaticCollisionMask)
			);
		}
	}
	else
	{
		addLaserTrailNode(rInfo.point, false);

		// create bounce explosion...
		if(bounceExp)
			this->createBounceExplosion(rInfo.point, rInfo.normal);

		// NortDiscs create oriented decals when bouncing...
		if(mDataBlock->decalCount > 0
		&& !(rInfo.object->getType() & Projectile::csmDynamicCollisionMask)
		&& (rInfo.object->getType() & Projectile::csmStaticCollisionMask))
		{
			// randomly choose a decal between 0 and (decal count - 1)
			U32 idx = (U32)(mCeil(mDataBlock->decalCount * Platform::getRandom()) - 1.0f);

			// this should never choose a NULL idx, but check anyway
			if(mDataBlock->decals[idx] != NULL)
			{
				DecalManager *decalMngr = gClientSceneGraph->getCurrentDecalManager();
				if(decalMngr)
					decalMngr->addDecal(rInfo.point, vec, rInfo.normal, mDataBlock->decals[idx]);
			}
		}
	}

	// reset mCurrTrackingAbility to zero...
	mCurrTrackingAbility = 0;

	// reflect our velocity around the normal...
	Point3F bounceVel = vec - rInfo.normal * (mDot( vec, rInfo.normal ) * 2.0);
	mCurrVelocity = bounceVel;

	// Add in surface friction...
	Point3F tangent = bounceVel - rInfo.normal * mDot(bounceVel, rInfo.normal);
	mCurrVelocity  -= tangent * mDataBlock->bounceFriction;

	// Now, take elasticity into account for modulating the speed of the disc
	mCurrVelocity *= mDataBlock->bounceElasticity;

	U32 timeLeft = 1.0 * (1.0 - rInfo.t);
	Point3F oldPosition = rInfo.point + rInfo.normal * 0.05;
	Point3F newPosition = oldPosition + (mCurrVelocity * ((timeLeft/1000.0) * TickMs));

	mBounceCount++;

	mTraveledDistance += (newPosition-oldPosition).len();

	return newPosition;
}

void
NortDisc::createExplosion(const Point3F& p, const Point3F& n, ExplosionType type)
{
	if(isServerObject()) return;

	ExplosionData* data = NULL;

	if      ( type == StandardExplosion && mDataBlock->explosion )
		data = mDataBlock->explosion;

	else if ( type == HitEnemyExplosion && mDataBlock->hitEnemyExplosion )
		data = mDataBlock->hitEnemyExplosion;

	else if ( type == NearEnemyExplosion && mDataBlock->nearEnemyExplosion )
		data = mDataBlock->nearEnemyExplosion;

	else if ( type == HitTeammateExplosion && mDataBlock->hitTeammateExplosion )
		data = mDataBlock->hitTeammateExplosion;

	else if ( type == HitDeflectorExplosion && mDataBlock->hitDeflectorExplosion )
		data = mDataBlock->hitDeflectorExplosion;

	else if ( type == BounceExplosion && mDataBlock->bounceExplosion )
		data = mDataBlock->bounceExplosion;

	Explosion* pExplosion = new Explosion;
	pExplosion->onNewDataBlock(data);
   if( pExplosion )
   {
      MatrixF xform(true);
      xform.setPosition(p);
      pExplosion->setTransform(xform);
      pExplosion->setInitialState(p, n);
      if (pExplosion->registerObject() == false)
      {
         Con::errorf(ConsoleLogEntry::General, "NortDisc(%s)::createExplosion: couldn't register explosion",
                     mDataBlock->getName() );
         delete pExplosion;
         pExplosion = NULL;
      }
   }

}


//--------------------------------------------------------------------------
U32 NortDisc::packUpdate(NetConnection* con, U32 mask, BitStream* stream)
{
	U32 retMask = Parent::packUpdate(con, mask, stream);

	if(stream->writeFlag(mask & MovementMask))
	{
		stream->writeInt(mState,2);
	}

	if(stream->writeFlag(mask & TargetMask))
	{
		if(mInitialTargetExists)
		{
			S32 ghostIndex = con->getGhostIndex(mInitialTarget);
			if(stream->writeFlag(ghostIndex != -1))
				stream->writeRangedU32(U32(ghostIndex), 0, NetConnection::MaxGhostCount);
		}
		else
			stream->writeFlag(false);	
	}

	return retMask;
}

void NortDisc::unpackUpdate(NetConnection* con, BitStream* stream)
{
   Parent::unpackUpdate(con, stream);

	// movement mask
	if(stream->readFlag())
	{
		mState = (State)stream->readInt(2);

		if(mState == Deflected)
			this->deflected(mCurrVelocity);
	}

	// target mask...
	if(stream->readFlag())
	{
		if(stream->readFlag()) // have initial target?
		{
			S32 ghostIndex = stream->readRangedU32(0, NetConnection::MaxGhostCount);

			NetObject* pObject = con->resolveGhost(ghostIndex);
			if( pObject != NULL )
			{
				mInitialTarget = dynamic_cast<GameBase*>(pObject);
				mInitialTargetExists = true;
				deleteNotify(mInitialTarget);
			}
		}
	}
}

//--------------------------------------------------------------------------

void
NortDisc::hit(GameBase* obj, const RayInfo& rInfo)
{
	mTraveledDistance += (rInfo.point-mCurrPosition).len();

	this->onCollision(rInfo.point,rInfo.normal,obj);

	if(obj == mTarget)
	{			
		DEBUG(("%s: hit target!", isGhost() ? "CLNT" : "SRVR"));
		if(isServerObject())
			Con::executef(mDataBlock, 2, "onHitTarget", scriptThis());
	}
	else
	{
		// re-set our target...
		this->setTarget(mTarget);
	}


	bool bounce = true;

	// don't bounce if the target was a ShapeBase and we killed it...
	if(obj && obj->getType() & ShapeBaseObjectType)
	{
		ShapeBase* shape = (ShapeBase*)obj;
		ShapeBase::DamageState state = shape->getDamageState();
		if( state  == ShapeBase::Disabled || state == ShapeBase::Destroyed )
		{
			mCurrTrackingAbility = 0; 
			bounce = false;
		}
	}

	if(bounce)
		mCurrPosition = this->bounce(rInfo, mCurrVelocity);

	setMaskBits(MovementMask);

	//
	// eyecandy stuff:
	//

	if(isClientObject())
	{
		ExplosionType expType;

		if(obj->getTeamId() != mTeamId)
			expType = HitEnemyExplosion;
		else
			expType = HitTeammateExplosion;

		this->createExplosion(rInfo.point,rInfo.normal,expType);
	}
}

void
NortDisc::deflected(const Point3F& newVel)
{
	if(isServerObject())
		Con::executef(mDataBlock, 2, "onDeflected", scriptThis());

	mCurrVelocity = newVel;
	mState = Deflected;
	this->setTarget(NULL);
	setMaskBits(MovementMask);

	//
	// eyecandy stuff...
	//

	if(isClientObject())
	{
		mHidden = false;

		Point3F normal = newVel;
		normal.normalize();
		ExplosionType expType = HitDeflectorExplosion;
		this->createExplosion(mCurrPosition, normal, expType);
	}
}

void
NortDisc::stopAttacking(U32 targetType)
{
	if(mSourceObject)
	{
		// return to source...
		this->setTarget(mSourceObject);
		mState = Returning;
	}
	else
	{
		// clear target...
		this->setTarget(NULL);
	}

	setMaskBits(MovementMask);
}

//void
//NortDisc::processNortDiscHitEvent(NetConnection* conn, GameBase* obj,
//					const RayInfo& rInfo, const Point3F& vec, bool deflected)
//{
//	mTraveledDistance += (rInfo.point-mCurrPosition).len();
//
//	// don't do the onCollision script call if we've been deflected...
//	if(isServerObject() && !deflected && obj)
//		this->onCollision(rInfo.point,rInfo.normal,obj);
//
//	if(deflected)
//	{
//		Con::executef(mDataBlock, 2, "onDeflected", scriptThis());
//
//		// clear target...
//		this->setTarget(NULL);
//
//		mState = Deflected;
//	}
//	else if(obj == mTarget)
//	{			
//		Con::executef(mDataBlock, 2, "onHitTarget", scriptThis());
//		if(mSourceObject)
//		{
//			// return to source...
//			this->setTarget(mSourceObject);
//		}
//		else
//		{
//			// clear target...
//			this->setTarget(NULL);
//		}
//
//		mState = Returning;
//	}
//	else
//	{
//		// re-set our target...
//		this->setTarget(mTarget);
//	}
//
//
//	bool bounce = true;
//
//	// don't bounce if the target was a ShapeBase and we killed it...
//	if(obj && obj->getType() & ShapeBaseObjectType)
//	{
//		ShapeBase* shape = (ShapeBase*)obj;
//		ShapeBase::DamageState state = shape->getDamageState();
//		if( state  == ShapeBase::Disabled || state == ShapeBase::Destroyed )
//		{
//			mCurrTrackingAbility = 0; 
//			bounce = false;
//		}
//	}
//
//	if(bounce)
//		mCurrPosition = this->bounce(rInfo,vec);
//
//	setMaskBits(MovementMask);
//
//	//
//	// eyecandy stuff:
//	//
//
//	if(isClientObject() && obj && obj->getType() & ProjectileObjectType)
//	{
//		ExplosionType expType;
//		if(deflected)
//			expType = HitDeflectorExplosion;
//		else
//			if(obj->getTeamId() != mTeamId)
//				expType = HitEnemyExplosion;
//			else
//				expType = HitTeammateExplosion;
//
//		this->createExplosion(rInfo.point,rInfo.normal,expType);
//	}
//	else if(isServerObject())
//	{
//		ExplosionData* expData = NULL;
//		if(deflected)
//			expData = mDataBlock->hitDeflectorExplosion;
//		else
//			if(obj && obj->getTeamId() != mTeamId)
//				expData = mDataBlock->hitEnemyExplosion;
//			else
//				expData = mDataBlock->hitTeammateExplosion;
//
//		if(expData)
//		{
//			SimGroup* clientGroup = Sim::getClientGroup();
//			for(SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++)
//			{
//				NetConnection* nc = static_cast<NetConnection*>(*itr);
//				if(nc == conn) 
//					continue;
//
//				CreateExplosionEvent* event = new CreateExplosionEvent(expData,rInfo.point,rInfo.normal);
//				nc->postNetEvent(event);
//			}
//		}
//	}
//}

//--------------------------------------------------------------------------

ConsoleMethod(NortDisc, state, S32, 2, 2, "")
{
   return object->state();
}

ConsoleMethod(NortDisc, setDeflected, void, 3, 3, "")
{
	Point3F vec;
	dSscanf(argv[3], "%f %f %f", &vec.x, &vec.y, &vec.z);
	object->deflected(vec);
}

ConsoleMethod(NortDisc, stopAttacking, void, 2, 2, "")
{
	object->stopAttacking(ShapeBaseObjectType);
}

ConsoleFunction( createExplosionOnClient, bool, 5, 5, "(NetConnection conn, DataBlock datablock, Point3F pos, Point3F norm)")
{
	NetConnection* nc = NULL;
	if(Sim::findObject(argv[1], nc) == false)
	{
		Con::warnf(ConsoleLogEntry::General, "createExplosionOnClient: couldn't find object: %s", argv[1]);
		return false;
	}

	ExplosionData* datablock = NULL;
	if(Sim::findObject(argv[2], datablock) == false)
	{
		Con::warnf(ConsoleLogEntry::General, "createExplosionOnClient: couldn't find object: %s", argv[2]);
		return false;
	}

	Point3F pos, norm;

	dSscanf(argv[3], "%f %f %f", &pos.x, &pos.y, &pos.z);
	dSscanf(argv[4], "%f %f %f", &norm.x, &norm.y, &norm.z);

	if(datablock)
	{
		CreateExplosionEvent* event = new CreateExplosionEvent(datablock,pos,norm);
		nc->postNetEvent(event);
	}

	return true;
}

ConsoleFunction( createExplosionOnClients, bool, 4, 4, "(DataBlock datablock, Point3F pos, Point3F norm)")
{
   ExplosionData* datablock = NULL;
	if(Sim::findObject(argv[1], datablock) == false)
	{
      Con::warnf(ConsoleLogEntry::General, "createExplosionOnClients: couldn't find object: %s", argv[1]);
      return false;
   }

   Point3F pos, norm;

   dSscanf(argv[2], "%f %f %f", &pos.x, &pos.y, &pos.z);
	dSscanf(argv[3], "%f %f %f", &norm.x, &norm.y, &norm.z);

	if(datablock)
	{
		SimGroup* clientGroup = Sim::getClientGroup();
		for(SimGroup::iterator itr = clientGroup->begin(); itr != clientGroup->end(); itr++)
		{
			NetConnection* nc = static_cast<NetConnection*>(*itr);
			CreateExplosionEvent* event = new CreateExplosionEvent(datablock,pos,norm);
			nc->postNetEvent(event);
		}
	}

	return true;
}

#endif // BORQUE_NEEDS_PORTING