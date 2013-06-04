// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "app/version.h"
#include "console/console.h"

static const U32 csgVersionNumber = TORQUE_GAME_ENGINE;
static const U32 appVersionNumber = TORQUE_APP_VERSION;

U32 getVersionNumber()
{
   return csgVersionNumber;
}

U32 getAppVersionNumber()
{
   return appVersionNumber;
}

const char* getVersionString()
{
   return TORQUE_GAME_ENGINE_VERSION_STRING;
}

const char* getAppVersionString()
{
   return TORQUE_APP_VERSION_STRING;
}

/// TGE       0001
/// TGEA      0002
/// TGB       0003
/// TGEA 360  0004
/// TGE  WII  0005
/// Torque 3D 0006
/// Torque 3D MIT 0007

const char* getEngineProductString()
{
#ifndef TORQUE_ENGINE_PRODUCT
   return "Torque Engine";
#else
   switch (TORQUE_ENGINE_PRODUCT)
   {
      case 0001:
         return "Torque Game Engine";
      case 0002:
         return "Torque Game Engine Advanced";
      case 0003:
         return "Torque 2D";
      case 0004:
         return "Torque 360";
      case 0005:
         return "Torque for Wii";
      case 0006:
         return "Torque 3D";
      case 0007:
	     return "Torque 3D MIT";
		 
      default:
         return "Torque Engine";
   };
#endif
}

const char* getCompileTimeString()
{
   return __DATE__ " at " __TIME__;
}
//----------------------------------------------------------------

ConsoleFunctionGroupBegin( CompileInformation, "Functions to get version information about the current executable." );

ConsoleFunction( getVersionNumber, S32, 1, 1, "Get the version of the engine build, as a string.\n\n"
				"@ingroup Debugging")
{
   return getVersionNumber();
}

ConsoleFunction( getAppVersionNumber, S32, 1, 1, "Get the version of the application build, as a string.\n\n"
            "@ingroup Debugging")
{
   return getAppVersionNumber();
}


ConsoleFunction( getVersionString, const char*, 1, 1, "Get the version of the engine build, as a human readable string.\n\n"
				"@ingroup Debugging")
{
   return getVersionString();
}

ConsoleFunction( getAppVersionString, const char*, 1, 1, "Get the version of the aplication, as a human readable string.\n\n"
            "@ingroup Debugging")
{
   return getAppVersionString();
}

ConsoleFunction( getEngineName, const char*, 1, 1, "Get the name of the engine product that this is running from, as a string.\n\n"
				"@ingroup Debugging")
{
   return getEngineProductString();
}

ConsoleFunction( getCompileTimeString, const char*, 1, 1, "Get the time of compilation.\n\n"
				"@ingroup Debugging")
{
   return getCompileTimeString();
}

ConsoleFunction( getBuildString, const char*, 1, 1, "Get the type of build, \"Debug\" or \"Release\".\n\n"
				"@ingroup Debugging")
{
#ifdef TORQUE_DEBUG
   return "Debug";
#else
   return "Release";
#endif
}

ConsoleFunctionGroupEnd( CompileInformation );

ConsoleFunction(isDemo, bool, 1, 1, "")
{
#ifdef TORQUE_DEMO
   return true;
#else
   return false;
#endif
}

ConsoleFunction(isWebDemo, bool, 1, 1, "")
{
#ifdef TORQUE_DEMO
   return Platform::getWebDeployment();
#else
   return false;
#endif
}