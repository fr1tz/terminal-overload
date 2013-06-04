// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#if 0 // BORQUE_NEEDS_PORTING

#ifndef _ETHERFORM_H_
#define _ETHERFORM_H_

#ifndef _SHAPEBASE_H_
#include "game/shapeBase.h"
#endif
#ifndef _BOXCONVEX_H_
#include "collision/boxConvex.h"
#endif

#define NUM_LASERTRAILS 3

class MultiNodeLaserBeam;
class MultiNodeLaserBeamData;

//----------------------------------------------------------------------------

class EtherformData : public ShapeBaseData
{
   typedef ShapeBaseData Parent;

protected:
   bool onAdd();

public:
	Point3F boxSize;        ///< Collision box width, depth, height
	F32 accelerationForce;

	// laser trail list...
	MultiNodeLaserBeamData* laserTrailList[NUM_LASERTRAILS];
	S32 laserTrailIdList[NUM_LASERTRAILS];

	// Particle trail
   enum Jets {
      TrailEmitter,
      MaxJetEmitters,
   };
   ParticleEmitterData* jetEmitter[MaxJetEmitters];
   F32 minTrailSpeed;

	EtherformData();
   
   virtual bool preload(bool server, char errorBuffer[256]);
	virtual void packData(BitStream* stream);
	virtual void unpackData(BitStream* stream);

	static void initPersistFields();
	DECLARE_CONOBJECT(EtherformData);
};


//----------------------------------------------------------------------------
/// Implements a basic camera object.
class Etherform: public ShapeBase
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

	MultiNodeLaserBeam* mLaserTrailList[NUM_LASERTRAILS];
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
	DECLARE_CONOBJECT(Etherform);

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
	void processTick(const Move *move);
	void interpolateTick(F32 delta);
	void advanceTime(F32 delta);
	bool onNewDataBlock(GameBaseData *dptr);

	void writePacketData(GameConnection *conn, BitStream *stream);
	void readPacketData(GameConnection *conn, BitStream *stream);
	U32  packUpdate(NetConnection *conn, U32 mask, BitStream *stream);
	void unpackUpdate(NetConnection *conn, BitStream *stream);
	Point3F &getPosition();
};

#endif

#endif // BORQUE_NEEDS_PORTING