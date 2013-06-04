// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PHYSX_WORLD_H_
#define _PHYSX_WORLD_H_

#ifndef _T3D_PHYSICS_PHYSICSWORLD_H_
#include "T3D/physics/physicsWorld.h"
#endif
#ifndef _MMATH_H_
#include "math/mMath.h"
#endif
#ifndef _PHYSX_H_
#include "T3D/physics/physX/px.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

class PxContactReporter;
class PxUserNotify;
class NxController;
class NxControllerDesc;
class ShapeBase;
class TSStatic;
class SceneObject;
class ProcessList;
class GameBase;
class CharacterControllerManager;
class PxConsoleStream;


class PxWorld : public PhysicsWorld
{
protected:

   F32 mEditorTimeScale;

   Vector<NxCloth*> mReleaseClothQueue;
   Vector<NxJoint*> mReleaseJointQueue;
   Vector<NxActor*> mReleaseActorQueue;
   Vector<NxMaterial*> mReleaseMaterialQueue;
   Vector<NxHeightField*> mReleaseHeightFieldQueue;
   Vector<NxFluid*> mReleaseFluidQueue;
   //Vector<StrongRefPtr<PxCollision>> mReleaseColQueue;

   Vector<NxActor*> mCatchupQueue;

   PxContactReporter *mConactReporter;

   PxUserNotify *mUserNotify;

   NxScene *mScene;

	CharacterControllerManager *mControllerManager;
	
   bool  mErrorReport;

   bool	mIsEnabled;

   bool mIsSimulating;

   U32 mTickCount;

   ProcessList *mProcessList;

   bool _init( bool isServer, ProcessList *processList );

   void _destroy();

   void _releaseQueues();

   void _updateScheduledStatics();

   /// The mesh cooking interface which is loaded on first use.
   /// @see getCooking
   static NxCookingInterface *smCooking;

   /// The console stream for PhysX error reporting.
   static PxConsoleStream *smConsoleStream;

public:

   // PhysicWorld
   virtual bool initWorld( bool isServer, ProcessList *processList );
   virtual void destroyWorld();
   virtual bool castRay( const Point3F &startPnt, const Point3F &endPnt, RayInfo *ri, const Point3F &impulse );
   virtual PhysicsBody* castRay( const Point3F &start, const Point3F &end, U32 bodyTypes = BT_All );
   virtual void explosion( const Point3F &pos, F32 radius, F32 forceMagnitude );   
   virtual void onDebugDraw( const SceneRenderState *state );
   virtual void reset() {}
   virtual bool isEnabled() const { return mIsEnabled; }

   /// @name Static Methods
   /// @{

   static bool restartSDK( bool destroyOnly = false, PxWorld *clientWorld = NULL, PxWorld *serverWorld = NULL );

   static void releaseWriteLocks();

   /// @}

   PxWorld();
   virtual ~PxWorld();

public:

   NxScene* getScene() { return mScene; }

   /// Returns the cooking interface.  Will only return NULL
   /// in the case of a missing or bad PhysX install.
   static NxCookingInterface* getCooking();

   U32 getTick() { return mTickCount; }

   void tickPhysics( U32 elapsedMs );

   void getPhysicsResults();

   //void enableCatchupMode( GameBase *obj );

   bool isWritable() const { return !mIsSimulating; /* mScene->isWritable(); */ }

   void releaseWriteLock();

   void setEnabled( bool enabled );
   bool getEnabled() const { return mIsEnabled; }

   NxMaterial* createMaterial( NxMaterialDesc &material );

   ///
   /// @see releaseController
   NxController* createController( NxControllerDesc &desc ); 

   //U16 setMaterial(NxMaterialDesc &material, U16 id);

   // NOTE: This is all a mess, but its a side effect of how 
   // PhysX works.  Many objects cannot be deleted without write
   // access to the scene.  Worse some objects cannot be deleted
   // until their owner objects are deleted first.
   //
   // For these reasons we have these methods to register objects to be
   // released after the Scene has been ticked.
   //
   // Since there is no common base to PhysX objects we're stuck with
   // this list of release methods.
   //

   void releaseActor( NxActor &actor );

   void releaseMaterial( NxMaterial &mat );

   void releaseJoint( NxJoint &joint );
   
   void releaseCloth( NxCloth &cloth );
   
   void releaseClothMesh( NxClothMesh &clothMesh );

   void releaseController( NxController &controller );

   void releaseHeightField( NxHeightField &heightfield );

   void releaseFluid( NxFluid &fluid );

   //void releaseCol( PxCollision *col );

   /// Returns the contact reporter for this scene.
   PxContactReporter* getContactReporter() { return mConactReporter; }

   void setEditorTimeScale( F32 timeScale ) { mEditorTimeScale = timeScale; }
   const F32 getEditorTimeScale() const { return mEditorTimeScale; }
};

#endif // _PHYSX_WORLD_H_
