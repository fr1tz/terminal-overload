// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PXPLAYER_H
#define _PXPLAYER_H

#ifndef _PHYSX_H_
#include "T3D/physics/physX/px.h"
#endif
#ifndef _T3D_PHYSICS_PHYSICSPLAYER_H_
#include "T3D/physics/physicsPlayer.h"
#endif
#ifndef _T3D_PHYSICSCOMMON_H_
#include "T3D/physics/physicsCommon.h"
#endif


class PxWorld;
class NxController;


class PxPlayer : public PhysicsPlayer, public NxUserControllerHitReport
{
protected:

   NxController *mController;

   F32 mSkinWidth;

   PxWorld *mWorld;

   SceneObject *mObject;

   /// Used to get collision info out of the
   /// NxUserControllerHitReport callbacks.
   CollisionList *mCollisionList;

   ///
   F32 mOriginOffset;

   ///
   F32 mStepHeight;

   ///
   void _releaseController();

   // NxUserControllerHitReport
   virtual NxControllerAction onShapeHit( const NxControllerShapeHit& hit );
   virtual NxControllerAction onControllerHit( const NxControllersHit& hit );

   void _findContact( SceneObject **contactObject, VectorF *contactNormal ) const;

   void _onPhysicsReset( PhysicsResetEvent reset );

   void _onStaticChanged();

public:
   
	PxPlayer();
	virtual ~PxPlayer();	

   // PhysicsObject
   virtual PhysicsWorld* getWorld();
   virtual void setTransform( const MatrixF &transform );
   virtual MatrixF& getTransform( MatrixF *outMatrix );
   virtual void setScale( const Point3F &scale );
   virtual Box3F getWorldBounds();
   virtual void setSimulationEnabled( bool enabled ) {}
   virtual bool isSimulationEnabled() { return true; }

   // PhysicsPlayer
   virtual void init(   const char *type, 
                        const Point3F &size,
                        F32 runSurfaceCos,
                        F32 stepHeight,
                        SceneObject *obj, 
                        PhysicsWorld *world );
   virtual Point3F move( const VectorF &displacement, CollisionList &outCol );
   virtual void findContact( SceneObject **contactObject, VectorF *contactNormal, Vector<SceneObject*> *outOverlapObjects ) const;
   virtual bool testSpacials( const Point3F &nPos, const Point3F &nSize ) const { return true; }
   virtual void setSpacials( const Point3F &nPos, const Point3F &nSize ) {}
   virtual void enableCollision();
   virtual void disableCollision();
};


#endif // _PXPLAYER_H