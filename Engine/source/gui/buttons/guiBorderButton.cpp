// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"

#include "gfx/gfxDevice.h"
#include "gfx/gfxDrawUtil.h"
#include "gui/core/guiCanvas.h"
#include "gui/buttons/guiButtonBaseCtrl.h"
#include "gui/core/guiDefaultControlRender.h"


class GuiBorderButtonCtrl : public GuiButtonBaseCtrl
{
   typedef GuiButtonBaseCtrl Parent;

protected:
public:
   DECLARE_CONOBJECT(GuiBorderButtonCtrl);

   void onRender(Point2I offset, const RectI &updateRect);
};

IMPLEMENT_CONOBJECT(GuiBorderButtonCtrl);

ConsoleDocClass( GuiBorderButtonCtrl,
   "@brief A push button that renders only a border.\n\n"
   
   "A border button consists of a border rendered along its extents according to the border thickness defined in its profile "
   "(GuiControlProfile::border).  For the border color, a color is selected from the profile according to current button state:\n"
   
   "- Default state: GuiControlProfile::borderColor\n"
   "- Highlighted (mouse is over the button): GuiControlProfile::fontColorHL\n"
   "- Depressed (mouse button down but not yet released): GuiControlProfile::fontColorSEL\n"
   
   "@ingroup GuiButtons\n"
);

void GuiBorderButtonCtrl::onRender(Point2I offset, const RectI &updateRect)
{
   if ( mProfile->mBorder > 0 )
   {
      RectI bounds( offset, getExtent() );
      for ( S32 i=0; i < mProfile->mBorderThickness; i++ )
      {
         GFX->getDrawUtil()->drawRect( bounds, mProfile->mBorderColor );
         bounds.inset( 1, 1 );
      }      
   }

   if ( mActive )
   {
      if ( mStateOn || mDepressed )
      {
         RectI bounds( offset, getExtent() );
         for ( S32 i=0; i < mProfile->mBorderThickness; i++ )
         {
            GFX->getDrawUtil()->drawRect( bounds, mProfile->mFontColorSEL );
            bounds.inset( 1, 1 );
         }
      }

      if ( mMouseOver )
      {
         RectI bounds( offset, getExtent() );
         for ( S32 i=0; i < mProfile->mBorderThickness; i++ )
         {
            GFX->getDrawUtil()->drawRect( bounds, mProfile->mFontColorHL );
            bounds.inset( 1, 1 );
         }
      }
   }

   renderChildControls( offset, updateRect );
}

