// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


singleton GuiControlProfile (NavPanelProfile) 
{
   opaque = false;
   border = -2;
   category = "Editor";
};


singleton GuiControlProfile (NavPanel : NavPanelProfile) 
{
   bitmap = "./navPanel";
   category = "Editor";
};

singleton GuiControlProfile (NavPanelBlue : NavPanelProfile) 
{
   bitmap = "./navPanel_blue";
   category = "Editor";
};

singleton GuiControlProfile (NavPanelGreen : NavPanelProfile) 
{
   bitmap = "./navPanel_green";
   category = "Editor";
};

singleton GuiControlProfile (NavPanelRed : NavPanelProfile) 
{
   bitmap = "./navPanel_red";
   category = "Editor";
};

singleton GuiControlProfile (NavPanelWhite : NavPanelProfile) 
{
   bitmap = "./navPanel_white";
   category = "Editor";
};

singleton GuiControlProfile (NavPanelYellow : NavPanelProfile) 
{
   bitmap = "./navPanel_yellow";
   category = "Editor";
};
singleton GuiControlProfile (menubarProfile : NavPanelProfile) 
{
   bitmap = "./menubar";
   category = "Editor";
};
singleton GuiControlProfile (editorMenubarProfile : NavPanelProfile) 
{
   bitmap = "./editor-menubar";
   category = "Editor";
};
singleton GuiControlProfile (editorMenu_wBorderProfile : NavPanelProfile) 
{
   bitmap = "./menu-fullborder";
   category = "Editor";
};
singleton GuiControlProfile (inspectorStyleRolloutProfile : NavPanelProfile) 
{
   bitmap = "./inspector-style-rollout";
   category = "Editor";
};
singleton GuiControlProfile (inspectorStyleRolloutListProfile : NavPanelProfile) 
{
   bitmap = "./inspector-style-rollout-list";
   category = "Editor";
};
singleton GuiControlProfile (inspectorStyleRolloutDarkProfile : NavPanelProfile) 
{
   bitmap = "./inspector-style-rollout-dark";
   category = "Editor";
};
singleton GuiControlProfile (inspectorStyleRolloutInnerProfile : NavPanelProfile) 
{
   bitmap = "./inspector-style-rollout_inner";
   category = "Editor";
};
singleton GuiControlProfile (inspectorStyleRolloutNoHeaderProfile : NavPanelProfile)
{
   bitmap = "./inspector-style-rollout-noheader";
   category = "Editor";
};
singleton GuiControlProfile (IconDropdownProfile : NavPanelProfile) 
{
   bitmap = "./icon-dropdownbar";
   category = "Editor";
};
