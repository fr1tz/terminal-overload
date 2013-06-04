// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gui/utility/guiBubbleTextCtrl.h"
#include "gui/core/guiCanvas.h"

IMPLEMENT_CONOBJECT(GuiBubbleTextCtrl);

ConsoleDocClass( GuiBubbleTextCtrl,
   "@brief A single-line text control that displays its text in a multi-line popup when clicked.\n\n"

   "This control acts like a GuiTextCtrl (and inherits from it), when clicked it creates a GuiMLTextCtrl "
   "roughly where you clicked with the same text in it.  This allows you to have a single line text control "
   "which upon clicking will display the entire text contained in a multi-line format.\n\n"

   "@tsexample\n"
   "new GuiBubbleTextCtrl(BubbleTextGUI)\n"
   "{\n"
   "   text = \"This is the first sentence.  This second sentence can be sized outside of the default single "
               "line view, upon clicking this will be displayed in a multi-line format.\";\n"
   "};\n"
   "@endtsexample\n\n"

   "@see GuiTextCtrl\n"
   "@see GuiMLTextCtrl\n\n"

   "@ingroup GuiControls\n"
);

//------------------------------------------------------------------------------
void GuiBubbleTextCtrl::popBubble()
{
	// Release the mouse:
	mInAction = false;
	mouseUnlock();

	// Pop the dialog
	getRoot()->popDialogControl(mDlg);

	// Kill the popup
	mDlg->removeObject(mPopup);
	mPopup->removeObject(mMLText);
	mMLText->deleteObject();
	mPopup->deleteObject();
	mDlg->deleteObject();
}

//------------------------------------------------------------------------------
void GuiBubbleTextCtrl::onMouseDown(const GuiEvent &event)
{
	if (mInAction)
	{
		popBubble();

		return;
	}

	mDlg = new GuiControl();
   AssertFatal(mDlg, "Failed to create the GuiControl for the BubbleTextCtrl");
   mDlg->setDataField( StringTable->insert("profile"), NULL, "GuiModelessDialogProfile");
   mDlg->setField("horizSizing", "width");
	mDlg->setField("vertSizing", "height");
	mDlg->setField("extent", "640 480");

   mPopup = new GuiControl();
   AssertFatal(mPopup, "Failed to create the GuiControl for the BubbleTextCtrl");
   mPopup->setDataField( StringTable->insert("profile"), NULL, "GuiBubblePopupProfile");

   mMLText = new GuiMLTextCtrl();
   AssertFatal(mMLText, "Failed to create the GuiMLTextCtrl for the BubbleTextCtrl");
	mMLText->setDataField( StringTable->insert("profile"), NULL, "GuiBubbleTextProfile");
	mMLText->setField("position", "2 2");
	mMLText->setField("extent", "296 51");	
	
	mMLText->setText((char*)mText,dStrlen(mText));

	mMLText->registerObject();
	mPopup->registerObject();
	mDlg->registerObject();

	mPopup->addObject(mMLText);
	mDlg->addObject(mPopup);

	mPopup->resize(event.mousePoint,Point2I(300,55));

	getRoot()->pushDialogControl(mDlg,0);
	mouseLock();

	mInAction = true;
}
