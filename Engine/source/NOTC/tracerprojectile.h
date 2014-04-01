// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#ifndef _TRACERPROJECTILE_H_
#define _TRACERPROJECTILE_H_

#ifndef _GAMEBASE_H_
#include "game/gameBase.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif
#ifndef _LIGHTMANAGER_H_
#include "sceneGraph/lightManager.h"
#endif
#ifndef _PLATFORMAUDIO_H_
#include "platform/platformAudio.h"
#endif
#ifndef _NETCONNECTION_H_
#include "sim/netConnection.h"
#endif

#include "game/fx/particleEmitter.h"
#include "game/fx/laserBeam.h"
#include "game/fx/fxLight.h"
#include "game/player.h"
#include "game/projectile.h"

class TracerProjectileData;
class ExplosionData;
class ShapeBase;
class TSShapeInstance;
class TSThread;

//--------------------------------------------------------------------------

class CreateTracerEvent : public NetEvent
{
  public:
	TracerProjectileData* datablock;
	U32 localId;      // local SimObject id of tracer projectile
	S32 sourceId;		// source of tracer, might not exist on client due to scoping
	S32 sourceSlot;   // source slot of tracer
	S32 targetId;     // SimObject id of projectile's target
	Point3F pos, vel;	// current position and velocity

   CreateTracerEvent();

   void pack(NetConnection*, BitStream* bstream);
   void write(NetConnection*, BitStream* bstream);
   void unpack(NetConnection*, BitStream* bstream);
   void process(NetConnection*);

   DECLARE_CONOBJECT(CreateTracerEvent);
};

//--------------------------------------------------------------------------

class TracerProjectileData : public ProjectileData
{
   typedef ProjectileData Parent;

protected:
   bool onAdd();

public:
	bool noFake;

	U32 energyDrain;
	Point3F posOffset;
	Point2F velOffset;

	TracerProjectileData();

	void packData(BitStream*);
	void unpackData(BitStream*);
	bool preload(bool server, char errorBuffer[256]);

	static void initPersistFields();
	DECLARE_CONOBJECT(TracerProjectileData);
};
DECLARE_CONSOLETYPE(TracerProjectileData)

//--------------------------------------------------------------------------

class TracerProjectile : public Projectile
{
   typedef Projectile Parent;

   TracerProjectileData* mDataBlock;

	struct FakeInfo
	{
		NetConnection* conn;
		U32            id;
	} mFake; // infos on a fake ghost this prj must replace

	bool mIsFake; // it this prj a fake ghost?

 public:
	TracerProjectile(bool onClient = true, bool isFake = false);
   ~TracerProjectile();

	// ConsoleObject...
   static void initPersistFields();
   static void consoleInit();

	// NetObject...
   U32  packUpdate(NetConnection* con, U32 mask, BitStream* stream);
   void unpackUpdate(NetConnection* con, BitStream* stream);

	// SimObject...
   bool onAdd();
   void onRemove();
	void onDeleteNotify(SimObject* obj);

	// SceneObject...
	bool prepRenderImage(SceneState*, const U32, const U32, const bool);

	// GameBase...
   void processTick(const Move*);
   void advanceTime(F32);
	void interpolateTick(F32 delta);
   bool onNewDataBlock(GameBaseData*);

	// TracerProjectile...
	void setFake(NetConnection* conn, U32 id) 
		{ mFake.conn = conn; mFake.id = id; };
   virtual void onCollision(const Point3F& p, const Point3F& n, SceneObject*);
   virtual void explode(const Point3F& p, const Point3F& n, const U32 collideType, bool nodecal = false);

   DECLARE_CONOBJECT(TracerProjectile);
};

#endif // _TRACERPROJECTILE_H_

#endif // BORQUE_NEEDS_PORTING