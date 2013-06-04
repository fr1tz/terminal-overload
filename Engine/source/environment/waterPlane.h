// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _WATERPLANE_H_
#define _WATERPLANE_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif
#ifndef _SCENEDATA_H_
#include "materials/sceneData.h"
#endif
#ifndef _MATINSTANCE_H_
#include "materials/matInstance.h"
#endif
#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif
#ifndef _RENDERPASSMANAGER_H_
#include "renderInstance/renderPassManager.h"
#endif
#ifndef _MATHUTIL_FRUSTUM_H_
#include "math/util/frustum.h"
#endif
#ifndef _WATEROBJECT_H_
#include "environment/waterObject.h"
#endif


//*****************************************************************************
// WaterPlane
//*****************************************************************************
class WaterPlane : public WaterObject
{
   typedef WaterObject Parent;

public:

   // LEGACY support
   enum EWaterType
   {
      eWater            = 0,
      eOceanWater       = 1,
      eRiverWater       = 2,
      eStagnantWater    = 3,
      eLava             = 4,
      eHotLava          = 5,
      eCrustyLava       = 6,
      eQuicksand        = 7,
   }; 

private:

   enum MaskBits {
      UpdateMask =   Parent::NextFreeMask,
      NextFreeMask = Parent::NextFreeMask << 1
   };
   
   // vertex / index buffers
   GFXVertexBufferHandle<GFXWaterVertex> mVertBuff;
   GFXPrimitiveBufferHandle mPrimBuff;

   // misc
   U32            mGridSize;
   U32            mGridSizeMinusOne;
   F32            mGridElementSize;
   U32            mVertCount;
   U32            mIndxCount;
   U32            mPrimCount;   
   Frustum        mFrustum;
   
   SceneData setupSceneGraphInfo( SceneRenderState *state );
   void setShaderParams( SceneRenderState *state, BaseMatInstance* mat, const WaterMatParams& paramHandles );
   void setupVBIB( SceneRenderState *state );
   virtual void prepRenderImage( SceneRenderState *state );
   virtual void innerRender( SceneRenderState *state );
   void setMultiPassProjection();

protected:

   //-------------------------------------------------------
   // Standard engine functions
   //-------------------------------------------------------
   bool onAdd();
   void onRemove();   
   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);
   bool castRay(const Point3F &start, const Point3F &end, RayInfo* info);

public:
   WaterPlane();
   virtual ~WaterPlane();

   DECLARE_CONOBJECT(WaterPlane);   

   static void initPersistFields();
   void onStaticModified( const char* slotName, const char*newValue = NULL );
   virtual void inspectPostApply();
   virtual void setTransform( const MatrixF & mat );
   virtual F32 distanceTo( const Point3F& point ) const;

   // WaterObject
   virtual F32 getWaterCoverage( const Box3F &worldBox ) const;
   virtual F32 getSurfaceHeight( const Point2F &pos ) const;
   virtual void onReflectionInfoChanged();
   virtual bool isUnderwater( const Point3F &pnt ) const;

   // WaterBlock   
   bool isPointSubmerged ( const Point3F &pos, bool worldSpace = true ) const{ return true; }

   // WaterPlane
   void setGridSize( U32 inSize );
   void setGridElementSize( F32 inSize );
   
   // Protected Set'ers
   static bool protectedSetGridSize( void *object, const char *index, const char *data );
   static bool protectedSetGridElementSize( void *object, const char *index, const char *data );

protected:

   // WaterObject
   virtual void _getWaterPlane( const Point3F &camPos, PlaneF &outPlane, Point3F &outPos );
};

#endif // _WATERPLANE_H_
