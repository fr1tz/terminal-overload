// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FORESTCELLBATCH_H_
#define _FORESTCELLBATCH_H_

#include "scene/sceneRenderState.h"

class ForestItem;


class ForestCellBatch 
{
protected:

   /// Used to detect when the batch rendering 
   /// objects need to be repacked.
   bool mDirty; 

   /// The items in the batch.
   Vector<ForestItem> mItems;

   /// The world space bounding box of this batch.
   Box3F mBounds;

   virtual bool _prepBatch( const ForestItem &item ) = 0;
   virtual void _rebuildBatch() = 0;
   virtual void _render( const SceneRenderState *state ) = 0;

public:
   
   ForestCellBatch();
   virtual ~ForestCellBatch();

   bool add( const ForestItem &item );
   S32 getItemCount() const { return mItems.size(); }

   void render( SceneRenderState *state );
   const Box3F& getWorldBox() const { return mBounds; }
};


#endif // _FORESTCELLBATCH_H_
