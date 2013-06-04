// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "ts/instancingMatHook.h"

#include "platform/profiler.h"
#include "materials/materialFeatureTypes.h"
#include "materials/matInstance.h"


const MatInstanceHookType InstancingMaterialHook::Type( "Instancing" );

InstancingMaterialHook::InstancingMaterialHook() :
   mMatInst( NULL )
{
}

InstancingMaterialHook::~InstancingMaterialHook()
{
   SAFE_DELETE( mMatInst );
}

BaseMatInstance* InstancingMaterialHook::getInstancingMat( BaseMatInstance *matInst )
{
   PROFILE_SCOPE( InstancingMaterialHook_GetInstancingMat );

   if ( matInst == NULL )
      return NULL;

   InstancingMaterialHook *hook = matInst->getHook<InstancingMaterialHook>();
   if ( hook == NULL )
   {
      hook = new InstancingMaterialHook();
      matInst->addHook( hook );

      BaseMatInstance *instMat = matInst->getMaterial()->createMatInstance();
      FeatureSet features( matInst->getRequestedFeatures() );
      features.addFeature( MFT_UseInstancing ); 

      // Allow for named texture assignments
      Material::sAllowTextureTargetAssignment = true;

      if ( !instMat->init( features, matInst->getVertexFormat() ) )
         SAFE_DELETE( instMat );

      // Turn back off named texture assignments
      Material::sAllowTextureTargetAssignment = false;

      hook->mMatInst = instMat;
   }

   return hook->mMatInst;
}
