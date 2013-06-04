// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FOREST_SHADERGEN_WINDDEFORMATION_H_
#define _FOREST_SHADERGEN_WINDDEFORMATION_H_

#ifndef _SHADERGEN_H_
#include "shaderGen/shaderGen.h"
#endif
#ifndef _FEATURETYPE_H_
#include "materials/materialFeatureTypes.h"
#endif

class GFXShaderConstHandle;

class WindDeformationConstHandles : public ShaderFeatureConstHandles
{
public:

   GFXShaderConstHandle *mWindDirAndSpeed;
   GFXShaderConstHandle *mWindParams;

   // ShaderFeatureConstHandles
   virtual void init( GFXShader *shader );
   virtual void setConsts( SceneRenderState *state, 
                           const SceneData &sgData,
                           GFXShaderConstBuffer *buffer );
};


DeclareFeatureType( MFT_WindEffect );

#endif // _FOREST_SHADERGEN_WINDDEFORMATION_H_
