// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PIXSPECULAR_HLSL_H_
#define _PIXSPECULAR_HLSL_H_

#ifndef _SHADERGEN_HLSL_SHADERFEATUREHLSL_H_
#include "shaderGen/HLSL/shaderFeatureHLSL.h"
#endif


/// A per-pixel specular feature.
class PixelSpecularHLSL : public ShaderFeatureHLSL
{
protected:

   ShaderIncludeDependency mDep;

public:

   PixelSpecularHLSL();

   virtual void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd );

   virtual void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd );

   virtual Resources getResources( const MaterialFeatureData &fd );
   
   virtual String getName()
   {
      return "Pixel Specular";
   }
};

/// A texture source for the PixSpecular feature
class SpecularMapHLSL : public ShaderFeatureHLSL
{

public:
   virtual void processPix( Vector<ShaderComponent*> &componentList, 
      const MaterialFeatureData &fd );

   virtual Resources getResources( const MaterialFeatureData &fd );

   virtual void setTexData( Material::StageData &stageDat,
      const MaterialFeatureData &fd,
      RenderPassData &passData,
      U32 &texIndex );

   virtual String getName()
   {
      return "Specular Map";
   }
};

#endif // _PIXSPECULAR_HLSL_H_