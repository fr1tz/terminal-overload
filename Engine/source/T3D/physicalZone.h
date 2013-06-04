// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _H_PHYSICALZONE
#define _H_PHYSICALZONE

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _EARLYOUTPOLYLIST_H_
#include "collision/earlyOutPolyList.h"
#endif
#ifndef _MPOLYHEDRON_H_
#include "math/mPolyhedron.h"
#endif

class Convex;


class PhysicalZone : public SceneObject
{
   typedef SceneObject Parent;

   enum UpdateMasks {      
      ActiveMask        = Parent::NextFreeMask << 0,
      NextFreeMask      = Parent::NextFreeMask << 1
   };

  protected:
   static bool smRenderPZones;

   F32        mVelocityMod;
   F32        mGravityMod;
   Point3F    mAppliedForce;

   // Basically ripped from trigger
   Polyhedron           mPolyhedron;
   EarlyOutPolyList     mClippedList;

   bool mActive;

   Convex* mConvexList;
   void buildConvex(const Box3F& box, Convex* convex);

  public:
   PhysicalZone();
   ~PhysicalZone();

   // SimObject
   DECLARE_CONOBJECT(PhysicalZone);
   static void consoleInit();
   static void initPersistFields();
   bool onAdd();
   void onRemove();
   void inspectPostApply();

   // NetObject
   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);

   // SceneObject
   void setTransform(const MatrixF &mat);
   void prepRenderImage( SceneRenderState* state );

   inline F32 getVelocityMod() const      { return mVelocityMod; }
   inline F32 getGravityMod()  const      { return mGravityMod;  }
   inline const Point3F& getForce() const { return mAppliedForce; }

   void setPolyhedron(const Polyhedron&);
   bool testObject(SceneObject*);

   bool testBox( const Box3F &box ) const;

   void renderObject( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *overrideMat );

   void activate();
   void deactivate();
   inline bool isActive() const { return mActive; }

};

#endif // _H_PHYSICALZONE

