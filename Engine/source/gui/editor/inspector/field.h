// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_FIELD_H_
#define _GUI_INSPECTOR_FIELD_H_

#include "gui/core/guiCanvas.h"
#include "gui/shiny/guiTickCtrl.h"
#include "gui/controls/guiTextEditCtrl.h"
#include "gui/buttons/guiBitmapButtonCtrl.h"
#include "gui/controls/guiPopUpCtrl.h"

#include "gui/containers/guiRolloutCtrl.h"

class GuiInspectorGroup;
class GuiInspector;


/// The GuiInspectorField control is a representation of a single abstract
/// field for a given ConsoleObject derived object.  It handles creation
/// getting and setting of it's fields data and editing control.  
///
/// Creation of custom edit controls is done through this class and is
/// dependent upon the dynamic console type, which may be defined to be
/// custom for different types.
///
/// @note GuiInspectorField controls must have a GuiInspectorGroup as their
///        parent.  
class GuiInspectorField : public GuiControl
{
   public:

      typedef GuiControl Parent;
      friend class GuiInspectorGroup;

   protected:

      /// The text to display as the field name.
      StringTableEntry mCaption;
      
      /// The group to which this field belongs.
      GuiInspectorGroup* mParent;
      
      /// The GuiInspector that the group is in to which this field belongs.
      GuiInspector* mInspector;
      
      ///
      AbstractClassRep::Field* mField;
      
      ///
      StringTableEntry mFieldArrayIndex;
      
      ///
      String mFieldDocs;
      
      ///
      GuiControl* mEdit;
      
      ///
      RectI mCaptionRect;
      
      ///
      RectI mEditCtrlRect;
      
      ///
      bool mHighlighted;

      virtual void _registerEditControl( GuiControl *ctrl );
      virtual void _executeSelectedCallback();
      
      void _setFieldDocs( StringTableEntry docs );
      
   public:

      explicit GuiInspectorField();

      ///
      GuiInspectorField( GuiInspector *inspector, GuiInspectorGroup* parent, AbstractClassRep::Field* field );
      
      virtual ~GuiInspectorField();

      ///
      virtual void init( GuiInspector *inspector, GuiInspectorGroup *group );      
      
      ///
      virtual void setInspectorField( AbstractClassRep::Field *field, 
                                      StringTableEntry caption = NULL, 
                                      const char *arrayIndex = NULL );
      
      ///
      virtual GuiControl* constructEditControl();

      /// Chooses and sets the GuiControlProfile.
      virtual void setInspectorProfile();

      /// Sets this control's caption text, usually set within setInspectorField,
      /// this is exposed in case someone wants to override the normal caption.
      virtual void setCaption( StringTableEntry caption ) { mCaption = caption; }

      /// Returns pointer to this InspectorField's edit ctrl.
      virtual GuiControl* getEditCtrl() { return mEdit; }

      /// Sets the value of this GuiInspectorField (not the actual field)
      /// This means the EditCtrl unless overridden.
      virtual void setValue( const char* newValue );

      /// Get the currently value of this control (not the actual field)
      virtual const char* getValue() { return NULL; }

      /// Update this controls value to reflect that of the inspected field.
      virtual void updateValue();
      
      /// Return the name of the field being edited.
      virtual StringTableEntry getFieldName();
      
      /// Return the name of the console type that this field uses.
      virtual StringTableEntry getFieldType();
      
      /// Return the name without the array index that may potentially be present.
      virtual StringTableEntry getRawFieldName();
      
      ///
      StringTableEntry getArrayIndex() const { return mFieldArrayIndex; }

      /// Called from within setData to allow child classes
      /// to perform their own verification.
      virtual bool verifyData( StringTableEntry data ) { return true; }

      /// Set value of the field we are inspecting
      virtual void setData( const char* data, bool callbacks = true );
      
      /// Reset the field value to its default value based on default-constructed objects.
      ///
      /// @note If multiple objects are inspected, this will take the default value from
      ///   the first object and set all fields to this value.
      virtual void resetData();

      /// Get value of the field we are inspecting.
      ///
      /// @note The string returned by this method may be a transient string allocated
      ///   internally by the console.  For any non-transient needs, this string has
      ///   to be copied to locally owned memory.
      /// @note This method always returns the value of the field in the first
      ///   inspected object.
      virtual const char* getData( U32 inspectObjectIndex = 0 );

      /// Update the inspected field to match the value of this control.
      virtual void updateData() {};

      ///
      virtual bool updateRects();   

      ///
      virtual void setHLEnabled( bool enabled );
      
      /// Return true if all inspected objects have the same value for this
      /// field.
      bool hasSameValueInAllObjects();
      
      /// Return the inspector object that this field belongs to.
      GuiInspector* getInspector() const { return mInspector; }
      
      // GuiControl.
      virtual bool onAdd();
      virtual bool resize(const Point2I &newPosition, const Point2I &newExtent);
      virtual void onRender(Point2I offset, const RectI &updateRect);
      virtual void setFirstResponder( GuiControl *firstResponder );
      virtual void onMouseDown( const GuiEvent &event );
      virtual void onRightMouseUp( const GuiEvent &event );

      DECLARE_CONOBJECT( GuiInspectorField );
      DECLARE_CATEGORY( "Gui Editor" );
};

#endif // _GUI_INSPECTOR_FIELD_H_
