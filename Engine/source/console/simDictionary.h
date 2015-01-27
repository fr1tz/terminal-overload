// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SIMDICTIONARY_H_
#define _SIMDICTIONARY_H_
#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _STRINGTABLE_H_
#include "core/stringTable.h"
#endif

#ifndef _PLATFORMMUTEX_H_
#include "platform/threads/mutex.h"
#endif

#include "torqueConfig.h"

class SimObject;

#ifdef USE_NEW_SIMDICTIONARY
#include <string>
#include <unordered_map>

#ifndef _SIM_H_
#include "console/sim.h"
#endif

struct StringTableEntryHash
{
   inline size_t operator()(StringTableEntry val) const
   {
      return (size_t)val;
   }
};

struct StringTableEntryEq
{
   inline bool operator()(StringTableEntry s1, StringTableEntry s2) const
   {
      return s1 == s2;
   }
};

typedef std::unordered_map<StringTableEntry, SimObject*, StringTableEntryHash, StringTableEntryEq> StringDictDef;	
typedef std::unordered_map<SimObjectId, SimObject*> SimObjectIdDictDef;
#endif

//----------------------------------------------------------------------------
/// Map of names to SimObjects
///
/// Provides fast lookup for name->object and
/// for fast removal of an object given object*
class SimNameDictionary
{
#ifndef USE_NEW_SIMDICTIONARY
   enum
   {
      DefaultTableSize = 29
   };

   SimObject **hashTable;  // hash the pointers of the names...
   S32 hashTableSize;
   S32 hashEntryCount;
#else
   StringDictDef root;
#endif

   void *mutex;

public:
   void insert(SimObject* obj);
   void remove(SimObject* obj);
   SimObject* find(StringTableEntry name);

   SimNameDictionary();
   ~SimNameDictionary();
};

class SimManagerNameDictionary
{
#ifndef USE_NEW_SIMDICTIONARY
   enum
   {
      DefaultTableSize = 29
   };

   SimObject **hashTable;  // hash the pointers of the names...
   S32 hashTableSize;
   S32 hashEntryCount;
#else
   StringDictDef root;
#endif

   void *mutex;

public:
   void insert(SimObject* obj);
   void remove(SimObject* obj);
   SimObject* find(StringTableEntry name);

   SimManagerNameDictionary();
   ~SimManagerNameDictionary();
};

//----------------------------------------------------------------------------
/// Map of ID's to SimObjects.
///
/// Provides fast lookup for ID->object and
/// for fast removal of an object given object*
class SimIdDictionary
{
#ifndef USE_NEW_SIMDICTIONARY
   enum
   {
      DefaultTableSize = 4096,
      TableBitMask = 4095
   };
   SimObject *table[DefaultTableSize];
#else
   SimObjectIdDictDef root;
#endif

   void *mutex;

public:
   void insert(SimObject* obj);
   void remove(SimObject* obj);
   SimObject* find(S32 id);

   SimIdDictionary();
   ~SimIdDictionary();
};

#endif //_SIMDICTIONARY_H_
