// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton GuiControlProfile( MeshRoadEditorProfile )
{
   canKeyFocus = true;
   opaque = true;
   fillColor = "192 192 192 192";
   category = "Editor";
};

singleton GuiControlProfile (GuiDisabledTextEditProfile)
{
   opaque = false;   
   border = 0;
   bitmap = "./textEdit";
   borderColor = "255 255 255 200";
   fontColor = "0 0 0";
   fontColorHL = "255 255 255";
   fontColorNA = "128 128 128";
   textOffset = "4 2";
   autoSizeWidth = false;
   autoSizeHeight = false;
   tab = false;
   canKeyFocus = false;   
   category = "Editor";
};

singleton GuiControlProfile (GuiSimpleBorderProfile)
{
   opaque = false;   
   border = 1;   
   category = "Editor";
};