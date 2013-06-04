// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _GUISEPARATORCTRL_H_
#define _GUISEPARATORCTRL_H_

#ifndef _GUICONTROL_H_
   #include "gui/core/guiControl.h"
#endif
#ifndef _DYNAMIC_CONSOLETYPES_H_
   #include "console/dynamicTypes.h"
#endif


/// Renders a separator line with optional text.
class GuiSeparatorCtrl : public GuiControl
{
private:
   typedef GuiControl Parent;

public:
   bool  mInvisible;
   String mText;
   S32   mTextLeftMargin;
   S32   mMargin;
   S32   mSeparatorType;

   enum separatorTypeOptions
   {
      separatorTypeVertical = 0, ///< Draw Vertical Separator
      separatorTypeHorizontal    ///< Horizontal Separator
   };

   //creation methods
   DECLARE_CONOBJECT(GuiSeparatorCtrl);
   DECLARE_CATEGORY( "Gui Other" );
   DECLARE_DESCRIPTION( "A control that renders a horizontal or vertical separator with\n"
      "an optional text label (horizontal only). ");
   GuiSeparatorCtrl();

   static void initPersistFields();

   void onRender(Point2I offset, const RectI &updateRect);
};

typedef GuiSeparatorCtrl::separatorTypeOptions GuiSeparatorType;
DefineEnumType( GuiSeparatorType );

#endif
