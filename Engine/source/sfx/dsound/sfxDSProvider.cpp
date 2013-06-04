// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/sfxProvider.h"
#include "sfx/dsound/sfxDSDevice.h"
#include "core/util/safeRelease.h"
#include "console/console.h"
#include "core/strings/unicode.h"
#include "core/util/safeDelete.h"
#include "core/module.h"


class SFXDSProvider : public SFXProvider
{
public:

   SFXDSProvider()
      : SFXProvider( "DirectSound" ) {}
   virtual ~SFXDSProvider();

   void init();

protected:
   DSoundFNTable mDSound;

   struct DSDeviceInfo : SFXDeviceInfo
   {
      GUID* guid;
      DSCAPS caps;
   };

   static BOOL CALLBACK dsEnumProc( 
      LPGUID lpGUID, 
      LPCTSTR lpszDesc, 
      LPCTSTR lpszDrvName, 
      LPVOID lpContext );

   void addDeviceDesc( GUID* guid, const String& name, const String& desc );

public:

   SFXDevice* createDevice( const String& deviceName, bool useHardware, S32 maxBuffers );

};

MODULE_BEGIN( DirectSound )

   MODULE_INIT_BEFORE( SFX )
   MODULE_SHUTDOWN_AFTER( SFX )
   
   SFXDSProvider* mProvider;
   
   MODULE_INIT
   {
      mProvider = new SFXDSProvider;
   }
   
   MODULE_SHUTDOWN
   {
      delete mProvider;
   }

MODULE_END;

//------------------------------------------------------------------------------
// Helper

bool dsBindFunction( DLibrary *dll, void *&fnAddress, const char *name )
{
   fnAddress = dll->bind( name );

   if (!fnAddress)
      Con::warnf( "DSound Loader: DLL bind failed for %s", name );

   return fnAddress != 0;
}

//------------------------------------------------------------------------------

SFXDSProvider::~SFXDSProvider()
{
}

void SFXDSProvider::init()
{
   // Grab the functions we'll want from the dsound DLL.
   mDSound.dllRef = OsLoadLibrary( "dsound.dll" );
   mDSound.isLoaded = true;
#define DS_FUNCTION(fn_name, fn_return, fn_args) \
   mDSound.isLoaded &= dsBindFunction(mDSound.dllRef, *(void**)&mDSound.fn_name, #fn_name);
#include "sfx/dsound/dsFunctions.h"
#undef DS_FUNCTION

   AssertISV( mDSound.isLoaded, "DirectSound failed to load." );

   // All we need to do to init is enumerate the 
   // devices... if this fails then don't register
   // the provider as it's broken in some way.
   if ( FAILED( mDSound.DirectSoundEnumerate( dsEnumProc, (VOID*)this ) ) )
   {
      Con::errorf( "SFXDSProvider - Device enumeration failed!" );
      return;
   }

   // Did we get any devices?
   if ( mDeviceInfo.empty() )
   {
      Con::errorf( "SFXDSProvider - No valid devices found!" );
      return;
   }

   // Wow, we made it - register the provider.
   regProvider( this );
}


BOOL CALLBACK SFXDSProvider::dsEnumProc( 
   LPGUID lpGUID, 
   LPCTSTR lpszDesc, 
   LPCTSTR lpszDrvName, 
   LPVOID lpContext )
{
   SFXDSProvider* provider = (SFXDSProvider*)lpContext;
   provider->addDeviceDesc( lpGUID, lpszDrvName, lpszDesc );
   return TRUE;
}

void SFXDSProvider::addDeviceDesc( GUID* guid, const String& name, const String& desc )
{
   // Create a dummy device to get the caps.
   IDirectSound8* dsound;
   HRESULT hr = mDSound.DirectSoundCreate8( guid, &dsound, NULL );   
   if ( FAILED( hr ) || !dsound )
      return;

   // Init the caps structure and have the device fill it out.
   DSCAPS caps;
   dMemset( &caps, 0, sizeof( caps ) ); 
   caps.dwSize = sizeof( caps );
   hr = dsound->GetCaps( &caps );

   // Clean up and handle errors.
   SAFE_RELEASE( dsound );

   if ( FAILED( hr ) )
      return;

   // Now, record the desc info into our own internal list.
   DSDeviceInfo* info = new DSDeviceInfo;
   info->name = desc;
   info->driver = name;
   info->hasHardware = caps.dwMaxHw3DAllBuffers > 0;
   info->maxBuffers = caps.dwMaxHw3DAllBuffers;
   info->guid = guid;
   info->caps = caps;

   mDeviceInfo.push_back( info );
}

SFXDevice* SFXDSProvider::createDevice( const String& deviceName, bool useHardware, S32 maxBuffers )
{
   DSDeviceInfo* info = dynamic_cast< DSDeviceInfo* >
      ( _findDeviceInfo( deviceName ) );

   if( !info )
      return NULL;

   SFXDSDevice* device = new SFXDSDevice( this, 
                                 &mDSound,
                                 info->guid,
                                 info->name, 
                                 useHardware, 
                                 maxBuffers );

   if( !device->_init() )
      SAFE_DELETE( device );

   return device;
}
