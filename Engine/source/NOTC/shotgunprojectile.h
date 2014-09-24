// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SHOTGUNPROJECTILE_H_
#define _SHOTGUNPROJECTILE_H_

#ifndef _PROJECTILE_H_
#include "T3D/projectile.h"
#endif
#ifndef _NETCONNECTION_H_
#include "sim/netConnection.h"
#endif

class ShapeBase;

//--------------------------------------------------------------------------

class ShotgunProjectileData : public ProjectileData
{
   typedef ProjectileData Parent;

protected:
   bool onAdd();

public:
	bool noFake;

	U32 energyDrain;

	U32 numBullets;
	U32 bulletDistMode;

	F32 range;

	F32 muzzleSpreadRadius;
	F32 referenceSpreadRadius;
	F32 referenceSpreadDistance;

   ShotgunProjectileData* tracer;
   S32 tracerId;

	ShotgunProjectileData();

	void packData(BitStream*);
	void unpackData(BitStream*);
	bool preload(bool server, String &errorStr);

	static void initPersistFields();
	DECLARE_CONOBJECT(ShotgunProjectileData);
};

//--------------------------------------------------------------------------

class ShotgunProjectileTracer : public Projectile
{
	typedef Projectile Parent;
	ShotgunProjectileData* mDataBlock;
	Point3F mImpactPos;
	bool mAtImpactPos;

 public:
	ShotgunProjectileTracer(const Point3F* impactPos = NULL);
	~ShotgunProjectileTracer();
	bool onAdd();
	void processTick(const Move*);
   void advanceTime(F32 dt);
   void interpolateTick(F32 delta); 
	bool onNewDataBlock(GameBaseData* dptr, bool reload);
	void simulate(F32 dt);
	DECLARE_CONOBJECT(ShotgunProjectileTracer);
};

//--------------------------------------------------------------------------

struct ShotgunHit
{
	SimObjectPtr<SceneObject> object;
	Point3F         objectPos;
	int             numImpacts;
	Point3F		    impactCenterVec; // relative to object position
	Vector<Point3F> impactVecs;      // relative to object position
	Vector<Point3F> impactNormals;

	ShotgunHit();
	ShotgunHit(const ShotgunHit& hit);
	~ShotgunHit();

	void pack(NetConnection* con, BitStream* stream);
	void unpack(NetConnection* con, BitStream* stream);
};

typedef Vector<ShotgunHit*> ShotgunHits;

class ShotgunProjectile : public Projectile
{
	typedef Projectile Parent;

 private:
	ShotgunProjectileData* mDataBlock;

	bool mFindHits;
	ShotgunHits mHits;
	NetConnection* mHitsSource;

 public:
	ShotgunProjectile(bool onClient = true, bool findHits = false);
	~ShotgunProjectile();

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

	// GameBase...
	void processTick(const Move*);
	void advanceTime(F32);
	void interpolateTick(F32 delta);
	bool onNewDataBlock(GameBaseData* dptr, bool reload);

	// ShotgunProjectile...
	void addHits(NetConnection* client, const ShotgunHits& hits);
	void findHits();
	void processHits();
	void serverProcessHits();
	void clientProcessHits();
	void transmitHitsToServer();

	DECLARE_CONOBJECT(ShotgunProjectile);
};

//--------------------------------------------------------------------------

class ShotgunFireEvent : public NetEvent
{
  public:
	typedef NetEvent Parent;

	ShotgunProjectileData* datablock;
	ShapeBase* source;
	S32 sourceId;    // source of shotgun blast
	S32 sourceSlot;  // source slot of shotgun blast
	ShotgunHits hits;
	Point3F muzzlePoint;
	Point3F muzzleVector;

	ShotgunFireEvent();
	~ShotgunFireEvent();

	void pack(NetConnection*, BitStream* bstream);
	void write(NetConnection*, BitStream* bstream);
	void unpack(NetConnection*, BitStream* bstream);
	void process(NetConnection*);

	DECLARE_CONOBJECT(ShotgunFireEvent);
};

#endif // _SHOTGUNPROJECTILE_H_

