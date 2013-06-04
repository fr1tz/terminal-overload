// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _DECALSPHERE_H_
#define _DECALSPHERE_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _MSPHERE_H_
#include "math/mSphere.h"
#endif


class DecalInstance;
class SceneZoneSpaceManager;


/// A bounding sphere in world space and a list of DecalInstance(s)
/// contained by it. DecalInstance(s) are organized/binned in this fashion
/// as a lookup and culling optimization.
class DecalSphere
{
   public:

      static F32 smDistanceTolerance;
      static F32 smRadiusTolerance;

      DecalSphere()
      {
         VECTOR_SET_ASSOCIATION( mItems );
         VECTOR_SET_ASSOCIATION( mZones );
      }
      DecalSphere( const Point3F &position, F32 radius )
      {
         VECTOR_SET_ASSOCIATION( mItems );
         VECTOR_SET_ASSOCIATION( mZones );

         mWorldSphere.center = position;
         mWorldSphere.radius = radius;
      }

      /// Recompute #mWorldSphere from the current instance list.
      void updateWorldSphere();

      /// Recompute the zoning information from the current bounds.
      void updateZoning( SceneZoneSpaceManager* zoneManager );

      /// Decal instances in this sphere.
      Vector< DecalInstance* > mItems;

      /// Zones that intersect with this sphere.  If this is empty, the zoning
      /// state of the sphere is uninitialized.
      Vector< U32 > mZones;

      /// World-space sphere corresponding to this DecalSphere.
      SphereF mWorldSphere;

      ///
      bool tryAddItem( DecalInstance* inst );
};

#endif // !_DECALSPHERE_H_