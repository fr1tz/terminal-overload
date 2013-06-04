// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXALBUFFER_H_
#define _SFXALBUFFER_H_

#ifndef _LOADOAL_H
   #include "sfx/openal/LoadOAL.h"
#endif
#ifndef _SFXINTERNAL_H_
   #include "sfx/sfxInternal.h"
#endif
#ifndef _TVECTOR_H_
   #include "core/util/tVector.h"
#endif


class SFXALVoice;


class SFXALBuffer : public SFXBuffer
{
   public:

      typedef SFXBuffer Parent;

      friend class SFXALDevice;
      friend class SFXALVoice;

   protected:
      
      /// AL buffer in case this is a static, non-streaming buffer.
      ALuint mALBuffer;
      
      /// Free buffers for use in queuing in case this is a streaming buffer.
      Vector< ALuint > mFreeBuffers;

      ///
      SFXALBuffer(   const OPENALFNTABLE &oalft, 
                     const ThreadSafeRef< SFXStream >& stream,
                     SFXDescription* description,
                     bool useHardware );

      ///
      bool mIs3d;

      ///
      bool mUseHardware;

      const OPENALFNTABLE &mOpenAL;

      ///
      ALenum _getALFormat() const
      {
         return _sfxFormatToALFormat( getFormat() );
      }

      ///
      static ALenum _sfxFormatToALFormat( const SFXFormat& format )
      {
         if( format.getChannels() == 2 )
         {
            const U32 bps = format.getBitsPerSample();
            if( bps == 16 )
               return AL_FORMAT_STEREO8;
            else if( bps == 32 )
               return AL_FORMAT_STEREO16;
         }
         else if( format.getChannels() == 1 )
         {
            const U32 bps = format.getBitsPerSample();
            if( bps == 8 )
               return AL_FORMAT_MONO8;
            else if( bps == 16 )
               return AL_FORMAT_MONO16;
         }
         return 0;
      }

      ///
      SFXALVoice* _getUniqueVoice() const
      {
         return ( SFXALVoice* ) mUniqueVoice.getPointer();
      }

      // SFXBuffer.
      virtual void write( SFXInternal::SFXStreamPacket* const* packets, U32 num );
      void _flush();

   public:

      static SFXALBuffer* create(   const OPENALFNTABLE &oalft, 
                                    const ThreadSafeRef< SFXStream >& stream,
                                    SFXDescription* description,
                                    bool useHardware );

      virtual ~SFXALBuffer();
};

#endif // _SFXALBUFFER_H_