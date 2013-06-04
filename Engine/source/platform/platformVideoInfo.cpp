// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platformVideoInfo.h"
#include "core/strings/stringFunctions.h"

//------------------------------------------------------------------------------

PlatformVideoInfo::PlatformVideoInfo() 
{
   VECTOR_SET_ASSOCIATION( mAdapters );
}

//------------------------------------------------------------------------------

PlatformVideoInfo::~PlatformVideoInfo()
{

}

//------------------------------------------------------------------------------


bool PlatformVideoInfo::profileAdapters()
{
   // Initialize the child class
   if( !_initialize() )
      return false;

   mAdapters.clear();

   // Query the number of adapters
   String tempString;

   if( !_queryProperty( PVI_NumAdapters, 0, &tempString ) )
   {
      // Not all platforms may support PVI_NumAdapters.  We will assume that there
      // is one adapter.  This was the behavior before PVI_NumAdapters was implemented.
      mAdapters.increment( 1 );
   }
   else
   {
      mAdapters.increment( dAtoi( tempString ) );
   }

   U32 adapterNum = 0;
   for( Vector<PVIAdapter>::iterator itr = mAdapters.begin(); itr != mAdapters.end(); itr++ )
   {
      PVIAdapter &adapter = *itr;

      
      U32 querySuccessFlags = U32_MAX;
      AssertFatal( PVI_QueryCount < sizeof( querySuccessFlags ) * 8, "Not enough bits in query success mask." );
      querySuccessFlags -= ( ( 1 << PVI_QueryCount ) - 1 );
      
      // Fill in adapter information
#define _QUERY_MASK_HELPER( querytype, outstringaddr ) \
      querySuccessFlags |= ( _queryProperty( querytype, adapterNum, outstringaddr ) ? 1 << querytype : 0 )

      _QUERY_MASK_HELPER( PVI_NumDevices, &tempString );
      adapter.numDevices = dAtoi( tempString );

      _QUERY_MASK_HELPER( PVI_VRAM, &tempString );
      adapter.vram = dAtoi( tempString );

      _QUERY_MASK_HELPER( PVI_Description, &adapter.description );
      _QUERY_MASK_HELPER( PVI_Name, &adapter.name );
      _QUERY_MASK_HELPER( PVI_ChipSet, &adapter.chipSet );
      _QUERY_MASK_HELPER( PVI_DriverVersion, &adapter.driverVersion );

#undef _QUERY_MASK_HELPER

      // Test flags here for success

      ++adapterNum;
   }

   return true;
}

//------------------------------------------------------------------------------

const PlatformVideoInfo::PVIAdapter &PlatformVideoInfo::getAdapterInformation( const U32 adapterIndex ) const
{
   AssertFatal( adapterIndex < mAdapters.size(), "Not that many adapters" );
   return mAdapters[adapterIndex];
}