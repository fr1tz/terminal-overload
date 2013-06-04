// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gfx/gfxDevice.h"


GFXVideoMode::GFXVideoMode()
{
   bitDepth = 32;
   fullScreen = false;
   refreshRate = 60;
   wideScreen = false;
   resolution.set(800,600);
   antialiasLevel = 0;
}

void GFXVideoMode::parseFromString( const char *str )
{
   if(!str)
      return;

   // Copy the string, as dStrtok is destructive
   char *tempBuf = new char[dStrlen( str ) + 1];
   dStrcpy( tempBuf, str );

#define PARSE_ELEM(type, var, func, tokParam, sep) \
   if(const char *ptr = dStrtok( tokParam, sep)) \
   { type tmp = func(ptr); if(tmp > 0) var = tmp; }

   PARSE_ELEM(S32, resolution.x, dAtoi, tempBuf, " x\0")
   PARSE_ELEM(S32, resolution.y, dAtoi, NULL,    " x\0")
   PARSE_ELEM(S32, fullScreen,   dAtob, NULL,    " \0")
   PARSE_ELEM(S32, bitDepth,     dAtoi, NULL,    " \0")
   PARSE_ELEM(S32, refreshRate,  dAtoi, NULL,    " \0")
   PARSE_ELEM(S32, antialiasLevel, dAtoi, NULL,    " \0")

#undef PARSE_ELEM

   delete [] tempBuf;
}

const String GFXVideoMode::toString() const
{
   return String::ToString("%d %d %s %d %d %d", resolution.x, resolution.y, (fullScreen ? "true" : "false"), bitDepth,  refreshRate, antialiasLevel);
}

void GFXShaderMacro::stringize( const Vector<GFXShaderMacro> &macros, String *outString )
{
   Vector<GFXShaderMacro>::const_iterator itr = macros.begin();
   for ( ; itr != macros.end(); itr++ )
   {
      (*outString) += itr->name;
      if ( itr->value.isNotEmpty() )
      {
         (*outString) += "=";
         (*outString) += itr->value;
      }
      (*outString) += ";";
   }
}