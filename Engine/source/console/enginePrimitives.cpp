// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/enginePrimitives.h"
#include "console/engineTypeInfo.h"


IMPLEMENT_PRIMITIVE( bool,          bool,,      "Boolean true/false." );
IMPLEMENT_PRIMITIVE( S8,            byte,,      "8bit signed integer." );
IMPLEMENT_PRIMITIVE( U8,            ubyte,,     "8bit unsigned integer." );
IMPLEMENT_PRIMITIVE( S32,           int,,       "32bit signed integer." );
IMPLEMENT_PRIMITIVE( U32,           uint,,      "32bit unsigned integer." );
IMPLEMENT_PRIMITIVE( F32,           float,,     "32bit single-precision floating-point." );
IMPLEMENT_PRIMITIVE( F64,           double,,    "64bit double-precision floating-point." );
IMPLEMENT_PRIMITIVE( String,        string,,    "Null-terminated UTF-16 Unicode string." );
IMPLEMENT_PRIMITIVE( void*,         ptr,,       "Opaque pointer." );
