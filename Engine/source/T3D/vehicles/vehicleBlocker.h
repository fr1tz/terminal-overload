// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _VEHICLEBLOCKER_H_
#define _VEHICLEBLOCKER_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif
#ifndef _BOXCONVEX_H_
#include "collision/boxConvex.h"
#endif

//--------------------------------------------------------------------------
class VehicleBlocker : public SceneObject
{
   typedef SceneObject Parent;
   friend class VehicleBlockerConvex;

  protected:
   bool onAdd();
   void onRemove();

   // Collision
   void buildConvex(const Box3F& box, Convex* convex);
  protected:
   Convex* mConvexList;

   Point3F mDimensions;

  public:
   VehicleBlocker();
   ~VehicleBlocker();

   DECLARE_CONOBJECT(VehicleBlocker);
   static void initPersistFields();

   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);
};

#endif // _H_VEHICLEBLOCKER
