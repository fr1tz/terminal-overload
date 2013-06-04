// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "lighting/advanced/advancedLightingFeatures.h"

#include "shaderGen/featureMgr.h"
#include "gfx/gfxStringEnumTranslate.h"
#include "materials/materialParameters.h"
#include "materials/materialFeatureTypes.h"
#include "materials/matTextureTarget.h"
#include "gfx/gfxDevice.h"
#include "core/util/safeDelete.h"

#if !defined( TORQUE_OS_MAC ) && !defined( TORQUE_OS_LINUX )
#  include "lighting/advanced/hlsl/gBufferConditionerHLSL.h"
#  include "lighting/advanced/hlsl/advancedLightingFeaturesHLSL.h"
#else
#  include "lighting/advanced/glsl/gBufferConditionerGLSL.h"
#  include "lighting/advanced/glsl/advancedLightingFeaturesGLSL.h"
#endif



bool AdvancedLightingFeatures::smFeaturesRegistered = false;

void AdvancedLightingFeatures::registerFeatures( const GFXFormat &prepassTargetFormat, const GFXFormat &lightInfoTargetFormat )
{
   AssertFatal( !smFeaturesRegistered, "AdvancedLightingFeatures::registerFeatures() - Features already registered. Bad!" );

   // If we ever need this...
   TORQUE_UNUSED(lightInfoTargetFormat);

   ConditionerFeature *cond = NULL;

   if(GFX->getAdapterType() == OpenGL)
   {
#if defined( TORQUE_OS_MAC ) || defined( TORQUE_OS_LINUX )
      cond = new GBufferConditionerGLSL( prepassTargetFormat );
      FEATUREMGR->registerFeature(MFT_PrePassConditioner, cond);
      FEATUREMGR->registerFeature(MFT_RTLighting, new DeferredRTLightingFeatGLSL());
      FEATUREMGR->registerFeature(MFT_NormalMap, new DeferredBumpFeatGLSL());
      FEATUREMGR->registerFeature(MFT_PixSpecular, new DeferredPixelSpecularGLSL());
      FEATUREMGR->registerFeature(MFT_MinnaertShading, new DeferredMinnaertGLSL());
      FEATUREMGR->registerFeature(MFT_SubSurface, new DeferredSubSurfaceGLSL());
#endif
   }
   else
   {
#if !defined( TORQUE_OS_MAC ) && !defined( TORQUE_OS_LINUX )
      cond = new GBufferConditionerHLSL( prepassTargetFormat, GBufferConditionerHLSL::ViewSpace );
      FEATUREMGR->registerFeature(MFT_PrePassConditioner, cond);
      FEATUREMGR->registerFeature(MFT_RTLighting, new DeferredRTLightingFeatHLSL());
      FEATUREMGR->registerFeature(MFT_NormalMap, new DeferredBumpFeatHLSL());
      FEATUREMGR->registerFeature(MFT_PixSpecular, new DeferredPixelSpecularHLSL());
      FEATUREMGR->registerFeature(MFT_MinnaertShading, new DeferredMinnaertHLSL());
      FEATUREMGR->registerFeature(MFT_SubSurface, new DeferredSubSurfaceHLSL());
#endif
   }

   NamedTexTarget *target = NamedTexTarget::find( "prepass" );
   if ( target )
      target->setConditioner( cond );

   smFeaturesRegistered = true;
}

void AdvancedLightingFeatures::unregisterFeatures()
{
   NamedTexTarget *target = NamedTexTarget::find( "prepass" );
   if ( target )
      target->setConditioner( NULL );

   FEATUREMGR->unregisterFeature(MFT_PrePassConditioner);
   FEATUREMGR->unregisterFeature(MFT_RTLighting);
   FEATUREMGR->unregisterFeature(MFT_NormalMap);
   FEATUREMGR->unregisterFeature(MFT_PixSpecular);
   FEATUREMGR->unregisterFeature(MFT_MinnaertShading);
   FEATUREMGR->unregisterFeature(MFT_SubSurface);

   smFeaturesRegistered = false;
}
