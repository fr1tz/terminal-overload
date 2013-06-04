// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/engineTypes.h"
#include "console/engineExports.h"

const EngineTypeInfo* const _EngineTypeTraits< void >::TYPEINFO = NULL;
EngineExportScope& _GLOBALSCOPE::__engineExportScope()
{
   return EngineExportScope::smGlobalScope;
}
