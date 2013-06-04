// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Material Editor Written by Dave Calabrese of Gaslight Studios

singleton GuiControlProfile (GuiMatEdSliderProfile)
{
   bitmap = "./matEdSlider";
   category = "Editor";
};

singleton GuiControlProfile (GuiMatEdRightJustifyProfile)
{
   // font
   fontType = "Arial";
   fontSize = 14;
   fontCharset = ANSI;

   fontColor = "0 0 0";
   
   justify = "right";
   category = "Editor";
};

singleton GuiControlProfile(GuiMatEdPopUpMenuProfile)
{
   opaque = false;
   mouseOverSelected = true;
   textOffset = "3 3";
   border = 1;
   /*borderThickness = 1;*/
   fixedExtent = true;
   //bitmap = "./images/scrollbar";
   bitmap = "tools/editorClasses/gui/images/scroll";
   hasBitmapArray = true;
   profileForChildren = GuiControlListPopupProfile;
   fillColor = "255 0 0 255";
   fontColor = "255 255 255 255";
   fillColorHL = "50 50 50";
   fontColorHL = "220 220 220";
   borderColor = "100 100 108";
   category = "Editor";
};

singleton GuiControlProfile (MatEdCenteredTextProfile)
{
   fontColor = "0 0 0";
   justify = "center";
   category = "Editor";
};
