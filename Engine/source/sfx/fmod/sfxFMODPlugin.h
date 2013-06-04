// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXFMODPLUGIN_H_
#define _SFXFMODPLUGIN_H_

#ifndef _SFXSYSTEM_H_
   #include "sfx/sfxSystem.h"
#endif


/// SFXSystem plugin that adds the capability to create SFXSources for
/// Designer SFXFMODEvents.
///
/// The plugin will only be installed if an FMOD device has been created.
/// While SFXFMODEvents may be constructed without an FMOD device, trying
/// to play such an event then will result in an error.
///
class SFXFMODPlugin : public SFXSystemPlugin
{
   public:
   
      typedef SFXSystemPlugin Parent;
      
      ///
      virtual SFXSource* createSource( SFXTrack* track );
};

#endif // !_SFXFMODPLUGIN_H_
