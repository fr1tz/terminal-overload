// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FOREST_EDITOR_UNDO_H_
#define _FOREST_EDITOR_UNDO_H_

#ifndef _UNDO_H_
#include "util/undo.h"
#endif
#ifndef _FORESTITEM_H_
#include "forest/forestItem.h"
#endif
#ifndef __RESOURCE_H__
#include "core/resource.h"
#endif

class ForestData;
class ForestEditorCtrl;

class ForestUndoAction : public UndoAction
{
   typedef UndoAction Parent;

public:

   ForestUndoAction( const Resource<ForestData> &data, ForestEditorCtrl *editor, const char *description );   

   // UndoAction
   virtual void undo() {}
   virtual void redo() {}

protected:

   ForestEditorCtrl *mEditor;
   Vector<ForestItem> mItems;
   Resource<ForestData> mData;
};

class ForestCreateUndoAction : public ForestUndoAction
{
   typedef ForestUndoAction Parent;

public:
  
   ForestCreateUndoAction( const Resource<ForestData> &data,
                           ForestEditorCtrl *editor );

   /// Adds the item to the Forest and stores 
   /// its info for undo later.
   void addItem( ForestItemData *data,
                 const Point3F &position,
                 F32 rotation,
                 F32 scale );

   // UndoAction
   virtual void undo();
   virtual void redo();
};


class ForestDeleteUndoAction : public ForestUndoAction
{
   typedef ForestUndoAction Parent;

public:
  
   ForestDeleteUndoAction( const Resource<ForestData> &data,
                           ForestEditorCtrl *editor );

   ///
   void removeItem( const ForestItem &item );
   void removeItem( const Vector<ForestItem> &itemList );

   // UndoAction
   virtual void undo();
   virtual void redo();
};


class ForestUpdateAction : public ForestUndoAction
{
   typedef ForestUndoAction Parent;

public:
  
   ForestUpdateAction(  const Resource<ForestData> &data,
                        ForestEditorCtrl *editor );

   void saveItem( const ForestItem &item );

   virtual void undo() { _swapState(); }
   virtual void redo() { _swapState(); }

protected:

   void _swapState();
};

#endif // _FOREST_EDITOR_UNDO_H_



