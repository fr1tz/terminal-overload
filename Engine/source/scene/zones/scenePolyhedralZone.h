// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENEPOLYHEDRALZONE_H_
#define _SCENEPOLYHEDRALZONE_H_

#ifndef _SCENESIMPLEZONE_H_
#include "scene/zones/sceneSimpleZone.h"
#endif

#ifndef _SCENEPOLYHEDRALOBJECT_H_
#include "scene/mixin/scenePolyhedralObject.h"
#endif

#ifndef _MINTERSECTOR_H_
#include "math/mIntersector.h"
#endif


/// A simple zone space that is described by a polyhedron.
///
/// By default, if no other polyhedron is assigned to a polyhedral zone, the
/// polyhedron is initialized from the zone's object box.
class ScenePolyhedralZone : public ScenePolyhedralObject
{
   public:

      typedef ScenePolyhedralObject Parent;

   protected:

      typedef PolyhedronBoxIntersector< PolyhedronType > IntersectorType;

      /// Fast polyhedron/AABB intersector used for testing SceneObject AABBs
      /// for overlap with the zone.
      IntersectorType mIntersector;

      /// Precompute polyhedron/AABB intersection data.
      void _updateIntersector()
      {
         mIntersector = IntersectorType( getPolyhedron(), getTransform(), getScale(), getWorldBox() );
      }

      // SceneSimpleZone.
      virtual void _updateOrientedWorldBox();

   public:

      ScenePolyhedralZone() {}
      ScenePolyhedralZone( const PolyhedronType& polyhedron );

      // SimObject.
      virtual bool onAdd();

      // SceneObject.
      virtual void setTransform( const MatrixF& mat );

      // SceneZoneSpace.
      virtual bool getOverlappingZones( const Box3F& aabb, U32* outZones, U32& outNumZones );
};

#endif // !_SCENEPOLYHEDRALZONE_H_
