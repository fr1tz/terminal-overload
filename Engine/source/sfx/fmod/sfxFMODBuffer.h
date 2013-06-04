// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXFMODBUFFER_H_
#define _SFXFMODBUFFER_H_

#include "fmod.h"

#ifndef _SFXINTERNAL_H_
#  include "sfx/sfxInternal.h"
#endif


class SFXFMODBuffer : public SFXInternal::SFXWrapAroundBuffer
{
      typedef SFXInternal::SFXWrapAroundBuffer Parent;

      friend class SFXFMODDevice;
      friend class SFXFMODVoice;

   protected:

      FMOD_SOUND *mSound;	   
      FMOD_MODE mMode;

      SFXFMODBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );
      SFXFMODBuffer( const String& filename, SFXDescription* description );

      // SFXWrapAroundBuffer.
      virtual bool _copyData( U32 offset, const U8* data, U32 length );
      virtual void _flush();

      virtual ~SFXFMODBuffer();

   public:

      ///
      static SFXFMODBuffer* create( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );
      static SFXFMODBuffer* create( const String& filename, SFXDescription* description );

      virtual U32 getMemoryUsed() const;
};

#endif // _SFXFMODBUFFER_H_