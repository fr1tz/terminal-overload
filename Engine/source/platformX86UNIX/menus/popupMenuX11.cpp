//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "platform/menus/popupMenu.h"

//////////////////////////////////////////////////////////////////////////

void PopupMenu::createPlatformPopupMenuData()
{
}

void PopupMenu::deletePlatformPopupMenuData()
{
}

void PopupMenu::createPlatformMenu()
{
}

//////////////////////////////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////////////////////////////

S32 PopupMenu::insertItem(S32 pos, const char *title, const char* accelerator)
{
    return -1;
}

S32 PopupMenu::insertSubMenu(S32 pos, const char *title, PopupMenu *submenu)
{
    return -1;
}

bool PopupMenu::setItem(S32 pos, const char *title, const char* accelerator)
{
    return false;
}

void PopupMenu::removeItem(S32 itemPos)
{
}

//////////////////////////////////////////////////////////////////////////

void PopupMenu::enableItem( S32 pos, bool enable )
{
}

void PopupMenu::checkItem(S32 pos, bool checked)
{
}

void PopupMenu::checkRadioItem(S32 firstPos, S32 lastPos, S32 checkPos)
{
}

bool PopupMenu::isItemChecked(S32 pos)
{
    return false;
}

U32 PopupMenu::getItemCount()
{
    return 0;
}

//////////////////////////////////////////////////////////////////////////

bool PopupMenu::canHandleID(U32 id)
{
    return false;
}

bool PopupMenu::handleSelect(U32 command, const char *text /* = NULL */)
{
    return false;
}

//////////////////////////////////////////////////////////////////////////

void PopupMenu::showPopup(GuiCanvas *owner, S32 x /* = -1 */, S32 y /* = -1 */)
{
}

//////////////////////////////////////////////////////////////////////////

void PopupMenu::attachToMenuBar(GuiCanvas *owner, S32 pos, const char *title)
{
}

// New version of above for use by MenuBar class. Do not use yet.
void PopupMenu::attachToMenuBar(GuiCanvas *owner, S32 pos)
{
}

void PopupMenu::removeFromMenuBar()
{
}

S32 PopupMenu::getPosOnMenuBar()
{
    return 0;
}

