// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SIMFIELDDICTIONARY_H_
#define _SIMFIELDDICTIONARY_H_

// Forward Refs
class ConsoleBaseType;
class SimObject;

#include "core/stringTable.h"
#include "core/stream/stream.h"

#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif

/// Dictionary to keep track of dynamic fields on SimObject.
class SimFieldDictionary
{
   friend class SimFieldDictionaryIterator;

public:
   struct Entry
   {
      Entry() : type( NULL ) {};

      StringTableEntry slotName;
      char *value;
      Entry *next;
      ConsoleBaseType *type;
   };
private:
   enum
   {
      HashTableSize = 19
   };
   Entry *mHashTable[HashTableSize];

   static Entry   *smFreeList;

   void           freeEntry(Entry *entry);
   Entry*         addEntry( U32 bucket, StringTableEntry slotName, ConsoleBaseType* type, char* value = 0 );

   static U32     getHashValue( StringTableEntry slotName );
   static U32     getHashValue( const String& fieldName );

   U32   mNumFields;

   /// In order to efficiently detect when a dynamic field has been
   /// added or deleted, we increment this every time we add or
   /// remove a field.
   U32 mVersion;

public:
   const U32 getVersion() const { return mVersion; }

   SimFieldDictionary();
   ~SimFieldDictionary();
   void setFieldType(StringTableEntry slotName, const char *typeString);
   void setFieldType(StringTableEntry slotName, const U32 typeId);
   void setFieldType(StringTableEntry slotName, ConsoleBaseType *type);
   void setFieldValue(StringTableEntry slotName, const char *value);
   const char *getFieldValue(StringTableEntry slotName);
   U32 getFieldType(StringTableEntry slotName) const;
   Entry  *findDynamicField(const String &fieldName) const;
   Entry  *findDynamicField( StringTableEntry fieldName) const;
   void writeFields(SimObject *obj, Stream &strem, U32 tabStop);
   void printFields(SimObject *obj);
   void assignFrom(SimFieldDictionary *dict);
   U32   getNumFields() const { return mNumFields; }

   Entry  *operator[](U32 index);
};

class SimFieldDictionaryIterator
{
   SimFieldDictionary *          mDictionary;
   S32                           mHashIndex;
   SimFieldDictionary::Entry *   mEntry;

public:
   SimFieldDictionaryIterator(SimFieldDictionary*);
   SimFieldDictionary::Entry* operator++();
   SimFieldDictionary::Entry* operator*();
};


#endif // _SIMFIELDDICTIONARY_H_
