// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _PARABOLOID_GLSL_H_
#define _PARABOLOID_GLSL_H_

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
#endif
#ifndef _SHADEROP_H_
#include "shaderGen/shaderOp.h"
#endif

class GFXShaderConstHandle;


class ParaboloidVertTransformGLSL : public ShaderFeatureGLSL
{
public:

   // ShaderFeature
   virtual void processVert( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
   virtual Resources getResources( const MaterialFeatureData &fd );
   virtual String getName() { return "Paraboloid Vert Transform"; }
   virtual Material::BlendOp getBlendOp() { return Material::None; }

};

#endif // _PARABOLOID_GLSL_H_