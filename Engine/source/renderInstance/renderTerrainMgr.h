// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RENDERTERRAINMGR_H_
#define _RENDERTERRAINMGR_H_

#ifndef _RENDERBINMANAGER_H_
#include "renderInstance/renderBinManager.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif

class TerrCell;
class GFXTextureObject;
class TerrainCellMaterial;


/// The render instance for terrain cells.
struct TerrainRenderInst : public RenderInst
{
   GFXVertexBuffer *vertBuff;

   GFXPrimitiveBuffer *primBuff;

   GFXPrimitive prim;

   BaseMatInstance *mat;

   const MatrixF *objectToWorldXfm;

   TerrainCellMaterial *cellMat;

   /// The lights we pass to the material for 
   /// this cell in order light importance.
   LightInfo *lights[8];

   void clear()
   {
      dMemset( this, 0, sizeof( TerrainRenderInst ) );   
      type = RenderPassManager::RIT_Terrain;      
   }
};


///
class RenderTerrainMgr : public RenderBinManager
{
   typedef RenderBinManager Parent;

protected:

   Vector<TerrainRenderInst*> mInstVector;

   static bool smRenderWireframe;

   static S32 smCellsRendered;
   static S32 smOverrideCells;
   static S32 smDrawCalls;

   static bool _clearStats( GFXDevice::GFXDeviceEventType type );

   // RenderBinManager
   virtual void internalAddElement( RenderInst *inst );

public:

   RenderTerrainMgr();
   RenderTerrainMgr( F32 renderOrder, F32 processAddOrder );
   virtual ~RenderTerrainMgr();

   // ConsoleObject
   static void initPersistFields();
   DECLARE_CONOBJECT(RenderTerrainMgr);

   // RenderBinManager
   virtual void sort();
   virtual void render( SceneRenderState *state );
   virtual void clear();

};

#endif // _RENDERTERRAINMGR_H_
