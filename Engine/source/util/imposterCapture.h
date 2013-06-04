// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _IMPOSTERCAPTURE_H_
#define _IMPOSTERCAPTURE_H_

#ifndef _MATHTYPES_H_
#include "math/mathTypes.h"
#endif
#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif
#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _TSRENDERDATA_H_
#include "ts/tsRenderState.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif

class GBitmap;
class SceneRenderState;
class TSShapeInstance;
class GFXTextureTarget;
class RenderPassManager;
class RenderMeshMgr;


class ImposterCapture
{
   
protected:

   S32 mDl;
   S32 mDim;

   /// The bounding radius of the shape used to size the billboard.
   F32 mRadius;

   /// 
   Point3F mCenter;

   GBitmap *mBlackBmp;
   GBitmap *mWhiteBmp;

   GFXTexHandle mBlackTex;
   GFXTexHandle mWhiteTex;
   GFXTexHandle mNormalTex;

   SceneRenderState *mState;
   TSShapeInstance *mShapeInstance;
   TSRenderState mRData;

   GFXTextureTarget *mRenderTarget;

   RenderPassManager *mRenderPass;
   RenderMeshMgr     *mMeshRenderBin;

   void _colorAverageFilter(  U32 dimensions, const U8 *inBmpBits, U8 *outBmpBits );
   void _renderToTexture( GFXTexHandle texHandle, GBitmap *outBitmap, const ColorI &color ); 

   void _separateAlpha( GBitmap *imposterOut );

   void _convertDXT5nm( GBitmap *imposterOut );

public:

   ImposterCapture();

   ~ImposterCapture();

   void begin( TSShapeInstance *shapeInst,
               S32 dl, 
               S32 dim,
               F32 radius,
               const Point3F &center );

   void capture(  const MatrixF &rotMatrix, 
                  GBitmap **imposterOut,
                  GBitmap **normalMapOut );

   void end();

};

#endif // _IMPOSTERCAPTURE_H_