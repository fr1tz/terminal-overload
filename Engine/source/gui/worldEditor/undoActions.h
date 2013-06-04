// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_WORLDEDITOR_UNDOACTIONS_H_
#define _GUI_WORLDEDITOR_UNDOACTIONS_H_

#ifndef _UNDO_H_
#include "util/undo.h"
#endif
#ifndef _CONSOLE_SIMOBJECTMEMENTO_H_
#include "console/simObjectMemento.h"
#endif

class GuiInspectorField;
class GuiInspector;

class MECreateUndoAction : public UndoAction
{
   typedef UndoAction Parent;

protected:

   struct ObjectState
   {
      /// The object we created and will delete in undo.
      SimObjectId id;

      /// The captured object state.
      SimObjectMemento memento;

      /// Keep track of the parent group.
      SimObjectId groupId;
   };

   /// All the objects that were created.
   Vector<ObjectState> mObjects;

public:

   DECLARE_CONOBJECT( MECreateUndoAction );
   static void initPersistFields();
   
   MECreateUndoAction( const UTF8* actionName = " " );
   virtual ~MECreateUndoAction();

   void addObject( SimObject *object );

   // UndoAction
   virtual void undo();
   virtual void redo();
};


class MEDeleteUndoAction : public UndoAction
{
   typedef UndoAction Parent;

protected:

   struct ObjectState
   {
      /// The object we deleted and will restore in undo.
      SimObjectId id;

      /// The captured object state.
      SimObjectMemento memento;

      /// Keep track of the parent group.
      SimObjectId groupId;
   };

   /// All the objects we're deleting.
   Vector<ObjectState> mObjects;

public:

   DECLARE_CONOBJECT( MEDeleteUndoAction );
   static void initPersistFields();
   
   MEDeleteUndoAction( const UTF8* actionName = "Delete Object" );
   virtual ~MEDeleteUndoAction();

   ///
   void deleteObject( SimObject *object );
   void deleteObject( const Vector<SimObject*> &objectList );

   // UndoAction
   virtual void undo();
   virtual void redo();
};

class InspectorFieldUndoAction : public UndoAction
{
   typedef UndoAction Parent;

public:

   InspectorFieldUndoAction();
   InspectorFieldUndoAction( const UTF8* actionName );

   DECLARE_CONOBJECT( InspectorFieldUndoAction );
   static void initPersistFields();

   GuiInspector *mInspector;
   SimObjectId mObjId;
   SimObjectPtr<GuiInspectorField> mField; 
   StringTableEntry mSlotName;
   StringTableEntry mArrayIdx;
   String mData;         

   // UndoAction
   virtual void undo();
   virtual void redo() { undo(); }
};

#endif // _GUI_WORLDEDITOR_UNDOACTIONS_H_
