// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PIXSPECULAR_GLSL_H_
#define _PIXSPECULAR_GLSL_H_

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
#endif


/// A per-pixel specular feature.
class PixelSpecularGLSL : public ShaderFeatureGLSL
{
protected:

   ShaderIncludeDependency mDep;

public:

   PixelSpecularGLSL();

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
class SpecularMapGLSL : public ShaderFeatureGLSL
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
