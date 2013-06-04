// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "materials/matInstanceHook.h"


MatInstanceHookType::MatInstanceHookType( const char *type )
{
   TypeMap::Iterator iter = getTypeMap().find( type );
   if ( iter == getTypeMap().end() )
      iter = getTypeMap().insertUnique( type, getTypeMap().size() );

   mTypeIndex = iter->value;
}

