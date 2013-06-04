// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXSPACE_H_
#define _SFXSPACE_H_

#ifndef _SCENESPACE_H_
#include "scene/sceneSpace.h"
#endif

#ifndef _SCENEAMBIENTSOUNDOBJECT_H_
#include "scene/mixin/sceneAmbientSoundObject.h"
#endif

#ifndef _SCENEPOLYHEDRALOBJECT_H_
#include "scene/mixin/scenePolyhedralObject.h"
#endif


/// A convex space that defines a custom ambient sound space.
class SFXSpace : public SceneAmbientSoundObject< ScenePolyhedralObject< SceneSpace > >
{
   public:

      typedef SceneAmbientSoundObject< ScenePolyhedralObject< SceneSpace > > Parent;

   protected:

      // SceneSpace.
      virtual ColorI _getDefaultEditorSolidColor() const { return ColorI( 244, 135, 18, 45 ); }

   public:

      SFXSpace();

      // SimObject.
      DECLARE_CONOBJECT( SFXSpace );
      DECLARE_DESCRIPTION( "A box volume that defines an ambient sound space." );
      DECLARE_CATEGORY( "3D Sound" );

      static void consoleInit();
};

#endif // !_SFXSPACE_H_
