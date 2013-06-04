// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platformMac/platformMacCarb.h"
#include "platform/platform.h"
#include "console/console.h"
#include "math/mMath.h"
#include "core/strings/stringFunctions.h"

extern void mInstallLibrary_C();
extern void mInstallLibrary_Vec();
extern void mInstall_Library_SSE();

static MRandomLCG sgPlatRandom;

U32 Platform::getMathControlState()
{
   return 0;
}

void Platform::setMathControlStateKnown()
{
   
}

void Platform::setMathControlState(U32 state)
{
   
}

//--------------------------------------
ConsoleFunction( MathInit, void, 1, 10, "(DETECT|C|VEC|SSE)")
{
   U32 properties = CPU_PROP_C;  // C entensions are always used
   
   if (argc == 1)
   {
         Math::init(0);
         return;
   }
   for (argc--, argv++; argc; argc--, argv++)
   {
      if (dStricmp(*argv, "DETECT") == 0) { 
         Math::init(0);
         return;
      }
      if (dStricmp(*argv, "C") == 0) { 
         properties |= CPU_PROP_C; 
         continue; 
      }
      if (dStricmp(*argv, "VEC") == 0) { 
         properties |= CPU_PROP_ALTIVEC; 
         continue; 
      }
      if( dStricmp( *argv, "SSE" ) == 0 )
      {
         properties |= CPU_PROP_SSE;
         continue;
      }
      Con::printf("Error: MathInit(): ignoring unknown math extension '%s'", *argv);
   }
   Math::init(properties);
}



//------------------------------------------------------------------------------
void Math::init(U32 properties)
{
   if (!properties)
      // detect what's available
      properties = Platform::SystemInfo.processor.properties;  
   else
      // Make sure we're not asking for anything that's not supported
      properties &= Platform::SystemInfo.processor.properties;  

   Con::printf("Math Init:");
   Con::printf("   Installing Standard C extensions");
   mInstallLibrary_C();
   
   #if defined(__VEC__)
   if (properties & CPU_PROP_ALTIVEC)
   {
      Con::printf("   Installing Altivec extensions");
      mInstallLibrary_Vec();
   }
   #endif
   #ifdef TORQUE_CPU_X86
   if( properties & CPU_PROP_SSE )
   {
      Con::printf( "   Installing SSE extensions" );
      mInstall_Library_SSE();
   }
   #endif
   
   Con::printf(" ");
}   

//------------------------------------------------------------------------------
F32 Platform::getRandom()
{
   return sgPlatRandom.randF();
}

