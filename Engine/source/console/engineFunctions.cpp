// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/engineFunctions.h"


IMPLEMENT_NONINSTANTIABLE_CLASS( EngineFunctionInfo,
   "Information about an engine function." )
END_IMPLEMENT_CLASS;


EngineFunctionInfo* EngineFunctionInfo::smFirstFunction;


//-----------------------------------------------------------------------------

EngineFunctionInfo::EngineFunctionInfo(   const char* name,
                                          EngineExportScope* scope,
                                          const char* docString,
                                          const char* prototypeString,
                                          const char* bindingName,
                                          const EngineTypeInfo* functionType,
                                          const EngineFunctionDefaultArguments* defaultArgs,
                                          void* address,
                                          U32 flags )
   : SuperType( name, EngineExportKindFunction, scope, docString ),
     mBindingName( bindingName ),
     mFunctionType( functionType ),
     mDefaultArgumentValues( defaultArgs ),
     mFunctionFlags( flags ),
     mPrototypeString( prototypeString ),
     mNextFunction( smFirstFunction ),
     mAddress( address )
{
   AssertFatal( functionType, "EngineFunctionInfo - Function cannot have void type!" );
   smFirstFunction = this;
}

//-----------------------------------------------------------------------------

void EngineFunctionInfo::resetAllCallouts()
{
   for( EngineFunctionInfo* function = smFirstFunction; function != NULL; function = function->mNextFunction )
      if( function->isCallout() )
         *reinterpret_cast< void** >( function->mAddress ) = NULL;
}
