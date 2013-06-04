// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "console/dynamicTypes.h"
#include "core/stringTable.h"
#include "core/strings/stringFunctions.h"


ConsoleBaseType* ConsoleBaseType::smListHead = NULL;
S32 ConsoleBaseType::smConsoleTypeCount = 0;

// And, we also privately store the types lookup table.
static VectorPtr< ConsoleBaseType* > gConsoleTypeTable( __FILE__, __LINE__ );


//-----------------------------------------------------------------------------

ConsoleBaseType::ConsoleBaseType( const S32 size, S32 *idPtr, const char *aTypeName )
   :  mInspectorFieldType( NULL ),
      mTypeSize( size ),
      mTypeInfo( NULL )
{
   mTypeName = StringTable->insert( aTypeName );
   mTypeID = smConsoleTypeCount++;
   *idPtr = mTypeID;

   // Link ourselves into the list.
   mListNext = smListHead;
   smListHead = this;
}

//-----------------------------------------------------------------------------

ConsoleBaseType *ConsoleBaseType::getListHead()
{
   return smListHead;
}

//-----------------------------------------------------------------------------

void ConsoleBaseType::initialize()
{
   // Prep and empty the vector.
   gConsoleTypeTable.setSize(smConsoleTypeCount+1);
   dMemset(gConsoleTypeTable.address(), 0, sizeof(ConsoleBaseType*) * gConsoleTypeTable.size());

   // Walk the list and register each one with the console system.
   ConsoleBaseType *walk = getListHead();
   while(walk)
   {
      const S32 id = walk->getTypeID();
      AssertFatal(gConsoleTypeTable[id]==NULL, "ConsoleBaseType::initialize - encountered a table slot that contained something!");
      gConsoleTypeTable[id] = walk;
  
      walk = walk->getListNext();
   }
}

//-----------------------------------------------------------------------------

ConsoleBaseType* ConsoleBaseType::getType(const S32 typeID)
{
   if( typeID == -1 || gConsoleTypeTable.size() <= typeID )
      return NULL;
      
   return gConsoleTypeTable[ typeID ];
}

//-----------------------------------------------------------------------------

ConsoleBaseType* ConsoleBaseType::getTypeByName(const char *typeName)
{
   ConsoleBaseType* walk = getListHead();
   while( walk != NULL )
   {
      if( dStrcmp( walk->getTypeName(), typeName ) == 0 )
         return walk;

      walk = walk->getListNext();
   }

   return NULL;
}

//-----------------------------------------------------------------------------

ConsoleBaseType * ConsoleBaseType::getTypeByClassName(const char *typeName)
{
   ConsoleBaseType *walk = getListHead();
   while( walk != NULL )
   {
      if( dStrcmp( walk->getTypeClassName(), typeName ) == 0 )
         return walk;

      walk = walk->getListNext();
   }

   return NULL;
}
