// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TERRCELLMATERIAL_H_
#define _TERRCELLMATERIAL_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _MATTEXTURETARGET_H_
#include "materials/matTextureTarget.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _GFXSHADER_H_
#include "gfx/gfxShader.h"
#endif
#ifndef _GFXSTATEBLOCK_H_
#include "gfx/gfxStateBlock.h"
#endif


class SceneRenderState;
struct SceneData;
class TerrainMaterial;
class TerrainBlock;
class BaseMatInstance;


/// This is a complex material which holds one or more
/// optimized shaders for rendering a single cell.
class TerrainCellMaterial
{
protected:

   class MaterialInfo
   {
   public:

      MaterialInfo()
      {
      }

      ~MaterialInfo() 
      {
      }

      TerrainMaterial *mat;
      U32 layerId;

      GFXShaderConstHandle *detailTexConst;
      GFXTexHandle detailTex;

      GFXShaderConstHandle *macroTexConst;
      GFXTexHandle macroTex;

      GFXShaderConstHandle *normalTexConst;
      GFXTexHandle normalTex;

      GFXShaderConstHandle *detailInfoVConst;
      GFXShaderConstHandle *detailInfoPConst;

	  GFXShaderConstHandle *macroInfoVConst;
      GFXShaderConstHandle *macroInfoPConst;
   };

   class Pass
   {
   public:

      Pass() 
         :  shader( NULL )                     
      {
      }

      ~Pass() 
      {
         for ( U32 i=0; i < materials.size(); i++ )
            delete materials[i];
      }

      Vector<MaterialInfo*> materials;

      ///
      GFXShader *shader;

      GFXShaderConstBufferRef consts;

      GFXStateBlockRef stateBlock;
      GFXStateBlockRef wireframeStateBlock;

      GFXShaderConstHandle *modelViewProjConst;
      GFXShaderConstHandle *worldViewOnly;
      GFXShaderConstHandle *viewToObj;

      GFXShaderConstHandle *eyePosWorldConst;
      GFXShaderConstHandle *eyePosConst;

      GFXShaderConstHandle *objTransConst;
      GFXShaderConstHandle *worldToObjConst;
      GFXShaderConstHandle *vEyeConst;

      GFXShaderConstHandle *layerSizeConst;
      GFXShaderConstHandle *lightParamsConst;
      GFXShaderConstHandle *lightInfoBufferConst;

      GFXShaderConstHandle *baseTexMapConst;
      GFXShaderConstHandle *layerTexConst;

      GFXShaderConstHandle *lightMapTexConst;

      GFXShaderConstHandle *squareSize;
      GFXShaderConstHandle *oneOverTerrainSize;

      GFXShaderConstHandle *fogDataConst;
      GFXShaderConstHandle *fogColorConst;
   };

   TerrainBlock *mTerrain;

   U64 mMaterials;

   Vector<Pass> mPasses;

   U32 mCurrPass;

   static const Vector<String> mSamplerNames;

   GFXTexHandle mBaseMapTexture;

   GFXTexHandle mLayerMapTexture;

   NamedTexTargetRef mLightInfoTarget;

   /// The prepass material for this material.
   TerrainCellMaterial *mPrePassMat;

   /// The reflection material for this material.
   TerrainCellMaterial *mReflectMat;

   /// A vector of all terrain cell materials loaded in the system.
   static Vector<TerrainCellMaterial*> smAllMaterials;

   bool _createPass( Vector<MaterialInfo*> *materials, 
                     Pass *pass, 
                     bool firstPass,
                     bool prePassMat,
                     bool reflectMat,
                     bool baseOnly );

   void _updateMaterialConsts( Pass *pass );

public:
   
   TerrainCellMaterial();
   ~TerrainCellMaterial();

   void init(  TerrainBlock *block, 
               U64 activeMaterials,
               bool prePassMat = false,
               bool reflectMat = false,
               bool baseOnly = false );

   /// Returns a prepass material from this material.
   TerrainCellMaterial* getPrePassMat();

   /// Returns the reflection material from this material.
   TerrainCellMaterial* getReflectMat();

   void setTransformAndEye(   const MatrixF &modelXfm, 
                              const MatrixF &viewXfm,
                              const MatrixF &projectXfm,
                              F32 farPlane );

   ///
   bool setupPass(   const SceneRenderState *state,
                     const SceneData &sceneData );

   ///
   static BaseMatInstance* getShadowMat();

   /// 
   static void _updateDefaultAnisotropy();
};

#endif // _TERRCELLMATERIAL_H_

