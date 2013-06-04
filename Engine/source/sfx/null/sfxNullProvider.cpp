// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/sfxProvider.h"
#include "sfx/null/sfxNullDevice.h"
#include "core/strings/stringFunctions.h"
#include "core/module.h"


class SFXNullProvider : public SFXProvider
{
public:

   SFXNullProvider()
      : SFXProvider( "Null" ) {}
   virtual ~SFXNullProvider();

protected:
   void addDeviceDesc( const String& name, const String& desc );
   void init();

public:

   SFXDevice* createDevice( const String& deviceName, bool useHardware, S32 maxBuffers );

};

MODULE_BEGIN( SFXNull )

   MODULE_INIT_BEFORE( SFX )
   MODULE_SHUTDOWN_AFTER( SFX )
   
   SFXNullProvider* mProvider;

   MODULE_INIT
   {
      mProvider = new SFXNullProvider;
   }
   
   MODULE_SHUTDOWN
   {
      delete mProvider;
   }

MODULE_END;

void SFXNullProvider::init()
{
   regProvider( this );
   addDeviceDesc( "Null", "SFX Null Device" );
}

SFXNullProvider::~SFXNullProvider()
{
}


void SFXNullProvider::addDeviceDesc( const String& name, const String& desc )
{
   SFXDeviceInfo* info = new SFXDeviceInfo;
   info->name = desc;
   info->driver = name;
   info->hasHardware = false;
   info->maxBuffers = 8;

   mDeviceInfo.push_back( info );
}

SFXDevice* SFXNullProvider::createDevice( const String& deviceName, bool useHardware, S32 maxBuffers )
{
   SFXDeviceInfo* info = _findDeviceInfo( deviceName );

   // Do we find one to create?
   if ( info )
      return new SFXNullDevice( this, info->name, useHardware, maxBuffers );

   return NULL;
}
