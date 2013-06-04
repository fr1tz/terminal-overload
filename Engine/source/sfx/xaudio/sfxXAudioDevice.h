// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXXAUDIODEVICE_H_
#define _SFXXAUDIODEVICE_H_

class SFXProvider;

#ifndef _SFXDEVICE_H_
#include "sfx/sfxDevice.h"
#endif

#ifndef _SFXPROVIDER_H_
#include "sfx/sfxProvider.h"
#endif

#ifndef _SFXXAUDIOVOICE_H_
#include "sfx/xaudio/sfxXAudioVoice.h"
#endif

#ifndef _SFXXAUDIOBUFFER_H_
#include "sfx/xaudio/sfxXAudioBuffer.h"
#endif

#include <xaudio2.h>
#include <x3daudio.h>


class SFXXAudioDevice : public SFXDevice
{
   public:

      typedef SFXDevice Parent;
      friend class SFXXAudioVoice; // mXAudio

   protected:

      /// The XAudio engine interface passed 
      /// on creation from the provider.
      IXAudio2 *mXAudio;

      /// The X3DAudio instance.
      X3DAUDIO_HANDLE mX3DAudio;

      /// The one and only mastering voice.
      IXAudio2MasteringVoice* mMasterVoice;

      /// The details of the master voice.
      XAUDIO2_VOICE_DETAILS mMasterVoiceDetails;

      /// The one listener.
      X3DAUDIO_LISTENER mListener;

      SFXDistanceModel mDistanceModel;
      F32 mRolloffFactor;
      F32 mDopplerFactor;

   public:

      SFXXAudioDevice(  SFXProvider* provider, 
                        const String& name,
                        IXAudio2 *xaudio,
                        U32 deviceIndex,
                        U32 speakerChannelMask,
                        U32 maxBuffers );

      virtual ~SFXXAudioDevice();

      // SFXDevice
      virtual SFXBuffer* createBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );
      virtual SFXVoice* createVoice( bool is3D, SFXBuffer *buffer );
      virtual void update();
      virtual void setListener( U32 index, const SFXListenerProperties& listener );
      virtual void setDistanceModel( SFXDistanceModel model );
      virtual void setRolloffFactor( F32 factor );
      virtual void setDopplerFactor( F32 factor );

      /// Called from the voice when its about to start playback.
      void _setOutputMatrix( SFXXAudioVoice *voice );
};

#endif // _SFXXAUDIODEVICE_H_