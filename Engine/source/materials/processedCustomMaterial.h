// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MATERIALS_PROCESSEDCUSTOMMATERIAL_H_
#define _MATERIALS_PROCESSEDCUSTOMMATERIAL_H_

#ifndef _MATERIALS_PROCESSEDSHADERMATERIAL_H_
#include "materials/processedShaderMaterial.h"
#endif
#ifndef _CUSTOMMATERIALDEFINITION_H_
#include "materials/customMaterialDefinition.h"
#endif


///
class ProcessedCustomMaterial : public ProcessedShaderMaterial
{
   typedef ProcessedShaderMaterial Parent;
public:
   ProcessedCustomMaterial(Material &mat);
   ~ProcessedCustomMaterial();

   virtual bool setupPass(SceneRenderState *, const SceneData& sgData, U32 pass);
   virtual bool init( const FeatureSet &features, const GFXVertexFormat *vertexFormat, const MatFeaturesDelegate &featuresDelegate );   
   virtual void setTextureStages(SceneRenderState *, const SceneData &sgData, U32 pass );
   virtual MaterialParameters* allocMaterialParameters();

protected:

   virtual void _setStageData();
   virtual bool _hasCubemap(U32 pass);
   void _initPassStateBlock( RenderPassData *rpd, GFXStateBlockDesc &result );
   virtual void _initPassStateBlocks();

private:

   CustomMaterial* mCustomMaterial;

   /// The conditioner macros passed to the 
   /// shader on construction.
   Vector<GFXShaderMacro> mConditionerMacros;

   /// How many texture slots are we using.
   U32 mMaxTex;
   
   template <typename T>
   void setMaterialParameter(MaterialParameters* param, MaterialParameterHandle* handle,
      const String& value);
   void setMatrixParameter(MaterialParameters* param, 
      MaterialParameterHandle* handle, const String& value, GFXShaderConstType matrixType);
};

#endif // _MATERIALS_PROCESSEDCUSTOMMATERIAL_H_
