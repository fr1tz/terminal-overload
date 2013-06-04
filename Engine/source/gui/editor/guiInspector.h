// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_H_
#define _GUI_INSPECTOR_H_

#ifndef _GUISTACKCTRL_H_
   #include "gui/containers/guiStackCtrl.h"
#endif


class GuiInspectorGroup;
class GuiInspectorField;
class GuiInspectorDatablockField;


/// A control that allows to edit the properties of one or more SimObjects.
class GuiInspector : public GuiStackControl
{
   typedef GuiStackControl Parent;

public:

   GuiInspector();
   virtual ~GuiInspector();

   DECLARE_CONOBJECT(GuiInspector);
   DECLARE_CATEGORY( "Gui Editor" );
   DECLARE_DESCRIPTION( "A control that allows to edit the properties of one or more SimObjects." );

   // Console Object
   static void initPersistFields();

   // SimObject
   virtual void onRemove();
   virtual void onDeleteNotify( SimObject *object );

   // GuiControl
   virtual void parentResized( const RectI &oldParentRect, const RectI &newParentRect );
   virtual bool resize( const Point2I &newPosition, const Point2I &newExtent );
   virtual GuiControl* findHitControl( const Point2I &pt, S32 initialLayer );   
   virtual void getCursor( GuiCursor *&cursor, bool &showCursor, const GuiEvent &lastGuiEvent );
   virtual void onMouseMove( const GuiEvent &event );
   virtual void onMouseDown( const GuiEvent &event );
   virtual void onMouseUp( const GuiEvent &event );
   virtual void onMouseDragged( const GuiEvent &event );

   // GuiInspector
   
   /// Return true if "object" is in the inspection set of this inspector.
   bool isInspectingObject( SimObject* object );

   /// Set the currently inspected object.
   virtual void inspectObject( SimObject *object );
   
   /// Add another object to the set of currently inspected objects.
   virtual void addInspectObject( SimObject* object, bool autoSync = true );
   
   /// Remove the given object from the set of inspected objects.
   virtual void removeInspectObject( SimObject* object );
   
   /// Remove all objects from the inspection set.
   virtual void clearInspectObjects();

   /// Get the currently inspected object
   SimObject* getInspectObject( U32 index = 0 ) { return mTargets[ index ]; }
   
   /// Return the number of objects being inspected by this GuiInspector.
   U32 getNumInspectObjects() const { return mTargets.size(); }
   
   /// Call inspectPreApply on all inspected objects.
   void sendInspectPreApply();
   
   /// Call inspectPostApply on all inspected objects.
   void sendInspectPostApply();

   /// Set the currently inspected object name
   /// @note Only valid in single-object mode.
   void setName( StringTableEntry newName );

   /// Deletes all GuiInspectorGroups
   void clearGroups();   

   /// Returns true if the named group exists
   /// Helper for inspectObject
   GuiInspectorGroup* findExistentGroup( StringTableEntry groupName );

   /// Should there be a GuiInspectorField associated with this fieldName,
   /// update it to reflect actual/current value of that field in the inspected object.
   /// Added to support UndoActions
   void updateFieldValue( StringTableEntry fieldName, const char* arrayIdx );

   /// Divider position is interpreted as an offset 
   /// from the right edge of the field control.
   /// Divider margin is an offset on both left and right
   /// sides of the divider in which it can be selected
   /// with the mouse.
   void getDivider( S32 &pos, S32 &margin );   

   void updateDivider();

   bool collideDivider( const Point2I &localPnt );

   void setHighlightField( GuiInspectorField *field );

   // If returns true that group will not be inspected.
   bool isGroupFiltered( const char *groupName ) const;

   // Returns true only if the group name follows a minus symbol in the filters.
   bool isGroupExplicitlyFiltered( const char *groupName ) const;

   void setObjectField( const char *fieldName, const char *data );

   static GuiInspector* findByObject( SimObject *obj );   

protected:
      
   typedef Vector< SimObjectPtr< SimObject > > TargetVector;

   Vector<GuiInspectorGroup*> mGroups;

   /// Objects being inspected by this GuiInspector.
   TargetVector mTargets;
   
   F32 mDividerPos;   
   S32 mDividerMargin;
   bool mOverDivider;
   bool mMovingDivider;
   SimObjectPtr<GuiInspectorField> mHLField;
   String mGroupFilters;   
   bool mShowCustomFields;
   
   void refresh();
};

#endif