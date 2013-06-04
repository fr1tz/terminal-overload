// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ENGINEPRIMITIVES_H_
#define _ENGINEPRIMITIVES_H_

#ifndef _ENGINETYPES_H_
   #include "console/engineTypes.h"
#endif


/// @file
/// Definitions for the core primitive types used in the
/// exposed engine API.



DECLARE_PRIMITIVE( bool );
DECLARE_PRIMITIVE( S8 );
DECLARE_PRIMITIVE( U8 );
DECLARE_PRIMITIVE( S32 );
DECLARE_PRIMITIVE( U32 );
DECLARE_PRIMITIVE( F32 );
DECLARE_PRIMITIVE( F64 );
DECLARE_PRIMITIVE( void* );


//FIXME: this allows String to be used as a struct field type

// String is special in the way its data is exchanged through the API.  Through
// calls, strings are passed as plain, null-terminated UTF-16 character strings.
// In addition, strings passed back as return values from engine API functions
// are considered to be owned by the API layer itself.  The rule here is that such
// a string is only valid until the next API call is made.  Usually, control layers
// will immediately copy and convert strings to their own string type.
_DECLARE_TYPE( String );
template<>
struct EngineTypeTraits< String > : public _EnginePrimitiveTypeTraits< String >
{
   typedef const UTF16* ArgumentValueType;
   typedef const UTF16* ReturnValueType;

   //FIXME: this needs to be sorted out; for now, we store default value literals in ASCII
   typedef const char* DefaultArgumentValueStoreType;
   
   static const UTF16* ReturnValue( const String& str )
   {
      static String sTemp;      
      sTemp = str;
      return sTemp.utf16();
   }
};


// For struct fields, String cannot be used directly but "const UTF16*" must be used
// instead.  Make sure this works with the template machinery by redirecting the type
// back to String.
template<> struct EngineTypeTraits< const UTF16* > : public EngineTypeTraits< String > {};
template<> inline const EngineTypeInfo* TYPE< const UTF16* >() { return TYPE< String >(); }
inline const EngineTypeInfo* TYPE( const UTF16*& ) { return TYPE< String >(); }

#endif // !_ENGINEPRIMITIVES_H_
