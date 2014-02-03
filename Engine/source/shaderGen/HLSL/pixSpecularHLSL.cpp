// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "shaderGen/HLSL/pixSpecularHLSL.h"
#include "materials/processedMaterial.h"
#include "materials/materialFeatureTypes.h"
#include "shaderGen/shaderOp.h"
#include "shaderGen/shaderGenVars.h"
#include "gfx/gfxStructs.h"


PixelSpecularHLSL::PixelSpecularHLSL()
   : mDep( "shaders/common/lighting.hlsl" )
{
   addDependency( &mDep );
}

void PixelSpecularHLSL::processVert(   Vector<ShaderComponent*> &componentList, 
                                       const MaterialFeatureData &fd )
{
   AssertFatal( fd.features[MFT_RTLighting], 
      "PixelSpecularHLSL requires RTLighting to be enabled!" );

   // Nothing to do here... MFT_RTLighting should have
   // taken care of passing everything to the pixel shader.
}

void PixelSpecularHLSL::processPix( Vector<ShaderComponent*> &componentList, 
                                    const MaterialFeatureData &fd )
{
   AssertFatal( fd.features[MFT_RTLighting], 
      "PixelSpecularHLSL requires RTLighting to be enabled!" );

   // RTLighting should have spit out the 4 specular
   // powers for the 4 potential lights on this pass.
   // 
   // This can sometimes be NULL if RTLighting skips out
   // on us for lightmaps or missing normals.
   Var *specular = (Var*)LangElement::find( "specular" );
   if ( !specular )
      return;

   MultiLine *meta = new MultiLine;

   LangElement *specMul = new GenOp( "@", specular );
   LangElement *final = specMul;

   // mask out with lightmap if present
   if ( fd.features[MFT_LightMap] )
   {
      LangElement *lmColor = NULL;

      // find lightmap color
      lmColor = LangElement::find( "lmColor" );

      if ( !lmColor )
      {
         LangElement * lightMap = LangElement::find( "lightMap" );
         LangElement * lmCoord = LangElement::find( "texCoord2" );

         lmColor = new GenOp( "tex2D(@, @)", lightMap, lmCoord );
      }

      final = new GenOp( "@ * float4(@.rgb,0)", specMul, lmColor );
   }

   // If we have a normal map then mask the specular
   if ( fd.features[MFT_SpecularMap] )
   {
      Var *specularColor = (Var*)LangElement::find( "specularColor" );
      if (specularColor)
         final = new GenOp( "@ * @", final, specularColor );
   }
   else if ( fd.features[MFT_NormalMap] && !fd.features[MFT_IsDXTnm] )
   {
      Var *bumpColor = (Var*)LangElement::find( "bumpNormal" );
      final = new GenOp( "@ * @.a", final, bumpColor );
   }

   // Add the specular to the final color.
   // search for color var
   Var *color = (Var*)LangElement::find( "col" );   
   meta->addStatement( new GenOp( "   @.rgb += ( @ ).rgb;\r\n", color, final ) );

   output = meta;
}

ShaderFeature::Resources PixelSpecularHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res;
   return res;
}


void SpecularMapHLSL::processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd )
{
   // Get the texture coord.
   Var *texCoord = getInTexCoord( "texCoord", "float2", true, componentList );

   // create texture var
   Var *specularMap = new Var;
   specularMap->setType( "sampler2D" );
   specularMap->setName( "specularMap" );
   specularMap->uniform = true;
   specularMap->sampler = true;
   specularMap->constNum = Var::getTexUnitNum();
   LangElement *texOp = new GenOp( "tex2D(@, @)", specularMap, texCoord );

   Var *specularColor = new Var( "specularColor", "float4" );

   output = new GenOp( "   @ = @;\r\n", new DecOp( specularColor ), texOp );
}

ShaderFeature::Resources SpecularMapHLSL::getResources( const MaterialFeatureData &fd )
{
   Resources res;
   res.numTex = 1;
   return res;
}

void SpecularMapHLSL::setTexData( Material::StageData &stageDat,
                                 const MaterialFeatureData &fd,
                                 RenderPassData &passData,
                                 U32 &texIndex )
{
   GFXTextureObject *tex = stageDat.getTex( MFT_SpecularMap );
   if ( tex )
   {
      passData.mTexType[ texIndex ] = Material::Standard;
      passData.mSamplerNames[ texIndex ] = "specularMap";
      passData.mTexSlot[ texIndex++ ].texObject = tex;
   }
}