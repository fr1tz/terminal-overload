// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXALDEVICE_H_
#define _SFXALDEVICE_H_

class SFXProvider;

#ifndef _SFXDEVICE_H_
#  include "sfx/sfxDevice.h"
#endif

#ifndef _SFXPROVIDER_H_
#  include "sfx/sfxProvider.h"
#endif

#ifndef _SFXALBUFFER_H_
#  include "sfx/openal/sfxALBuffer.h"
#endif

#ifndef _SFXALVOICE_H_
#  include "sfx/openal/sfxALVoice.h"
#endif

#ifndef _OPENALFNTABLE
#  include "sfx/openal/LoadOAL.h"
#endif


class SFXALDevice : public SFXDevice
{
   public:

      typedef SFXDevice Parent;
      friend class SFXALVoice; // mDistanceFactor, mRolloffFactor

      SFXALDevice(   SFXProvider *provider, 
                     const OPENALFNTABLE &openal, 
                     String name, 
                     bool useHardware, 
                     S32 maxBuffers );

      virtual ~SFXALDevice();

   protected:

      OPENALFNTABLE mOpenAL;

      ALCcontext *mContext;

      ALCdevice *mDevice;
      
      SFXDistanceModel mDistanceModel;
      F32 mDistanceFactor;
      F32 mRolloffFactor;
      F32 mUserRolloffFactor;
      
      void _setRolloffFactor( F32 factor );

   public:

      // SFXDevice.
      virtual SFXBuffer* createBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );
      virtual SFXVoice* createVoice( bool is3D, SFXBuffer *buffer );
      virtual void setListener( U32 index, const SFXListenerProperties& listener );
      virtual void setDistanceModel( SFXDistanceModel model );
      virtual void setDopplerFactor( F32 factor );
      virtual void setRolloffFactor( F32 factor );
};

#endif // _SFXALDEVICE_H_