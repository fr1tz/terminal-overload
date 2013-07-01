// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ETHERFORM_H_
#define _ETHERFORM_H_

#ifndef _SHAPEBASE_H_
#include "T3D/shapeBase.h"
#endif

#ifndef _DYNAMIC_CONSOLETYPES_H_
#include "console/dynamicTypes.h"
#endif

#ifndef _BOXCONVEX_H_
#include "collision/boxConvex.h"
#endif

#define NUM_ETHERFORM_LASERTRAILS 3

#if 0 // BORQUE_NEEDS_PORTING
class MultiNodeLaserBeam;
class MultiNodeLaserBeamData;
#endif

class EtherformData: public ShapeBaseData 
{
	typedef ShapeBaseData Parent;

protected:
	bool onAdd();

public:
	EtherformData();

   bool preload(bool server, String &errorStr);
	static void initPersistFields();
	virtual void packData(BitStream* stream);
	virtual void unpackData(BitStream* stream);

	Point3F boxSize;        ///< Collision box width, depth, height
	F32 accelerationForce;

	// laser trail list...
#if 0 // BORQUE_NEEDS_PORTING
	MultiNodeLaserBeamData* laserTrailList[NUM_ETHERFORM_LASERTRAILS];
	S32 laserTrailIdList[NUM_ETHERFORM_LASERTRAILS];
#endif

	// Particle trail
   enum Jets {
      TrailEmitter,
      MaxJetEmitters,
   };
   ParticleEmitterData* jetEmitter[MaxJetEmitters];
   F32 minTrailSpeed;

	DECLARE_CONOBJECT(EtherformData);
	DECLARE_CATEGORY("Game");
	DECLARE_DESCRIPTION("A datablock that describes an etherform.");
};

class Etherform : public ShapeBase
{
	typedef ShapeBase Parent;
	EtherformData* mDataBlock;

	enum MaskBits {
		MoveMask     = Parent::NextFreeMask,
		NextFreeMask = Parent::NextFreeMask << 1
	};

	/// @name 3rd person camera
	/// @{
	Point3F mCameraPos;
	Point3F mCameraTargetPos;
	/// @}

	/// Client interpolation/warp data
	struct StateDelta {
		Move move;                    ///< Last move from server
		F32 dt;                       ///< Last interpolation time

		/// @name Interpolation data
		/// @{
		Point3F pos;
		Point3F rot;
		VectorF posVec;
		VectorF rotVec;
		/// @}

		/// @name Warp data
		/// @{
		S32 warpTicks;
		Point3F warpOffset;
		Point3F rotOffset;
		/// @}
	};
	StateDelta delta;                ///< Used for interpolation on the client.  @see StateDelta
	S32 mPredictionCount;            ///< Number of ticks to predict

	Box3F mScaledBox;

	Point3F mRot;
	Point3F mVelocity;

#if 0 // BORQUE_NEEDS_PORTING
	MultiNodeLaserBeam* mLaserTrailList[NUM_LASERTRAILS];
#endif
	SimObjectPtr<ParticleEmitter> mJetEmitter[EtherformData::MaxJetEmitters];

public:
	OrthoBoxConvex mConvex;
	Box3F          mWorkingQueryBox;

private:
	void setPosition(const Point3F& pos,const Point3F& viewRot);
	//void setRenderPosition(const Point3F& pos,const Point3F& viewRot);

	void setPosition(const Point3F& pos,const Point3F& viewRot, MatrixF *mat);
	void setRenderPosition(const Point3F& pos,const Point3F& viewRot,F32 dt=-1);
	void setTransform(const MatrixF& mat);
	//void setRenderTransform(const MatrixF& mat);
	void getCameraTransform(F32* pos,MatrixF* mat);

protected:
	// Etherform...
	void addLaserTrailNode(const Point3F& pos);
	void updateTrailEmitter(F32 dt);
	void updateWorkingCollisionSet();
	void findContacts();
	void updateVelocity(const Move* move);
	bool updatePos(const F32 travelTime = TickSec);
	void updateCameraPos(F32 delta);
	Point3F getVelocity() const;
	void setVelocity(const VectorF& vel);
	void applyImpulse(const Point3F& pos,const VectorF& vec);

public:
	Etherform();
	~Etherform();
	static void initPersistFields();
	static void consoleInit();

	// SimObject...
	bool onAdd();
	void onRemove();
	void onDeleteNotify(SimObject* obj);
	void onScaleChanged();

	// GameBase...
	void processTick(const Move* move);
	void interpolateTick(F32 delta);
	void advanceTime(F32 delta);
	bool onNewDataBlock(GameBaseData *dptr, bool reload);

	void writePacketData(GameConnection *conn, BitStream *stream);
	void readPacketData(GameConnection *conn, BitStream *stream);
	U32  packUpdate(NetConnection *conn, U32 mask, BitStream *stream);
	void unpackUpdate(NetConnection *conn, BitStream *stream);
	Point3F& getPosition();

	DECLARE_CONOBJECT(Etherform);
	DECLARE_CATEGORY("Game");
	DECLARE_DESCRIPTION("TODO");
};

#endif
