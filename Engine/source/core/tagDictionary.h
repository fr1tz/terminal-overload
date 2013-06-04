// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TAGDICTIONARY_H_
#define _TAGDICTIONARY_H_

#ifndef _STRINGTABLE_H_
#include "core/stringTable.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

class Stream;

class TagDictionary
{
   struct TagEntry
   {
      S32 id;
      StringTableEntry define;
      StringTableEntry string;
      TagEntry *chain; // for linear traversal
      TagEntry *defineHashLink;
      TagEntry *idHashLink;
   };

   TagEntry **defineHashBuckets;
   TagEntry **idHashBuckets;

   TagEntry *entryChain;
   DataChunker mempool;
   S32 numBuckets;
   S32 numEntries;

   bool match(const char* pattern, const char* str);
   void sortIdVector(Vector<S32>& out_v);
public:
   TagDictionary();
   ~TagDictionary();
   
	//IO functions
	//
   bool writeHeader(Stream &);

   // String/Define retrieval and search functions...
   //

   bool addEntry(S32 value, StringTableEntry define, StringTableEntry string);
   
   StringTableEntry defineToString(StringTableEntry tag);
   StringTableEntry idToString(S32 tag);
   StringTableEntry idToDefine(S32 tag);
   S32 defineToId(StringTableEntry tag);

   // get IDs such that minID < IDs < maxID 
   void findIDs( Vector<S32> &v, const S32 minID, const S32 maxID );
	void findStrings( Vector<S32> &v, const char *pattern);
	void findDefines( Vector<S32> &v, const char *pattern);
};

extern TagDictionary tagDictionary;

#endif //_TAGDICTIONARY_H_
