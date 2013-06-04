// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/engineExports.h"
#include "console/engineTypeInfo.h"
#include "console/engineAPI.h"


IMPLEMENT_SCOPE( ReflectionAPI, Reflection,,
   "Metadata for the exported engine API." );
   
IMPLEMENT_NONINSTANTIABLE_CLASS( EngineExport,
   "Abstract base class of entities exported through the engine API." )
END_IMPLEMENT_CLASS;
IMPLEMENT_NONINSTANTIABLE_CLASS( EngineExportScope,
   "A scope contained a collection of exported engine API entities." )
END_IMPLEMENT_CLASS;
   
EngineExportScope EngineExportScope::smGlobalScope;


//-----------------------------------------------------------------------------

EngineExport::EngineExport( const char* name, EngineExportKind kind, EngineExportScope* scope, const char* docString )
   : mExportName( name ),
     mExportKind( kind ),
     mExportScope( scope ),
     mNextExport( NULL ),
     mDocString( docString )
{
   AssertFatal( name != NULL, "EngineExport - export without name!" );
   AssertFatal( scope != NULL, avar( "EngineExport - export '%s' is in no scope" ) );
   
   // Link to scope's export chain.
   
   mNextExport = scope->mExports;
   scope->mExports = this;
}

//-----------------------------------------------------------------------------

String EngineExport::getFullyQualifiedExportName() const
{
   if( getExportScope() )
   {
      String parentQualifiedName = getExportScope()->getFullyQualifiedExportName();
      if( parentQualifiedName.isEmpty() )
         return getExportName();
         
      return String::ToString( "%s::%s", parentQualifiedName.c_str(), getExportName() );
   }
      
   return getExportName();
}

//-----------------------------------------------------------------------------

EngineExportScope::EngineExportScope( const char* name, EngineExportScope* scope, const char* docString )
   : SuperType( name, EngineExportKindScope, scope, docString )
{
   // Do *NOT* initialize mExports here.  EngineExportScopes should be
   // instantiated globally and by not initializing the field, we allow
   // exports to link themselves to their scope without being order dependent
   // on our constructor.
}
