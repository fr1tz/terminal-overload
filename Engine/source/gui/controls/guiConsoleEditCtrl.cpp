// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/consoleTypes.h"
#include "console/console.h"
#include "gui/core/guiCanvas.h"
#include "gui/controls/guiConsoleEditCtrl.h"
#include "core/frameAllocator.h"

IMPLEMENT_CONOBJECT(GuiConsoleEditCtrl);

ConsoleDocClass( GuiConsoleEditCtrl,
   "@brief Text entry element of a GuiConsole.\n\n"
   "@tsexample\n"
   "new GuiConsoleEditCtrl(ConsoleEntry)\n"
   "{\n"
   "   profile = \"ConsoleTextEditProfile\";\n"
   "   horizSizing = \"width\";\n"
   "   vertSizing = \"top\";\n"
   "   position = \"0 462\";\n"
   "   extent = \"640 18\";\n"
   "   minExtent = \"8 8\";\n"
   "   visible = \"1\";\n"
   "   altCommand = \"ConsoleEntry::eval();\";\n"
   "   helpTag = \"0\";\n"
   "   maxLength = \"255\";\n"
   "   historySize = \"40\";\n"
   "   password = \"0\";\n"
   "   tabComplete = \"0\";\n"
   "   sinkAllKeyEvents = \"1\";\n"
   "   useSiblingScroller = \"1\";\n"
   "};\n"
   "@endtsexample\n\n"
   "@ingroup GuiCore"
);

GuiConsoleEditCtrl::GuiConsoleEditCtrl()
{
   mSinkAllKeyEvents = true;
   mSiblingScroller = NULL;
   mUseSiblingScroller = true;
}

void GuiConsoleEditCtrl::initPersistFields()
{
   addGroup("GuiConsoleEditCtrl");
   addField("useSiblingScroller", TypeBool, Offset(mUseSiblingScroller, GuiConsoleEditCtrl));
   endGroup("GuiConsoleEditCtrl");

   Parent::initPersistFields();
}

bool GuiConsoleEditCtrl::onKeyDown(const GuiEvent &event)
{
   setUpdate();

   if (event.keyCode == KEY_TAB) 
   {
      // Get a buffer that can hold the completed text...
      FrameTemp<UTF8> tmpBuff(GuiTextCtrl::MAX_STRING_LENGTH);
      // And copy the text to be completed into it.
      mTextBuffer.getCopy8(tmpBuff, GuiTextCtrl::MAX_STRING_LENGTH);

      // perform the completion
      bool forward = (event.modifier & SI_SHIFT) == 0;
      mCursorPos = Con::tabComplete(tmpBuff, mCursorPos, GuiTextCtrl::MAX_STRING_LENGTH, forward);

      // place results in our buffer.
      mTextBuffer.set(tmpBuff);
      return true;
   }
   else if ((event.keyCode == KEY_PAGE_UP) || (event.keyCode == KEY_PAGE_DOWN)) 
   {
      // See if there's some other widget that can scroll the console history.
      if (mUseSiblingScroller) 
      {
         if (mSiblingScroller) 
         {
            return mSiblingScroller->onKeyDown(event);
         }
         else 
         {
            // Let's see if we can find it...
            SimGroup* pGroup = getGroup();
            if (pGroup) 
            {
               // Find the first scroll control in the same group as us.
               for (SimSetIterator itr(pGroup); *itr; ++itr) 
               {
                  mSiblingScroller = dynamic_cast<GuiScrollCtrl*>(*itr);
                  if (mSiblingScroller != NULL)
                  {
                     return mSiblingScroller->onKeyDown(event);
                  }
               }
            }

            // No luck... so don't try, next time.
            mUseSiblingScroller = false;
         }
      }
   }
	else if( event.keyCode == KEY_RETURN || event.keyCode == KEY_NUMPADENTER )
	{
      if ( event.modifier & SI_SHIFT &&
           mTextBuffer.length() + dStrlen("echo();") <= GuiTextCtrl::MAX_STRING_LENGTH )
      {
         // Wrap the text with echo( %s );

         char buf[GuiTextCtrl::MAX_STRING_LENGTH];
         getText( buf );

         String text( buf );         
         text.replace( ";", "" );

         text = String::ToString( "echo(%s);", text.c_str() );

         setText( text );
      }

		return Parent::dealWithEnter(false);
	}

   return Parent::onKeyDown(event);
}

