// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/strings/stringFunctions.h"
#include "console/console.h"
#include "platformWin32/platformWin32.h"


void initDisplayDeviceInfo()
{
   Con::printf( "Reading Display Device information..." );

   U8 i = 0;

   DISPLAY_DEVICEA ddData;
   ddData.cb = sizeof( DISPLAY_DEVICEA );

   // Search for the primary display adapter, because that is what the rendering
   // context will get created on.
   while( EnumDisplayDevicesA( NULL, i, &ddData, 0 ) != 0 )
   {
      // If we find the primary display adapter, break out
      if( ddData.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE )
         break;

      i++;
   }

   Con::printf( "   Primary Display Device Found:" );

   // Ok, now we have the primary display device. Parse the device information.
   char ven[9];
   char dev[9];

   ven[8] = dev[8] = '\0';

   // It may seem a bit silly here to cast, but there are two implimentations in Platform.h
   // This usage is the "const" version...
   char *pos = dStrstr( ddData.DeviceID, (const char *)"VEN_");

   dStrncpy( ven, ( pos ) ? pos : "VEN_0000", 8 );

   Con::printf( "      Vendor Id: %s", ven );

   pos = dStrstr( ddData.DeviceID, (const char *)"DEV_" );

   dStrncpy( dev, ( pos ) ? pos : "DEV_0000", 8 );

   Con::printf( "      Device Id: %s", dev );

   // We now have the information, set them to console variables so we can parse
   // the file etc in script using getField and so on.
   Con::setVariable( "$PCI_VEN", ven );
   Con::setVariable( "$PCI_DEV", dev );
}

ConsoleFunction( initDisplayDeviceInfo, void, 1, 1, "()"
				"@brief Initializes variables that track device and vendor information/IDs\n\n"
				"@ingroup Rendering")
{
   initDisplayDeviceInfo();
}