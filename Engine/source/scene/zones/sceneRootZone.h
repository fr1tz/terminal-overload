// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENEROOTZONE_H_
#define _SCENEROOTZONE_H_

#ifndef _SCENESIMPLEZONE_H_
#include "scene/zones/sceneSimpleZone.h"
#endif



/// Root zone in a scene.
///
/// The root zone is an infinite zone that contains all others zones and
/// objects in the scene.
///
/// This class is not declared as a ConsoleObject and is not visible
/// from TorqueScript.  SceneRootZone objects are not registered with the
/// Sim system.
class SceneRootZone : public SceneSimpleZone
{
   public:

      typedef SceneSimpleZone Parent;

   protected:

      // SceneObject.
      virtual bool onSceneAdd();
      virtual void onSceneRemove();

   public:

      SceneRootZone();

      // SimObject.
      virtual bool onAdd();
      virtual void onRemove();
      virtual String describeSelf() const;

      // SceneObject.
      virtual bool containsPoint( const Point3F &point ) const;

      // SceneZoneSpace.
      virtual U32 getPointZone( const Point3F &p ) const;
      virtual bool getOverlappingZones( const Box3F& aabb, U32* outZones, U32& outNumZones );
};

#endif //_SCENEROOTZONE_H_
