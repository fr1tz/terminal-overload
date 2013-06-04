// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXALVOICE_H_
#define _SFXALVOICE_H_

#ifndef _SFXVOICE_H_
   #include "sfx/sfxVoice.h"
#endif
#ifndef _OPENALFNTABLE
   #include "sfx/openal/LoadOAL.h"
#endif
#ifndef _PLATFORM_THREADS_MUTEX_H_
   #include "platform/threads/mutex.h"
#endif


class SFXALBuffer;
class SFXALDevice;

class SFXALVoice : public SFXVoice
{
   public:

      typedef SFXVoice Parent;
      friend class SFXALDevice;
      friend class SFXALBuffer;

   protected:

      SFXALVoice( const OPENALFNTABLE &oalft,
                  SFXALBuffer *buffer, 
                  ALuint sourceName );

      ALuint mSourceName;

      /// Buggy OAL jumps around when pausing.  Save playback cursor here.
      F32 mResumeAtSampleOffset;
      
      /// Amount by which OAL's reported sample position is offset.
      ///
      /// OAL's sample position is relative to the current queue state,
      /// so we manually need to keep track of how far into the total
      /// queue we are.
      U32 mSampleOffset;

      Mutex mMutex;

      const OPENALFNTABLE &mOpenAL;

      ///
      SFXALBuffer* _getBuffer() const
      {
         return ( SFXALBuffer* ) mBuffer.getPointer();
      }
      
      /// For non-streaming buffers, late-bind the audio buffer
      /// to the source as OAL will not accept writes to buffers
      /// already bound.
      void _lateBindStaticBufferIfNecessary();

      // SFXVoice.
      virtual SFXStatus _status() const;
      virtual void _play();
      virtual void _pause();
      virtual void _stop();
      virtual void _seek( U32 sample );
      virtual U32 _tell() const;

   public:

      static SFXALVoice* create( SFXALDevice* device,
                                 SFXALBuffer *buffer );

      virtual ~SFXALVoice();

      /// SFXVoice
      void setMinMaxDistance( F32 min, F32 max );
      void play( bool looping );
      void setVelocity( const VectorF& velocity );
      void setTransform( const MatrixF& transform );
      void setVolume( F32 volume );
      void setPitch( F32 pitch );
      void setCone( F32 innerAngle, F32 outerAngle, F32 outerVolume );
      void setRolloffFactor( F32 factor );
};

#endif // _SFXALVOICE_H_