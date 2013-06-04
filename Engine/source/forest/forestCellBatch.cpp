// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "forest/forestCellBatch.h"

#include "forest/forestItem.h"


ForestCellBatch::ForestCellBatch()
   :  mDirty( false ),
      mBounds( Box3F::Invalid )
{
}

ForestCellBatch::~ForestCellBatch()
{
}

bool ForestCellBatch::add( const ForestItem &item )
{
   // A little hacky, but don't allow more than 65K / 6 items
   // in a cell... this is generally the VB size limit on hardware.
   const U32 maxItems = 10000;
   if ( mItems.size() > maxItems )
      return false;

   // Do the pre batching tests... if it fails
   // then we cannot batch this type!
   if ( !_prepBatch( item ) )
      return false;

   // Add it to our list and we'll populate the VB at render time.
   mItems.push_back( item );
   mDirty = true;

   // Expand out bounds.
   const Box3F &box = item.getWorldBox();
   mBounds.intersect( box );
   return true;
}

void ForestCellBatch::render( SceneRenderState *state )
{
   if ( mDirty )
   {
      _rebuildBatch();
      mDirty = false;
   }

   _render( state );
}
