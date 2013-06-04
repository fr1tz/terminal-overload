// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/engineTypeInfo.h"
#include "console/engineAPI.h"
#include "core/strings/stringFunctions.h"


IMPLEMENT_ENUM( EngineTypeKind,
   EngineTypeKind, ReflectionAPI,
   "Kinding for engine types.  Engine types are segregated into kinds which "
   "are to types what types are to values, i.e. a value is an instance of a type "
   "and a type is an instance of a kind.\n"
   "@internal\n\n")
   { EngineTypeKindPrimitive, "Primitive", "Atomic data." },
   { EngineTypeKindEnum, "Enum", "Enumeration." },
   { EngineTypeKindBitfield, "Bitfield", "Bitfield." },
   { EngineTypeKindFunction, "Function", "Function pointer." },
   { EngineTypeKindStruct, "Struct", "Structured value." },
   { EngineTypeKindClass, "Class", "EngineObject value." },
END_IMPLEMENT_ENUM;

IMPLEMENT_NONINSTANTIABLE_CLASS( EngineTypeInfo,
   "Information about an engine type." )
   PROPERTY( TypeKind, 1, "Kind of type.", 0 )
   PROPERTY( SuperType, 1, "Type that this type subtypes from.", 0 )
END_IMPLEMENT_CLASS;

U32 EngineTypeInfo::smNumTypes;
const EngineTypeInfo* EngineTypeInfo::smFirst;


//-----------------------------------------------------------------------------

EngineTypeInfo::EngineTypeInfo( const char* typeName, EngineExportScope* scope, EngineTypeKind kind, U32 instanceSize, const char* docString )
   : SuperType( typeName, scope, docString ),
     mTypeKind( kind ),
     mInstanceSize( instanceSize ),
     mNext( smFirst ),
     mEnumTable( NULL ),
     mFieldTable( NULL ),
     mPropertyTable( NULL ),
     mSuperType( NULL )
{
   mExportKind = EngineExportKindType;
   
   smFirst = this;
   smNumTypes ++;
}

//-----------------------------------------------------------------------------

const EngineTypeInfo* EngineTypeInfo::getTypeInfoByName( const char* typeName )
{
   for( const EngineTypeInfo* typeInfo = getFirstType(); typeInfo != NULL; typeInfo = typeInfo->getNextType() )
      if( dStricmp( typeInfo->getTypeName(), typeName ) == 0 )
         return typeInfo;
         
   return NULL;
}

//-----------------------------------------------------------------------------

U32 EngineTypeInfo::getValueSize() const
{
   switch( getTypeKind() )
   {
      case EngineTypeKindPrimitive:
      case EngineTypeKindEnum:
      case EngineTypeKindBitfield:
         return mInstanceSize;
         
      case EngineTypeKindStruct:
      case EngineTypeKindFunction:
      case EngineTypeKindClass:
         return sizeof( void* );
   }
   
   AssertFatal( false, "EngineTypeInfo - unknown type kind!" );
   return U32( -1 );
}

//-----------------------------------------------------------------------------

bool EngineTypeInfo::isSubtypeOf( const EngineTypeInfo* type ) const
{
   for( const EngineTypeInfo* p = this; p != NULL; p = p->getSuperType() )
      if( p == type )
         return true;
         
   return false;
}

//-----------------------------------------------------------------------------

bool EngineTypeInfo::constructInstance( void* ptr ) const
{
   AssertFatal( !isAbstract(), "EngineTypeInfo::constructInstance - Called on abstract type!" );
   return false;
}

//-----------------------------------------------------------------------------

void EngineTypeInfo::destructInstance( void* ptr ) const
{
   AssertFatal( !isAbstract(), "EngineTypeInfo::destructInstance - Called on abstract type!" );
}

//=============================================================================
//    API.
//=============================================================================
// MARK: ---- API ----

//-----------------------------------------------------------------------------

DefineNewEngineMethod( EngineTypeInfo, getTypeKind, EngineTypeKind, (),,
   "Get the kind of the type.\n"
   "@return The type kind." )
{
   return object->getTypeKind();
}

//-----------------------------------------------------------------------------

DefineNewEngineMethod( EngineTypeInfo, getSuperType, const EngineTypeInfo*, (),,
   "Get the type that this type subtypes from.\n"
   "@return The supertype info instance or NULL." )
{
   return object->getSuperType();
}
