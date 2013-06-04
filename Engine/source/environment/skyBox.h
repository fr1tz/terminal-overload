// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif

#ifndef _CUBEMAPDATA_H_
#include "gfx/sim/cubemapData.h"
#endif

#ifndef _MATERIALLIST_H_
#include "materials/materialList.h"
#endif

#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif

#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif


GFXDeclareVertexFormat( GFXSkyVertex )
{
   Point3F point;
   Point3F normal;
   GFXVertexColor color;
};


struct SkyMatParams
{
   void init( BaseMatInstance *matInst ) {};
};

class MatrixSet;

class SkyBox : public SceneObject
{
   typedef SceneObject Parent;

public:

   SkyBox();
   virtual ~SkyBox();

   DECLARE_CONOBJECT( SkyBox );

   // SimObject
   void onStaticModified( const char *slotName, const char *newValue );

   // ConsoleObject
   virtual bool onAdd();
   virtual void onRemove();
   static void initPersistFields();
   virtual void inspectPostApply();      

   // NetObject
   virtual U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
   virtual void unpackUpdate( NetConnection *conn, BitStream *stream );

   // SceneObject
   void prepRenderImage( SceneRenderState* state );

   /// Our render delegate.
   void _renderObject( ObjectRenderInst *ri, SceneRenderState *state, BaseMatInstance *mi );

   /// Prepares rendering structures and geometry.
   void _initRender();

protected:

   // Material 
   String mMatName;
   BaseMatInstance *mMatInstance;
   SkyMatParams mMatParamHandle;

   SimObjectPtr<Material> mMaterial;
   
   GFXVertexBufferHandle<GFXVertexPNTT> mVB;

   GFXVertexBufferHandle<GFXVertexPC> mFogBandVB;
   Material *mFogBandMat;
   BaseMatInstance *mFogBandMatInst;

   ColorF mLastFogColor;

   bool mDrawBottom;
   bool mIsVBDirty;
   U32 mPrimCount;

   MatrixSet *mMatrixSet;

   F32 mFogBandHeight;   

   void _updateMaterial();
   void _initMaterial();

   BaseMatInstance* _getMaterialInstance();
};

#endif // _SKYBOX_H_