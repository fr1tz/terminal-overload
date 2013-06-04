// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GUIMISSIONAREAEDITORCTRL_H_
#define _GUIMISSIONAREAEDITORCTRL_H_

#ifndef _EDITTSCTRL_H_
#include "gui/worldEditor/editTSCtrl.h"
#endif
#ifndef _MISSIONAREA_H_
#include "T3D/missionArea.h"
#endif

class GuiMissionAreaEditorCtrl : public EditTSCtrl
{
   typedef EditTSCtrl Parent;

protected:
   SimObjectPtr<MissionArea>  mSelMissionArea;

public:
   GuiMissionAreaEditorCtrl();
   virtual ~GuiMissionAreaEditorCtrl();
   
   DECLARE_CONOBJECT(GuiMissionAreaEditorCtrl);

   // SimObject
   bool onAdd();
   static void initPersistFields();

   // EditTSCtrl      
   void get3DCursor( GuiCursor *&cursor, bool &visible, const Gui3DMouseEvent &event_ );

   void setSelectedMissionArea( MissionArea *missionArea );
   MissionArea* getSelectedMissionArea() { return mSelMissionArea; };
};

#endif // _GUIMISSIONAREAEDITORCTRL_H_
