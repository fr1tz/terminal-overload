// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "scene/reflectionMatHook.h"

#include "materials/materialManager.h"
#include "materials/customMaterialDefinition.h"
#include "materials/materialFeatureTypes.h"
#include "materials/materialFeatureData.h"
#include "shaderGen/featureType.h"
#include "shaderGen/featureMgr.h"
#include "scene/sceneRenderState.h"


const MatInstanceHookType ReflectionMaterialHook::Type( "Reflection" );

ReflectionMaterialHook::ReflectionMaterialHook() : 
   mReflectMat(NULL)
{

}

ReflectionMaterialHook::~ReflectionMaterialHook()
{
   SAFE_DELETE(mReflectMat);
}

void ReflectionMaterialHook::init( BaseMatInstance *inMat )
{
   if( !inMat->isValid() )
      return;

   Material *reflectMat = (Material*)inMat->getMaterial();
   if ( inMat->isCustomMaterial() )
   {
      // This is a custom material... who knows what it really does...do something
      // smart here later.
   }

   // We may want to disable some states that the material might enable for us.
   GFXStateBlockDesc refractState = inMat->getUserStateBlock();

   // Always z-read, and z-write if the material isn't translucent
   refractState.setZReadWrite( true, reflectMat->isTranslucent() ? false : true );
   
   // Create reflection material instance.
   BaseMatInstance *newMat = new ReflectionMatInstance( reflectMat );
   newMat->setUserObject( inMat->getUserObject() );
   newMat->getFeaturesDelegate().bind( &ReflectionMaterialHook::_overrideFeatures );
   newMat->addStateBlockDesc( refractState );
   if( !newMat->init( inMat->getFeatures(), inMat->getVertexFormat() ) )
   {
      SAFE_DELETE( newMat );
      newMat = MATMGR->createWarningMatInstance();
   }
   
   mReflectMat = newMat;
}

void ReflectionMaterialHook::_overrideFeatures(  ProcessedMaterial *mat,
                                             U32 stageNum,
                                             MaterialFeatureData &fd, 
                                             const FeatureSet &features )
{
   // First stage only in reflections
   if( stageNum != 0 )
   {
      fd.features.clear();
      return;
   }

   // Forward shading on materials in reflections
   fd.features.addFeature( MFT_ForwardShading );
   fd.features.addFeature( MFT_Fog );
}

//------------------------------------------------------------------------------

ReflectionMatInstance::ReflectionMatInstance( Material *mat ) 
 : MatInstance( *mat )
{

}

bool ReflectionMatInstance::setupPass( SceneRenderState *state, const SceneData &sgData )
{
   return Parent::setupPass(state, sgData);
}
