// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUICONSOLETEXTCTRL_H_
#define _GUICONSOLETEXTCTRL_H_

#ifndef _GFONT_H_
#include "gfx/gFont.h"
#endif
#ifndef _GUITYPES_H_
#include "gui/core/guiTypes.h"
#endif
#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

class GuiConsoleTextCtrl : public GuiControl
{
private:
   typedef GuiControl Parent;

public:
   enum Constants { MAX_STRING_LENGTH = 255 };


protected:

   String mConsoleExpression;
   String mResult;
   Resource<GFont> mFont;

   Vector<U32> mStartLineOffset;
   Vector<U32> mLineLen;

public:

   //creation methods
   DECLARE_CONOBJECT(GuiConsoleTextCtrl);
   DECLARE_CATEGORY( "Gui Editor" );
   
   GuiConsoleTextCtrl();
   virtual ~GuiConsoleTextCtrl();
   static void initPersistFields();

   //Parental methods
   bool onWake();
   void onSleep();

   //text methods
   virtual void setText( const char *txt = NULL );
   const char* getText() { return mConsoleExpression.c_str(); }

   //rendering methods
   void calcResize();
   void onPreRender();    // do special pre render processing
   void onRender( Point2I offset, const RectI &updateRect );

   //Console methods
   const char* getScriptValue();
   void setScriptValue( const char *value );
};

#endif //_GUI_TEXT_CONTROL_H_
