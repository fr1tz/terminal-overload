// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platformX86UNIX/platformX86UNIX.h"
#include "core/strings/stringFunctions.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>


char *stristr(char *szStringToBeSearched, const char *szSubstringToSearchFor)
{
   char *pPos = NULL;
   char *szCopy1 = NULL;
   char *szCopy2 = NULL;

   // verify parameters
   if ( szStringToBeSearched == NULL ||
        szSubstringToSearchFor == NULL )
   {
      return szStringToBeSearched;
   }

   // empty substring - return input (consistent with strstr)
   if (strlen(szSubstringToSearchFor) == 0 ) {
      return szStringToBeSearched;
   }

   szCopy1 = dStrlwr(strdup(szStringToBeSearched));
   szCopy2 = dStrlwr(strdup(szSubstringToSearchFor));

   if ( szCopy1 == NULL || szCopy2 == NULL  ) {
      // another option is to raise an exception here
      free((void*)szCopy1);
      free((void*)szCopy2);
      return NULL;
   }

   pPos = strstr(szCopy1, szCopy2);

   if ( pPos != NULL ) {
      // map to the original string
      pPos = szStringToBeSearched + (pPos - szCopy1);
   }

   free((void*)szCopy1);
   free((void*)szCopy2);

   return pPos;
} // stristr(...)

