// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Override base controls
//GuiMenuButtonProfile.soundButtonOver = "AudioButtonOver";
//GuiMenuButtonProfile.soundButtonDown = "AudioButtonDown";

//-----------------------------------------------------------------------------
// Core Hud profiles

singleton GuiControlProfile ("HudScrollProfile")
{
   opaque = false;
   border = true;
   borderColor = "0 255 0";
   bitmap = "core/art/gui/images/scrollBar";
   hasBitmapArray = true;
};

singleton GuiControlProfile ("HudTextProfile")
{
   opaque = false;
   fillColor = "128 128 128";
   fontColor = "0 255 0";
   border = true;
   borderColor = "0 255 0";
};

//-----------------------------------------------------------------------------
// Center and bottom print

singleton GuiControlProfile ("CenterPrintProfile")
{
   opaque = false;
   fillColor = "128 128 128";
   fontColor = "0 255 0";
   border = true;
   borderColor = "0 255 0";
};

singleton GuiControlProfile ("CenterPrintTextProfile")
{
   opaque = false;
   fontType = "Quantico";
   fontSize = 16;
   fontColor = "0 255 0";
};

// -----------------------------------------------------------------------------
// HUD text
// -----------------------------------------------------------------------------

singleton GuiControlProfile (HudTextNormalProfile)
{
   opaque = false;
   fontType = "Quantico";
   fontSize = 14;
   fontColor = "255 255 255";
};

singleton GuiControlProfile(HudBigTextNormalProfile : HudTextNormalProfile)
{
   fontSize = 36;
};

singleton GuiControlProfile (HudTextItalicProfile : HudTextNormalProfile)
{
   fontType = "Quantico Italic";
};

singleton GuiControlProfile (HudTextBoldProfile : HudTextNormalProfile)
{
   fontType = "Quantico Bold";
};

singleton GuiControlProfile (HudTextCenterBoldProfile : HudTextNormalProfile)
{
   fontType = "Quantico Bold";
   justify = "Center";
};

// -----------------------------------------------------------------------------
// Numerical health text
// -----------------------------------------------------------------------------

singleton GuiControlProfile (NumericHealthProfile)
{
   opaque = true;
   justify = "center";
   fontType = "Quantico";
   fontSize = 32;
   fontColor = "255 255 255";
};


