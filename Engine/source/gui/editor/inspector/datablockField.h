// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUI_INSPECTOR_DATABLOCKFIELD_H_
#define _GUI_INSPECTOR_DATABLOCKFIELD_H_

#include "gui/editor/guiInspectorTypes.h"


//-----------------------------------------------------------------------------
// GuiInspectorDatablockField - custom field type for datablock enumeration
//-----------------------------------------------------------------------------
class GuiInspectorDatablockField : public GuiInspectorTypeMenuBase
{
   public:
      
      typedef GuiInspectorTypeMenuBase Parent;
      
   protected:

      AbstractClassRep *mDesiredClass;

      virtual SimSet* _getDatablockSet() const { return Sim::getDataBlockGroup(); }
      virtual void _populateMenu( GuiPopUpMenuCtrl* menu );
      
   public:
      
      DECLARE_CONOBJECT(GuiInspectorDatablockField);
      
      GuiInspectorDatablockField( StringTableEntry className );
      GuiInspectorDatablockField() { mDesiredClass = NULL; };

      void setClassName( StringTableEntry className );
};

//-----------------------------------------------------------------------------
// TypeSFXDescriptionName GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeSFXDescriptionName : public GuiInspectorDatablockField
{
   public:
   
      typedef GuiInspectorDatablockField Parent;
      
   protected:
   
      virtual SimSet* _getDatablockSet() const { return Sim::getSFXDescriptionSet(); }
   
   public:
      
      DECLARE_CONOBJECT(GuiInspectorTypeSFXDescriptionName);
      static void consoleInit();
};


//-----------------------------------------------------------------------------
// TypeSFXTrackName GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeSFXTrackName : public GuiInspectorDatablockField
{
   public:
   
      typedef GuiInspectorDatablockField Parent;
      
   protected:
   
      virtual SimSet* _getDatablockSet() const { return Sim::getSFXTrackSet(); }
      
   public:

      DECLARE_CONOBJECT(GuiInspectorTypeSFXTrackName);
      static void consoleInit();
};


//-----------------------------------------------------------------------------
// TypeSFXEnvironmentName GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeSFXEnvironmentName : public GuiInspectorDatablockField
{
   public:
   
      typedef GuiInspectorDatablockField Parent;
      
   protected:
   
      virtual SimSet* _getDatablockSet() const { return Sim::getSFXEnvironmentSet(); }
   
   public:
      DECLARE_CONOBJECT(GuiInspectorTypeSFXEnvironmentName);
      static void consoleInit();
};


//-----------------------------------------------------------------------------
// TypeSFXAmbienceName GuiInspectorField Class
//-----------------------------------------------------------------------------
class GuiInspectorTypeSFXAmbienceName : public GuiInspectorDatablockField
{
   public:
   
      typedef GuiInspectorDatablockField Parent;
      
   protected:
   
      virtual SimSet* _getDatablockSet() const { return Sim::getSFXAmbienceSet(); }
   
   public:
   
      DECLARE_CONOBJECT(GuiInspectorTypeSFXAmbienceName);
      static void consoleInit();
};


#endif