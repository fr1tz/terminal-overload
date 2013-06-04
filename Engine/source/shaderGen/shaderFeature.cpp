// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "shaderGen/shaderFeature.h"

#include "shaderGen/langElement.h"
#include "shaderGen/shaderOp.h"


void ShaderFeature::addDependency( const ShaderDependency *dependsOn )
{
   for ( U32 i = 0; i < mDependencies.size(); i++ )
   {
      if ( *mDependencies[i] == *dependsOn )
         return;
   }

   mDependencies.push_back( dependsOn );
}

ShaderFeature::Resources ShaderFeature::getResources( const MaterialFeatureData &fd )
{
   Resources temp; 
   return temp; 
}

const char* ShaderFeature::getOutputTargetVarName( OutputTarget target ) const
{
   const char* targName = "col";
   if ( target != DefaultTarget )
   {
      targName = "col1";
      AssertFatal(target == RenderTarget1, "yeah Pat is lame and didn't want to do bit math stuff, TODO");
   }

   return targName;
}

Var* ShaderFeature::findOrCreateLocal( const char *name, 
                                       const char *type, 
                                       MultiLine *multi )
{
   Var *outVar = (Var*)LangElement::find( name );
   if ( !outVar )
   {
      outVar = new Var;
      outVar->setType( type );
      outVar->setName( name );
      multi->addStatement( new GenOp( "   @;\r\n", new DecOp( outVar ) ) );
   }

   return outVar;
}