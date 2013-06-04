// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FOREST_SHADERGEN_WINDDEFORMATIONGLSL_H_
#define _FOREST_SHADERGEN_WINDDEFORMATIONGLSL_H_

#ifndef _SHADERGEN_GLSL_SHADERFEATUREGLSL_H_
#include "shaderGen/GLSL/shaderFeatureGLSL.h"
#endif
#ifndef _FEATURETYPE_H_
#include "materials/materialFeatureTypes.h"
#endif

class GFXShaderConstHandle;


class WindDeformationGLSL : public ShaderFeatureGLSL
{
protected:

   ShaderIncludeDependency mDep;

public:

   WindDeformationGLSL();

   virtual void processVert( Vector<ShaderComponent*> &componentList,
                             const MaterialFeatureData &fd );

   virtual String getName()
   {
      return "Wind Effect";
   }

   virtual void determineFeature(   Material *material,
                                    const GFXVertexFormat *vertexFormat,
                                    U32 stageNum,
                                    const FeatureType &type,
                                    const FeatureSet &features,
                                    MaterialFeatureData *outFeatureData );

   virtual ShaderFeatureConstHandles* createConstHandles( GFXShader *shader, SimObject *userObject );
};

DeclareFeatureType( MFT_WindEffect );

#endif // _FOREST_SHADERGEN_WINDDEFORMATIONGLSL_H_
