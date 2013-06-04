// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _GUIDECOYCTRL_H_
#define _GUIDECOYCTRL_H_

#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

class GuiDecoyCtrl : public GuiControl
{
private:
   typedef GuiControl Parent;

public:
   // Constructor/Destructor/ConObject Declaration
   GuiDecoyCtrl();
   virtual ~GuiDecoyCtrl();

   DECLARE_CONOBJECT(GuiDecoyCtrl);
   DECLARE_CATEGORY( "Gui Other" );
   
   static void initPersistFields();

   bool	mMouseOver;
   bool mIsDecoy;
   GuiControl* mDecoyReference;
   bool mMouseOverDecoy;
   Point2I mMouseDownPosition;


   virtual void onMouseUp(const GuiEvent &event);
   virtual void onMouseDown(const GuiEvent &event);
   virtual void onMouseMove(const GuiEvent &event);
   virtual void onMouseDragged(const GuiEvent &event);
   virtual void onMouseEnter(const GuiEvent &event);
   virtual void onMouseLeave(const GuiEvent &event);

   virtual bool onMouseWheelUp(const GuiEvent &event);
   virtual bool onMouseWheelDown(const GuiEvent &event);

   virtual void onRightMouseDown(const GuiEvent &event);
   virtual void onRightMouseUp(const GuiEvent &event);
   virtual void onRightMouseDragged(const GuiEvent &event);

   virtual void onMiddleMouseDown(const GuiEvent &event);
   virtual void onMiddleMouseUp(const GuiEvent &event);
   virtual void onMiddleMouseDragged(const GuiEvent &event);
};
#endif
