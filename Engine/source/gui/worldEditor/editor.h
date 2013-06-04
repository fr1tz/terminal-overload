// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _EDITOR_H_
#define _EDITOR_H_

#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif
#ifndef _GUICONTROL_H_
#include "gui/core/guiControl.h"
#endif

class GameBase;

//------------------------------------------------------------------------------

class EditManager : public GuiControl
{
   private:
      typedef GuiControl Parent;

   public:
      EditManager();
      ~EditManager();

      bool onWake();
      void onSleep();

      // SimObject
      bool onAdd();

      /// Perform the onEditorEnabled callback on all SimObjects
      /// and set gEditingMission true.
      void editorEnabled();

      /// Perform the onEditorDisabled callback on all SimObjects
      /// and set gEditingMission false.
      void editorDisabled();

      MatrixF mBookmarks[10];
      DECLARE_CONOBJECT(EditManager);
      DECLARE_CATEGORY( "Gui Editor" );
};

extern bool gEditingMission;

//------------------------------------------------------------------------------

#endif
