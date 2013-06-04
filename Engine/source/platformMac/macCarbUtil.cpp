// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include <ApplicationServices/ApplicationServices.h>
#include <CoreServices/CoreServices.h>

#include "platform/platform.h"
#include "core/strings/stringFunctions.h"

void Platform::outputDebugString( const char *string, ... )
{
#ifdef TORQUE_DEBUG
   char buffer[ 2048 ];
   
   va_list args;
   va_start( args, string );
   
   dVsprintf( buffer, sizeof( buffer ), string, args );
   va_end( args );

   U32 length = strlen( buffer );
   if( length == ( sizeof( buffer ) - 1 ) )
      length --;

   buffer[ length ]     = '\n';
   buffer[ length + 1 ] = '\0';

   fputs( buffer, stderr );
   fflush(stderr);
#endif
}

#pragma mark ---- Platform utility funcs ----
//--------------------------------------
// Web browser function:
//--------------------------------------
bool Platform::openWebBrowser( const char* webAddress )
{
   OSStatus err;
   CFURLRef url = CFURLCreateWithBytes(NULL,(UInt8*)webAddress,dStrlen(webAddress),kCFStringEncodingASCII,NULL);
   err = LSOpenCFURLRef(url,NULL);
   CFRelease(url);

   return(err==noErr);
}

