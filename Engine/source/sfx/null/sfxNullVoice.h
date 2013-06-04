// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXNULLVOICE_H_
#define _SFXNULLVOICE_H_

#ifndef _SFXVOICE_H_
   #include "sfx/sfxVoice.h"
#endif
#ifndef _TIMESOURCE_H_
   #include "core/util/timeSource.h"
#endif


class SFXNullBuffer;


class SFXNullVoice : public SFXVoice
{
   public:

      typedef SFXVoice Parent;
      friend class SFXNullDevice;

   protected:
   
      typedef GenericTimeSource< VirtualMSTimer > TimeSource;

      SFXNullVoice( SFXNullBuffer* buffer );
      
      /// The virtual play timer.
      mutable TimeSource mPlayTimer;

      ///
      bool mIsLooping;

      // SFXVoice.
      virtual SFXStatus _status() const;
      virtual void _play();
      virtual void _pause();
      virtual void _stop();
      virtual void _seek( U32 sample );
      virtual U32 _tell() const;

      ///
      U32 _getPlayTime() const
      {
         return mPlayTimer.getPosition();
      }

   public:

      virtual ~SFXNullVoice();

      /// SFXVoice
      SFXStatus getStatus() const;
      void setPosition( U32 sample );
      void play( bool looping );
      void setMinMaxDistance( F32 min, F32 max );
      void setVelocity( const VectorF& velocity );
      void setTransform( const MatrixF& transform );
      void setVolume( F32 volume );
      void setPitch( F32 pitch );
      void setCone( F32 innerAngle, F32 outerAngle, F32 outerVolume );
};

#endif // _SFXNULLVOICE_H_