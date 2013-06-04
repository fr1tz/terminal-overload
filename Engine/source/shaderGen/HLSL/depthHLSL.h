// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _DEPTH_HLSL_H_
#define _DEPTH_HLSL_H_

#ifndef _SHADERGEN_HLSL_SHADERFEATUREHLSL_H_
#include "shaderGen/HLSL/shaderFeatureHLSL.h"
#endif
#ifndef _SHADEROP_H_
#include "shaderGen/shaderOp.h"
#endif


class EyeSpaceDepthOutHLSL : public ShaderFeatureHLSL
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


class DepthOutHLSL : public ShaderFeatureHLSL
{
public:

   // ShaderFeature
   virtual void processVert( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual Resources getResources( const MaterialFeatureData &fd );
   virtual String getName() { return "Depth (Out)"; }
   virtual Material::BlendOp getBlendOp() { return Material::None; }
   virtual const char* getOutputVarName() const { return "IN.depth"; }
};

#endif // _DEPTH_HLSL_H_