// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXXAUDIOBUFFER_H_
#define _SFXXAUDIOBUFFER_H_

#include <xaudio2.h>

#ifndef _SFXINTERNAL_H_
#include "sfx/sfxInternal.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif


/// Audio data buffer for the XAudio device layer.
class SFXXAudioBuffer : public SFXBuffer
{
   public:

      typedef SFXBuffer Parent;
      
      friend class SFXXAudioDevice;
      friend class SFXXAudioVoice;

   protected:

      struct Buffer
      {
         XAUDIO2_BUFFER mData;
         SFXInternal::SFXStreamPacket* mPacket;

         Buffer()
            : mPacket( 0 )
         {
            dMemset( &mData, 0, sizeof( mData ) );
         }
      };

      typedef Vector< Buffer > QueueType;

      QueueType mBufferQueue;

      /// If this is a streaming buffer, return the unique voice associated
      /// with the buffer.
      SFXXAudioVoice* _getUniqueVoice() { return ( SFXXAudioVoice* ) mUniqueVoice.getPointer(); }

      ///
      SFXXAudioBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );
      virtual ~SFXXAudioBuffer();

      // SFXBuffer.
      virtual void write( SFXInternal::SFXStreamPacket* const* packets, U32 num );
      void _flush();

   public:

      ///
      static SFXXAudioBuffer* create( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );
};

#endif // _SFXXAUDIOBUFFER_H_