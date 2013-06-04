// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BUMP_GLSL_H_
#define _BUMP_GLSL_H_

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
#endif

struct RenderPassData;
class MultiLine;


/// The Bumpmap feature will read the normal map and
/// transform it by the inverse of the worldToTanget 
/// matrix.  This normal is then used by subsequent
/// shader features.
class BumpFeatGLSL : public ShaderFeatureGLSL
{
public:

   // ShaderFeatureGLSL
   virtual void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd );
   virtual void processPix( Vector<ShaderComponent*> &componentList, 
                            const MaterialFeatureData &fd );
   virtual Material::BlendOp getBlendOp(){ return Material::LerpAlpha; }  
   virtual Resources getResources( const MaterialFeatureData &fd );
   virtual void setTexData( Material::StageData &stageDat,
                            const MaterialFeatureData &fd,
                            RenderPassData &passData,
                            U32 &texIndex );

   virtual String getName() { return "Bumpmap"; }
};


/// This feature either generates the cheap yet effective offset
/// mapping style parallax or the much more expensive occlusion 
/// mapping technique based on the enabled feature flags.
class ParallaxFeatGLSL : public ShaderFeatureGLSL
{
protected:

   static Var* _getUniformVar( const char *name, const char *type );

public:

   // ShaderFeatureGLSL
   virtual void processVert(  Vector<ShaderComponent*> &componentList,
                              const MaterialFeatureData &fd );
   virtual void processPix(   Vector<ShaderComponent*> &componentList, 
                              const MaterialFeatureData &fd );
   virtual Resources getResources( const MaterialFeatureData &fd );
   virtual void setTexData(   Material::StageData &stageDat,
                              const MaterialFeatureData &fd,
                              RenderPassData &passData,
                              U32 &texIndex );
   virtual String getName() { return "Parallax"; }
};



/// This feature is used to render normals to the 
/// diffuse target for imposter rendering.
class NormalsOutFeatGLSL : public ShaderFeatureGLSL
{
public:
	
   // ShaderFeatureGLSL
   virtual void processVert(  Vector<ShaderComponent*> &componentList,
									 const MaterialFeatureData &fd );
   virtual void processPix( Vector<ShaderComponent*> &componentList, 
									const MaterialFeatureData &fd );
   virtual Material::BlendOp getBlendOp(){ return Material::LerpAlpha; }  
   virtual String getName() { return "NormalsOut"; }
};

#endif // _BUMP_GLSL_H_