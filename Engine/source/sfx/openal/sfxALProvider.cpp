// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#include "platform/platform.h"

#include "sfx/sfxProvider.h"
#include "sfx/openal/sfxALDevice.h"
#include "sfx/openal/aldlist.h"
#include "sfx/openal/LoadOAL.h"

#include "core/strings/stringFunctions.h"
#include "console/console.h"
#include "core/module.h"


class SFXALProvider : public SFXProvider
{
public:

   SFXALProvider()
      : SFXProvider( "OpenAL" ) { mALDL = NULL; }
   virtual ~SFXALProvider();

protected:
   OPENALFNTABLE mOpenAL;
   ALDeviceList *mALDL;

   struct ALDeviceInfo : SFXDeviceInfo
   {
      
   };

   void init();

public:
   SFXDevice *createDevice( const String& deviceName, bool useHardware, S32 maxBuffers );

};

MODULE_BEGIN( OpenAL )

   MODULE_INIT_BEFORE( SFX )
   MODULE_SHUTDOWN_AFTER( SFX )
   
   SFXALProvider* mProvider;
   
   MODULE_INIT
   {
      mProvider = new SFXALProvider;
   }
   
   MODULE_SHUTDOWN
   {
      delete mProvider;
   }

MODULE_END;

void SFXALProvider::init()
{
#ifdef TORQUE_OS_LINUX
   return;
#endif

   if( LoadOAL10Library( NULL, &mOpenAL ) != AL_TRUE )
   {
      Con::printf( "SFXALProvider - OpenAL not available." );
      return;
   }
   mALDL = new ALDeviceList( mOpenAL );

   // Did we get any devices?
   if ( mALDL->GetNumDevices() < 1 )
   {
      Con::printf( "SFXALProvider - No valid devices found!" );
      return;
   }

   // Cool, loop through them, and caps em
   const char *deviceFormat = "OpenAL v%d.%d %s";

   char temp[256];
   for( int i = 0; i < mALDL->GetNumDevices(); i++ )
   {
      ALDeviceInfo* info = new ALDeviceInfo;
      
      info->name = String( mALDL->GetDeviceName( i ) );

      int major, minor, eax = 0;

      mALDL->GetDeviceVersion( i, &major, &minor );

      // Apologies for the blatent enum hack -patw
      for( int j = SFXALEAX2; j < SFXALEAXRAM; j++ )
         eax += (int)mALDL->IsExtensionSupported( i, (SFXALCaps)j );

      if( eax > 0 )
      {
         eax += 2; // EAX support starts at 2.0
         dSprintf( temp, sizeof( temp ), "[EAX %d.0] %s", eax, ( mALDL->IsExtensionSupported( i, SFXALEAXRAM ) ? "EAX-RAM" : "" ) );
      }
      else
         dStrcpy( temp, "" );

      info->driver = String::ToString( deviceFormat, major, minor, temp );
      info->hasHardware = eax > 0;
      info->maxBuffers = mALDL->GetMaxNumSources( i );

      mDeviceInfo.push_back( info );
   }

   regProvider( this );
}

SFXALProvider::~SFXALProvider()
{
#ifdef TORQUE_OS_LINUX
   return;
#endif

   UnloadOAL10Library();

   if (mALDL)
	delete mALDL;
}

SFXDevice *SFXALProvider::createDevice( const String& deviceName, bool useHardware, S32 maxBuffers )
{
   ALDeviceInfo *info = dynamic_cast< ALDeviceInfo* >
      ( _findDeviceInfo( deviceName) );

   // Do we find one to create?
   if ( info )
      return new SFXALDevice( this, mOpenAL, info->name, useHardware, maxBuffers );

   return NULL;
}