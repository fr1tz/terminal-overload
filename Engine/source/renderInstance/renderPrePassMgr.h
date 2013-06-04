// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _PREPASS_MGR_H_
#define _PREPASS_MGR_H_

#include "renderInstance/renderTexTargetBinManager.h"
#include "materials/matInstance.h"
#include "materials/processedShaderMaterial.h"
#include "shaderGen/conditionerFeature.h"
#include "core/util/autoPtr.h"

// Forward declare
class PrePassMatInstance;

// This render manager renders opaque objects to the z-buffer as a z-fill pass.
// It can optionally accumulate data from this opaque render pass into a render
// target for later use.
class RenderPrePassMgr : public RenderTexTargetBinManager
{
   typedef RenderTexTargetBinManager Parent;

public:

   // registered buffer name
   static const String BufferName;

   // Generic PrePass Render Instance Type
   static const RenderInstType RIT_PrePass;

   RenderPrePassMgr( bool gatherDepth = true, 
                     GFXFormat format = GFXFormatR16G16B16A16 );

   virtual ~RenderPrePassMgr();

   virtual void setPrePassMaterial( PrePassMatInstance *mat );

   // RenderBinManager interface
   virtual void render(SceneRenderState * state);
   virtual void sort();
   virtual void clear();
   virtual void addElement( RenderInst *inst );

   // ConsoleObject
   DECLARE_CONOBJECT(RenderPrePassMgr);


   typedef Signal<void(const SceneRenderState*, RenderPrePassMgr*, bool)> RenderSignal;

   static RenderSignal& getRenderSignal();  

   static const U32 OpaqueStaticLitMask = BIT(1);     ///< Stencil mask for opaque, lightmapped pixels
   static const U32 OpaqueDynamicLitMask = BIT(0);    ///< Stencil mask for opaque, dynamic lit pixels

   static const GFXStateBlockDesc &getOpaqueStencilTestDesc();
   static const GFXStateBlockDesc &getOpaqueStenciWriteDesc(bool lightmappedGeometry = true);

   virtual bool setTargetSize(const Point2I &newTargetSize);

   inline BaseMatInstance* getPrePassMaterial( BaseMatInstance *mat );

protected:

   /// The terrain render instance elements.
   Vector< MainSortElem > mTerrainElementList;

   /// The object render instance elements.
   Vector< MainSortElem > mObjectElementList;

   PrePassMatInstance *mPrePassMatInstance;

   virtual void _registerFeatures();
   virtual void _unregisterFeatures();
   virtual bool _updateTargets();
   virtual void _createPrePassMaterial();

   bool _lightManagerActivate(bool active);
};

//------------------------------------------------------------------------------

class ProcessedPrePassMaterial : public ProcessedShaderMaterial
{
   typedef ProcessedShaderMaterial Parent;
   
public:   
   ProcessedPrePassMaterial(Material& mat, const RenderPrePassMgr *prePassMgr);

   virtual U32 getNumStages();

   virtual void addStateBlockDesc(const GFXStateBlockDesc& desc);

protected:
   virtual void _determineFeatures( U32 stageNum, MaterialFeatureData &fd, const FeatureSet &features );

   const RenderPrePassMgr *mPrePassMgr;
   bool mIsLightmappedGeometry;
};

//------------------------------------------------------------------------------

class PrePassMatInstance : public MatInstance
{
   typedef MatInstance Parent;

public:   
   PrePassMatInstance(MatInstance* root, const RenderPrePassMgr *prePassMgr);
   virtual ~PrePassMatInstance();

   bool init()
   {
      return init( mFeatureList, mVertexFormat );
   }   

   // MatInstance
   virtual bool init(   const FeatureSet &features, 
                        const GFXVertexFormat *vertexFormat );

protected:      
   virtual ProcessedMaterial* getShaderMaterial();

   const RenderPrePassMgr *mPrePassMgr;
};

//------------------------------------------------------------------------------

class PrePassMatInstanceHook : public MatInstanceHook
{
public:
   PrePassMatInstanceHook(MatInstance *baseMatInst, const RenderPrePassMgr *prePassMgr);
   virtual ~PrePassMatInstanceHook();

   virtual PrePassMatInstance *getPrePassMatInstance() { return mHookedPrePassMatInst; }

   virtual const MatInstanceHookType& getType() const { return Type; }

   /// The type for prepass material hooks.
   static const MatInstanceHookType Type;

protected:
   PrePassMatInstance *mHookedPrePassMatInst; 
   const RenderPrePassMgr *mPrePassManager;
};

//------------------------------------------------------------------------------

// A very simple, default depth conditioner feature
class LinearEyeDepthConditioner : public ConditionerFeature
{
   typedef ConditionerFeature Parent;

public:
   LinearEyeDepthConditioner(const GFXFormat bufferFormat) 
      : Parent(bufferFormat)
   {

   }

   virtual String getName()
   {
      return "Linear Eye-Space Depth Conditioner";
   }

   virtual void processPix( Vector<ShaderComponent*> &componentList, const MaterialFeatureData &fd );
protected:
   virtual Var *_conditionOutput( Var *unconditionedOutput, MultiLine *meta );
   virtual Var *_unconditionInput( Var *conditionedInput, MultiLine *meta );

   virtual Var *printMethodHeader( MethodType methodType, const String &methodName, Stream &stream, MultiLine *meta );
};


inline BaseMatInstance* RenderPrePassMgr::getPrePassMaterial( BaseMatInstance *mat )
{
   PrePassMatInstanceHook *hook = static_cast<PrePassMatInstanceHook*>( mat->getHook( PrePassMatInstanceHook::Type ) );
   if ( !hook )
   {
      hook = new PrePassMatInstanceHook( static_cast<MatInstance*>( mat ), this );
      mat->addHook( hook );
   }

   return hook->getPrePassMatInstance();
}

#endif // _PREPASS_MGR_H_

