// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if( !isObject( XaNotcCatHudXJumpChargeProfile ) )
new GuiControlProfile( XaNotcCatHudXJumpChargeProfile )
{
   opaque = true;
   fillcolor = "0 125 255";
   fontColor = "0 0 0";
   fontColorHL = "150 150 150";
   //borderColor = GuiDefaultProfile.borderColor;
   border = true;
};

singleton GuiControlProfile(NotcCatHudNumericTextProfile)
{
   opaque = false;
   fillColor = "255 255 255";
   fillColorHL = "128 128 128";
   border = false;
   borderThickness = 0;
   borderColor = "40 231 240";
   fontColor = "2 2 2 255";
   fontColorHL = "40 231 240";
   fontColorNA = "128 128 128";
   textOffset = "0 0";
   autoSizeWidth = "0";
   autoSizeHeight = "0";
   tab = true;
   canKeyFocus = true;
   fontType = "Segment7";
   fontSize = "35";
   fontColors[0] = "2 2 2 255";
   fontColors[1] = "40 231 240 255";
   fontColors[2] = "128 128 128 255";
   justify = "Right";
   category = "NOTC";
};

singleton GuiControlProfile(NotcCatHudDefaultProfile : GuiDefaultProfile)
{
   fillColor = "255 255 255 255";
};

singleton GuiControlProfile(NotcCatHudHealthProfile : GuiDefaultProfile)
{
   fillColor = "255 255 0 255";
};

singleton GuiControlProfile(NotcCatHudShieldProfile : GuiDefaultProfile)
{
   fillColor = "255 255 255 255";
};
