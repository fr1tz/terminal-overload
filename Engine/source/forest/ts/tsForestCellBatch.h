// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TSFORESTCELLBATCH_H_
#define _TSFORESTCELLBATCH_H_

#ifndef _FORESTCELLBATCH_H_
#include "renderInstance/renderImposterMgr.h"
#endif
#ifndef _FORESTCELLBATCH_H_
#include "forest/forestCellBatch.h"
#endif
#ifndef _GFXTEXTUREHANDLE_H_
#include "gfx/gfxTextureHandle.h"
#endif
#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef _GFXSTRUCTS_H_
#include "gfx/gfxStructs.h"
#endif

class GFXShader;


class TSForestCellBatch : public ForestCellBatch
{
protected:
   
   /// We use the same shader and vertex format as TSLastDetail.
   GFXVertexBufferHandle<ImposterState> mVB;

   TSLastDetail *mDetail;

   // ForestCellBatch
   virtual bool _prepBatch( const ForestItem &item );
   virtual void _rebuildBatch();
   virtual void _render( const SceneRenderState *state );

public:
   
   TSForestCellBatch( TSLastDetail *detail );

   virtual ~TSForestCellBatch();

};


#endif // _TSFORESTCELLBATCH_H_
