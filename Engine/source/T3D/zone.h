// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ZONE_H_
#define _ZONE_H_

#ifndef _SCENEPOLYHEDRALZONE_H_
#include "scene/zones/scenePolyhedralZone.h"
#endif

#ifndef _SCENEAMBIENTSOUNDOBJECT_H_
#include "scene/mixin/sceneAmbientSoundObject.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif


/// A volume in space that encloses objects.
///
/// Zones do not physically contain objects in the scene.  Rather, any object
/// that has its world box coincide with the world box of a zone is considered
/// to be part of that zone.  As such, objects can be in multiple zones at
/// the same time.
class Zone : public SceneAmbientSoundObject
{
   public:

      typedef SceneAmbientSoundObject Parent;

   protected:

      // SceneVolume.
      virtual ColorI _getDefaultEditorSolidColor() const { return ColorI( 255, 0, 0, 45 ); }

   public:

      Zone() {}
      Zone( const Polyhedron& polyhedron )
      {
         mPolyhedron = polyhedron;
      }

      // SimObject
      DECLARE_CONOBJECT( Zone );
      DECLARE_DESCRIPTION( "A volume that encloses objects for visibility culling." );
      DECLARE_CATEGORY( "3D" );

      static void consoleInit();
};

#endif // _ZONE_H_
