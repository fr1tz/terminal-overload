// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/fmod/sfxFMODPlugin.h"
#include "sfx/fmod/sfxFMODEvent.h"
#include "sfx/fmod/sfxFMODEventSource.h"


//-----------------------------------------------------------------------------

SFXSource* SFXFMODPlugin::createSource( SFXTrack* track )
{
   SFXFMODEvent* event = dynamic_cast< SFXFMODEvent* >( track );
   if( !event )
      return NULL;
         
   return SFXFMODEventSource::create( event );
}
