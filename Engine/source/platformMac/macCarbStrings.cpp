// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "core/strings/stringFunctions.h"

char *dStrnew(const char *src)
{
   char *buffer = new char[dStrlen(src) + 1];
   dStrcpy(buffer, src);
   return buffer;
} 

char* dStrstr(char *str1, char *str2)
{
   return strstr(str1,str2);
}  

int dSprintf(char *buffer, dsize_t /*bufferSize*/, const char *format, ...)
{
   va_list args;
   va_start(args, format);
   S32 len = vsprintf(buffer, format, args);

   return (len);
}   


int dVsprintf(char *buffer, dsize_t /*bufferSize*/, const char *format, void *arglist)
{
   S32 len = vsprintf(buffer, format, (char*)arglist);

   return (len);
}   

int dFflushStdout()
{
   return fflush(stdout);
}

int dFflushStderr()
{
   return fflush(stderr);
}

