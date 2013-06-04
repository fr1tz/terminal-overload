// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXDSVOICE_H_
#define _SFXDSVOICE_H_

#ifndef _SFXVOICE_H_
   #include "sfx/sfxVoice.h"
#endif
#ifndef _SFXDSBUFFER_H_
   #include "sfx/dsound/sfxDSBuffer.h"
#endif

#include <dsound.h>

class SFXDSDevice;


class SFXDSVoice : public SFXVoice
{
      typedef SFXVoice Parent;

   protected:

      SFXDSVoice( SFXDSDevice *device,
                  SFXDSBuffer *buffer,
                  IDirectSoundBuffer8 *dsBuffer, 
                  IDirectSound3DBuffer8 *dsBuffer3d );

      /// The device used to commit deferred settings. 
      SFXDSDevice *mDevice;

      IDirectSoundBuffer8 *mDSBuffer;

      IDirectSound3DBuffer8 *mDSBuffer3D;

      bool mIsLooping;

      SFXDSBuffer* _getBuffer() const { return ( SFXDSBuffer* ) mBuffer.getPointer(); }

      /// Helper for converting floating point linear volume
      /// to a logrithmic integer volume for dsound.
      static LONG _linearToLogVolume( F32 linVolume );

      // SFXVoice
      virtual SFXStatus _status() const;
      virtual void _play();
      virtual void _pause();
      virtual void _stop();
      virtual void _seek( U32 sample );
      virtual U32 _tell() const;

   public:

      ///
      static SFXDSVoice* create( SFXDSDevice *device,
                                 SFXDSBuffer *buffer );

      ///
      virtual ~SFXDSVoice();

      // SFXVoice
      void setMinMaxDistance( F32 min, F32 max );
      void play( bool looping );
      void setVelocity( const VectorF& velocity );
      void setTransform( const MatrixF& transform );
      void setVolume( F32 volume );
      void setPitch( F32 pitch );
      void setCone( F32 innerAngle, F32 outerAngle, F32 outerVolume );

};

#endif // _SFXDSBUFFER_H_