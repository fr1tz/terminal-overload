// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXNULLDEVICE_H_
#define _SFXNULLDEVICE_H_

class SFXProvider;

#ifndef _SFXDEVICE_H_
   #include "sfx/sfxDevice.h"
#endif
#ifndef _SFXPROVIDER_H_
   #include "sfx/sfxProvider.h"
#endif
#ifndef _SFXNULLBUFFER_H_
   #include "sfx/null/sfxNullBuffer.h"
#endif
#ifndef _SFXNULLVOICE_H_
   #include "sfx/null/sfxNullVoice.h"
#endif


class SFXNullDevice : public SFXDevice
{
   typedef SFXDevice Parent;

   public:

      SFXNullDevice( SFXProvider* provider, 
                     String name, 
                     bool useHardware, 
                     S32 maxBuffers );

      virtual ~SFXNullDevice();

   public:

      // SFXDevice.
      virtual  SFXBuffer* createBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );
      virtual SFXVoice* createVoice( bool is3D, SFXBuffer *buffer );
      virtual void update();
};

#endif // _SFXNULLDEVICE_H_