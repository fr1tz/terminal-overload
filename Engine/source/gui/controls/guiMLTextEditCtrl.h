// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIMLTEXTEDITCTRL_H_
#define _GUIMLTEXTEDITCTRL_H_

#ifndef _GUIMLTEXTCTRL_H_
#include "gui/controls/guiMLTextCtrl.h"
#endif

class GuiMLTextEditCtrl : public GuiMLTextCtrl
{
   typedef GuiMLTextCtrl Parent;

   //-------------------------------------- Overrides
  protected:
   StringTableEntry mEscapeCommand;

   // Events
   bool onKeyDown(const GuiEvent&event);

   // Event forwards
   void handleMoveKeys(const GuiEvent&);
   void handleDeleteKeys(const GuiEvent&);

   // rendering
   void onRender(Point2I offset, const RectI &updateRect);

  public:
   GuiMLTextEditCtrl();
   ~GuiMLTextEditCtrl();

   virtual void setFirstResponder();
   virtual void onLoseFirstResponder();

   bool onWake();
   bool resize(const Point2I &newPosition, const Point2I &newExtent);

   DECLARE_CONOBJECT(GuiMLTextEditCtrl);
   DECLARE_DESCRIPTION( "A control that allows to edit multiple lines of text." );
   
   static void initPersistFields();
};

#endif  // _H_GUIMLTEXTEDITCTRL_
