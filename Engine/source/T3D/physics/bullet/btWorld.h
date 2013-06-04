// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BTWORLD_H_
#define _BTWORLD_H_

#ifndef _T3D_PHYSICS_PHYSICSWORLD_H_
#include "T3D/physics/physicsWorld.h"
#endif
#ifndef _T3D_PHYSICS_BTDEBUGDRAW_H_
#include "T3D/physics/bullet/btDebugDraw.h"
#endif
#ifndef _BULLET_H_
#include "T3D/physics/bullet/bt.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

class ProcessList;
class btThreadSupportInterface;
class PhysicsBody;


class BtWorld : public PhysicsWorld
{
protected:

   BtDebugDraw mDebugDraw;

   F32 mEditorTimeScale;

   btDynamicsWorld *mDynamicsWorld;
   btBroadphaseInterface *mBroadphase;
   btCollisionDispatcher *mDispatcher;
   btConstraintSolver *mSolver;
   btDefaultCollisionConfiguration *mCollisionConfiguration;
  	btThreadSupportInterface *mThreadSupportCollision;

   bool mErrorReport;

   bool	mIsEnabled;

   bool mIsSimulating;

   U32 mTickCount;

   ProcessList *mProcessList;

   void _destroy();

public:

   BtWorld();
   virtual ~BtWorld();

   // PhysicWorld
   virtual bool initWorld( bool isServer, ProcessList *processList );
   virtual void destroyWorld();
   virtual bool castRay( const Point3F &startPnt, const Point3F &endPnt, RayInfo *ri, const Point3F &impulse );
   virtual PhysicsBody* castRay( const Point3F &start, const Point3F &end, U32 bodyTypes );
   virtual void explosion( const Point3F &pos, F32 radius, F32 forceMagnitude );   
   virtual void onDebugDraw( const SceneRenderState *state );
   virtual void reset();
   virtual bool isEnabled() const { return mIsEnabled; }

   btDynamicsWorld* getDynamicsWorld() const { return mDynamicsWorld; }

   void tickPhysics( U32 elapsedMs );
   void getPhysicsResults();
   bool isWritable() const { return !mIsSimulating; }

   void setEnabled( bool enabled );
   bool getEnabled() const { return mIsEnabled; }

   void setEditorTimeScale( F32 timeScale ) { mEditorTimeScale = timeScale; }
   const F32 getEditorTimeScale() const { return mEditorTimeScale; }

};

#endif // _BTWORLD_H_
