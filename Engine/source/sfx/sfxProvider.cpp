// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/strings/stringFunctions.h"
#include "sfx/sfxProvider.h"

SFXProvider* SFXProvider::smProviders = NULL;
Vector<SFXProvider*> SFXProvider::sAllProviders( __FILE__, __LINE__ );

SFXProvider* SFXProvider::findProvider( String providerName )
{
   if( providerName.isEmpty() )
      return NULL;

   SFXProvider* curr = smProviders;
   for ( ; curr != NULL; curr = curr->mNextProvider )
   {
      if( curr->getName().equal( providerName, String::NoCase ) )
         return curr;
   }

   return NULL;
}

void SFXProvider::regProvider( SFXProvider* provider )
{
   AssertFatal( provider, "Got null provider!" );
   AssertFatal( findProvider( provider->getName() ) == NULL, "Can't register provider twice!" );
   AssertFatal( provider->mNextProvider == NULL, "Can't register provider twice!" );

   SFXProvider* oldHead = smProviders;
   smProviders = provider;
   provider->mNextProvider = oldHead;
}

SFXProvider::SFXProvider( const String& name )
   :  mName( name ),
      mNextProvider( NULL )
{
   VECTOR_SET_ASSOCIATION( mDeviceInfo );

   sAllProviders.push_back( this );
}

void SFXProvider::initializeAllProviders()
{

   for (U32 i = 0; i < sAllProviders.size(); i++)
      sAllProviders[i]->init();

}

SFXProvider::~SFXProvider()
{
   SFXDeviceInfoVector::iterator iter = mDeviceInfo.begin();
   for ( ; iter != mDeviceInfo.end(); iter++ )
      delete *iter;
}

SFXDeviceInfo* SFXProvider::_findDeviceInfo( const String& deviceName )
{
   SFXDeviceInfoVector::iterator iter = mDeviceInfo.begin();
   for ( ; iter != mDeviceInfo.end(); iter++ )
   {
      if( deviceName.equal( ( *iter )->name, String::NoCase ) )
         return *iter;
   }

   // If not found and deviceName is empty,
   // return first (default) device.

   if( deviceName.isEmpty() && mDeviceInfo.size() > 0 )
      return mDeviceInfo[ 0 ];

   return NULL;
}
