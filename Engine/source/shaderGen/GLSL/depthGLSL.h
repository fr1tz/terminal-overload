// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _DEPTH_GLSL_H_
#define _DEPTH_GLSL_H_

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
#endif
#ifndef _SHADEROP_H_
#include "shaderGen/shaderOp.h"
#endif


class EyeSpaceDepthOutGLSL : public ShaderFeatureGLSL
{
public:

   // ShaderFeature
   virtual void processVert( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual Resources getResources( const MaterialFeatureData &fd );
   virtual String getName() { return "Eye Space Depth (Out)"; }
   virtual Material::BlendOp getBlendOp() { return Material::None; }
   virtual const char* getOutputVarName() const { return "eyeSpaceDepth"; }
};


class DepthOutGLSL : public ShaderFeatureGLSL
{
public:

   // ShaderFeature
   virtual void processVert( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual Resources getResources( const MaterialFeatureData &fd );
   virtual String getName() { return "Depth (Out)"; }
   virtual Material::BlendOp getBlendOp() { return Material::None; }
   virtual const char* getOutputVarName() const { return "IN_depth"; }
};

#endif // _DEPTH_GLSL_H_