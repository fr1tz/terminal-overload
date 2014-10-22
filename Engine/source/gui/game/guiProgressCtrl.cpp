// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gui/game/guiProgressCtrl.h"

#include "console/console.h"
#include "console/consoleTypes.h"
#include "gfx/gfxDrawUtil.h"
#include "console/engineAPI.h"

IMPLEMENT_CONOBJECT(GuiProgressCtrl);

ConsoleDocClass( GuiProgressCtrl,
   "@brief GUI Control which displays a horizontal bar which increases as the progress value of 0.0 - 1.0 increases.\n\n"

   "@tsexample\n"
   "     new GuiProgressCtrl(JS_statusBar)\n"
   "	 {\n"
   "		    //Properties not specific to this control have been omitted from this example.\n"
   "     };\n\n"
   "// Define the value to set the progress bar"
   "%value = \"0.5f\"\n\n"
   "// Set the value of the progress bar, from 0.0 - 1.0\n"
   "%thisGuiProgressCtrl.setValue(%value);\n"
   "// Get the value of the progress bar.\n"
   "%progress = %thisGuiProgressCtrl.getValue();\n"
   "@endtsexample\n\n"

   "@see GuiTextCtrl\n"
   "@see GuiControl\n\n"

   "@ingroup GuiValues\n"
);

GuiProgressCtrl::GuiProgressCtrl()
{
   mProgress = 0.0f;
}

const char* GuiProgressCtrl::getScriptValue()
{
   static const U32 bufSize = 64;
   char * ret = Con::getReturnBuffer(bufSize);
   dSprintf(ret, bufSize, "%g", mProgress);
   return ret;
}

void GuiProgressCtrl::setScriptValue(const char *value)
{
   //set the value
   if (! value)
      mProgress = 0.0f;
   else
      mProgress = dAtof(value);

   //validate the value
   mProgress = mClampF(mProgress, 0.f, 1.f);
   setUpdate();
}

void GuiProgressCtrl::onPreRender()
{
   const char * var = getVariable();
   if(var)
   {
      F32 value = mClampF(dAtof(var), 0.f, 1.f);
      if(value != mProgress)
      {
         mProgress = value;
         setUpdate();
      }
   }
}

void GuiProgressCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   RectI ctrlRect(offset, getExtent());

   //draw the progress
   S32 width = (S32)((F32)(getWidth()) * mProgress);
   if (width > 0)
   {
      RectI progressRect = ctrlRect;
      progressRect.extent.x = width;
      GFX->getDrawUtil()->drawRectFill(progressRect, mProfile->mFillColor);
   }

   //now draw the border
   if (mProfile->mBorder)
      GFX->getDrawUtil()->drawRect(ctrlRect, mProfile->mBorderColor);

   Parent::onRender( offset, updateRect );

   //render the children
   renderChildControls(offset, updateRect);
}

