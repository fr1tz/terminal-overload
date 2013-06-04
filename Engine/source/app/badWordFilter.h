// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _H_BADWORDFILTER
#define _H_BADWORDFILTER

#include "core/util/tVector.h"

class BadWordFilter
{
private:
   struct FilterTable
   {
      U16 nextState[26]; // only 26 alphabetical chars.
      FilterTable();
   };
   friend struct FilterTable;
   Vector<FilterTable*> filterTables;

   enum {
      TerminateNotFound = 0xFFFE,
      TerminateFound = 0xFFFF,
      MaxBadwordLength = 32,
   };
   char defaultReplaceStr[32];

   BadWordFilter();
   ~BadWordFilter();
   U32 curOffset;
   static U8 remapTable[257];
   static U8 randomJunk[MaxBadwordLength + 1];
   static bool filteringEnabled;

public:
   bool addBadWord(const char *word);
   bool setDefaultReplaceStr(const char *str);
   const char* getDefaultReplaceStr(){ return defaultReplaceStr; }
   void filterString(char *string, const char *replaceStr = NULL);
   bool containsBadWords(const char *string);

   static bool isEnabled() { return filteringEnabled; }
   static void setEnabled(bool enable) { filteringEnabled = enable; }
   static void create();
   static void destroy();
};

extern BadWordFilter *gBadWordFilter;

#endif