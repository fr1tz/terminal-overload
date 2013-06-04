// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "T3D/sfx/sfxSpace.h"

#include "scene/mixin/sceneAmbientSoundObject.impl.h"
#include "scene/mixin/scenePolyhedralObject.impl.h"
#include "console/engineAPI.h"


IMPLEMENT_CO_NETOBJECT_V1( SFXSpace );

ConsoleDocClass( SFXSpace,
   "@brief A volume in space that defines an ambient sound zone.\n\n"

   "@ingroup SFX"
);

//-----------------------------------------------------------------------------

SFXSpace::SFXSpace()
{
   mObjScale.set( 10, 10, 10 );
   mObjBox.set(
      Point3F( -0.5f, -0.5f, -0.5f ),
      Point3F( 0.5f, 0.5f, 0.5f )
   );
}

//-----------------------------------------------------------------------------

void SFXSpace::consoleInit()
{
   // Disable rendering of SFXSpaces by default.
   getStaticClassRep()->mIsRenderEnabled = false;
}
