// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Override base controls
//GuiMenuButtonProfile.soundButtonOver = "AudioButtonOver";
//GuiMenuButtonProfile.soundButtonDown = "AudioButtonDown";

//-----------------------------------------------------------------------------
// Chat Hud profiles


singleton GuiControlProfile (ChatHudEditProfile)
{
   opaque = false;
   fillColor = "255 255 255";
   fillColorHL = "128 128 128";
   border = false;
   borderThickness = 0;
   borderColor = "40 231 240";
   fontColor = "40 231 240";
   fontColorHL = "40 231 240";
   fontColorNA = "128 128 128";
   textOffset = "0 2";
   autoSizeWidth = false;
   autoSizeHeight = true;
   tab = true;
   canKeyFocus = true;
};

singleton GuiControlProfile (ChatHudTextProfile)
{
   opaque = false;
   fillColor = "255 255 255";
   fillColorHL = "128 128 128";
   border = false;
   borderThickness = 0;
   borderColor = "40 231 240";
   fontColor = "40 231 240";
   fontColorHL = "40 231 240";
   fontColorNA = "128 128 128";
   textOffset = "0 0";
   autoSizeWidth = true;
   autoSizeHeight = true;
   tab = true;
   canKeyFocus = true;
};

singleton GuiControlProfile ("ChatHudMessageProfile")
{
   fontType = "Quantico";
   fontSize = 16;
   fontColor = "150 150 150";      // default color (death msgs, scoring, inventory)
   fontColors[1] = "250 230 100";   // client join/drop, tournament mode
   fontColors[2] = "250 100 100"; // gameplay, admin/voting, pack/deployable
   fontColors[3] = "70 250 100";   // team chat, spam protection message, client tasks
   fontColors[4] = "250 250 250";  // global chat
   fontColors[5] = "200 200 50 200";  // used in single player game
   // WARNING! Colors 6-9 are reserved for name coloring
   autoSizeWidth = true;
   autoSizeHeight = true;
};

singleton GuiControlProfile ("ChatHudScrollProfile")
{
   opaque = false;
   borderThickness = 0;
   borderColor = "0 255 0";
   bitmap = "core/art/gui/images/scrollBar";
   hasBitmapArray = true;
};


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

singleton GuiControlProfile ("ChatHudBorderProfile")
{
   bitmap = "core/art/gui/images/chatHudBorderArray";
   hasBitmapArray = true;
   opaque = false;
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
   fontSize = 12;
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
