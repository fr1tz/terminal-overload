// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PHYSICSPLAYER_H_
#define _T3D_PHYSICS_PHYSICSPLAYER_H_

#ifndef _T3D_PHYSICS_PHYSICSOBJECT_H_
#include "T3D/physics/physicsObject.h"
#endif
#ifndef _MMATH_H_
#include "math/mMath.h"
#endif

class CollisionList;
//struct ObjectRenderInst;
//class BaseMatInstance;
//class Player;
//class SceneState;
class SceneObject;


///
class PhysicsPlayer : public PhysicsObject
{
public:

   PhysicsPlayer() {}

   virtual ~PhysicsPlayer() {};

   ///
   virtual void init(   const char *type, 
                        const Point3F &size,
                        F32 runSurfaceCos,
                        F32 stepHeight,
                        SceneObject *obj, 
                        PhysicsWorld *world ) = 0;

   virtual void findContact(  SceneObject **contactObject, 
                              VectorF *contactNormal,
                              Vector<SceneObject*> *outOverlapObjects ) const = 0;

   virtual Point3F move( const VectorF &displacement, CollisionList &outCol ) = 0;

   virtual bool testSpacials( const Point3F &nPos, const Point3F &nSize ) const = 0;

   virtual void setSpacials( const Point3F &nPos, const Point3F &nSize ) = 0;

   virtual void enableCollision() = 0;

   virtual void disableCollision() = 0;
};


#endif // _T3D_PHYSICS_PHYSICSPLAYER_H_