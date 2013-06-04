// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ADVANCEDLIGHTMANAGER_H_
#define _ADVANCEDLIGHTMANAGER_H_

#ifndef _SIMOBJECT_H_
#include "console/simObject.h"
#endif 
#ifndef _LIGHTMANAGER_H_
#include "lighting/lightManager.h"
#endif 
#ifndef _LIGHTINFO_H_
#include "lighting/lightInfo.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _GFXTARGET_H_
#include "gfx/gfxTarget.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _LIGHTSHADOWMAP_H_
#include "lighting/shadowMap/lightShadowMap.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif


class AvailableSLInterfaces;
class AdvancedLightBinManager;
class RenderPrePassMgr;
class BaseMatInstance;
class MaterialParameters;
class MaterialParameterHandle;
class GFXShader;
class GFXShaderConstHandle;
class ShadowMapManager;


class AdvancedLightManager : public LightManager
{
   typedef LightManager Parent;

public:

   /// Return the lightBinManager for this light manager.
   AdvancedLightBinManager* getLightBinManager() { return mLightBinManager; }

   // LightManager
   virtual bool isCompatible() const;
   virtual void activate( SceneManager *sceneManager );
   virtual void deactivate();
   virtual void registerGlobalLight(LightInfo *light, SimObject *obj);
   virtual void unregisterAllLights();
   virtual void setLightInfo( ProcessedMaterial *pmat, 
                              const Material *mat, 
                              const SceneData &sgData, 
                              const SceneRenderState *state,
                              U32 pass, 
                              GFXShaderConstBuffer *shaderConsts );
   virtual bool setTextureStage( const SceneData &sgData, 
                                 const U32 currTexFlag, 
                                 const U32 textureSlot, 
                                 GFXShaderConstBuffer *shaderConsts, 
                                 ShaderConstHandles *handles );

   typedef GFXVertexPC LightVertex;

   GFXVertexBufferHandle<LightVertex> getSphereMesh(U32 &outNumPrimitives, GFXPrimitiveBuffer *&outPrimitives );
   GFXVertexBufferHandle<LightVertex> getConeMesh(U32 &outNumPrimitives, GFXPrimitiveBuffer *&outPrimitives );

   LightShadowMap* findShadowMapForObject( SimObject *object );

protected:   

   // LightManager
   virtual void _addLightInfoEx( LightInfo *lightInfo );
   virtual void _initLightFields();

   /// A simple protected singleton.  Use LightManager::findByName()
   /// to access this light manager.
   /// @see LightManager::findByName()
   static AdvancedLightManager smSingleton;

   // These are protected because we're a singleton and
   // no one else should be creating us!
   AdvancedLightManager();
   virtual ~AdvancedLightManager();

   SimObjectPtr<AdvancedLightBinManager> mLightBinManager;

   SimObjectPtr<RenderPrePassMgr> mPrePassRenderBin;

   LightConstantMap mConstantLookup;

   GFXShaderRef mLastShader;

   LightingShaderConstants* mLastConstants;

   // Convex geometry for lights
   GFXVertexBufferHandle<LightVertex> mSphereGeometry;

   GFXPrimitiveBufferHandle mSphereIndices;

   U32 mSpherePrimitiveCount;

   GFXVertexBufferHandle<LightVertex> mConeGeometry;

   GFXPrimitiveBufferHandle mConeIndices;

   U32 mConePrimitiveCount;

   LightingShaderConstants* getLightingShaderConstants(GFXShaderConstBuffer* shader);
   
};

#endif // _ADVANCEDLIGHTMANAGER_H_
