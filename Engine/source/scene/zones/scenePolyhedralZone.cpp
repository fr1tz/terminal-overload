// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "scene/zones/scenePolyhedralZone.h"



//-----------------------------------------------------------------------------

ScenePolyhedralZone::ScenePolyhedralZone( const PolyhedronType& polyhedron )
   : Parent( polyhedron )
{
}

//-----------------------------------------------------------------------------

bool ScenePolyhedralZone::onAdd()
{
   if( !Parent::onAdd() )
      return false;

   // Precompute polyhedron/AABB intersection data, if not
   // a trivial box polyhedron.

   if( !mIsBox )
   {
      _updateIntersector();

      // Also need to update OBB.
      _updateOrientedWorldBox();
   }
      
   return true;
}

//-----------------------------------------------------------------------------

void ScenePolyhedralZone::setTransform( const MatrixF& mat )
{
   Parent::setTransform( mat );

   // Recompute intersection data.

   if( !mIsBox )
      _updateIntersector();
}

//-----------------------------------------------------------------------------

void ScenePolyhedralZone::_updateOrientedWorldBox()
{
   if( mIsBox )
      Parent::_updateOrientedWorldBox();
   else
       mOrientedWorldBox.set( getTransform(), mObjBox.getExtents() * getScale() );
}

//-----------------------------------------------------------------------------

bool ScenePolyhedralZone::getOverlappingZones( const Box3F& aabb, U32* outZones, U32& outNumZones )
{
   // If a trivial box, let parent handle this.

   if( mIsBox )
      return Parent::getOverlappingZones( aabb, outZones, outNumZones );

   // Otherwise, use the intersector.

   OverlapTestResult overlap = mIntersector.test( aabb );
   
   if( overlap == GeometryOutside )
   {
      outNumZones = 0;
      return true;
   }

   outZones[ 0 ] = getZoneRangeStart();
   outNumZones = 1;

   return ( overlap != GeometryInside );
}
