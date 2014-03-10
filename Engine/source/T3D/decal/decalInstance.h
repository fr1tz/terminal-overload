// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _DECALINSTANCE_H_
#define _DECALINSTANCE_H_

#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif

#ifndef _DECALDATA_H_
#include "T3D/decal/decalData.h"
#endif

#ifndef _PALETTE_H_
#include "scene/palette.h"
#endif

struct DecalVertex;
class SceneRenderState;

/// DecalInstance represents a rendering decal in the scene.
/// You should not allocate this yourself, add new decals to the scene
/// via the DecalManager.
/// All data is public, change it if you wish, but be sure to inform
/// the DecalManager.
class DecalInstance
{
   public:

      DecalData *mDataBlock;

      Point3F mPosition;
      Point3F mNormal;
      Point3F mTangent;
      F32 mRotAroundNormal;   
      F32 mSize;

      U32 mCreateTime;
      F32 mVisibility;

      F32 mLastAlpha;

      U32 mTextureRectIdx;      

      DecalVertex *mVerts;
      U16 *mIndices;

      U32 mVertCount;
      U32 mIndxCount;

      U8 mFlags;

      U8 mRenderPriority;

      S32 mId;

      Palette mPalette;

      GFXTexHandle *mCustomTex;

      void getWorldMatrix( MatrixF *outMat, bool flip = false );
      
      Box3F getWorldBox() const
      {
         return Box3F( mPosition - Point3F( mSize / 2.f ), mPosition + Point3F( mSize / 2.f ) );
      }

      U8 getRenderPriority() const
      {
         return mRenderPriority == 0 ? mDataBlock->renderPriority : mRenderPriority;
      }

      /// Calculates the size of this decal onscreen in pixels, used for LOD.
      F32 calcPixelSize( U32 viewportHeight, const Point3F &cameraPos, F32 worldToScreenScaleY ) const;
   		
	   DecalInstance() : mId(-1), mPalette(Palette::active) {}   
};

#endif // _DECALINSTANCE_H_
