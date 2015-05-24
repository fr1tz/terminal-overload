// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton GuiControlProfile(notcChatHudEditProfile)
{
   tab = "1";
   canKeyFocus = "1";
   fillColor = "255 255 255 255";
   fillColorHL = "128 128 128 255";
   borderThickness = "0";
   borderColor = "40 231 240 255";
   fontType = "Fixedsys Excelsior 2.00";
   fontSize = "20";
   fontColors[0] = "18 255 0 255";
   fontColors[1] = "40 231 240 255";
   fontColors[2] = "128 128 128 255";
   fontColors[4] = "255 0 255 255";
   fontColor = "18 255 0 255";
   fontColorHL = "40 231 240 255";
   fontColorNA = "128 128 128 255";
   fontColorLink = "255 0 255 255";
   textOffset = "0 2";
   autoSizeHeight = "1";
};

singleton GuiControlProfile(notcChatHudTextProfile)
{
   opaque = false;
   fillColor = "255 255 255";
   fillColorHL = "128 128 128";
   border = false;
   borderThickness = 0;
   borderColor = "40 231 240";
   fontColor = "18 255 0 255";
   fontColorHL = "40 231 240";
   fontColorNA = "128 128 128";
   textOffset = "0 0";
   autoSizeWidth = "1";
   autoSizeHeight = true;
   tab = true;
   canKeyFocus = true;
   fontType = "Fixedsys Excelsior 2.00";
   fontColors[0] = "255 255 255 255";
   fontColors[1] = "40 231 240 255";
   fontColors[2] = "128 128 128 255";
   fontSize = "20";
   fontColors[4] = "255 0 255 255";
   fontColorLink = "255 0 255 255";
};

singleton GuiControlProfile ("notcChatHudMessageProfile")
{
   fontType = "Fixedsys Excelsior 2.00";
   fontSize = "14";
   fontColor = "141 141 141 255";      // default color (death msgs, scoring, inventory)
   fontColors[1] = "250 230 100";   // client join/drop, tournament mode
   fontColors[2] = "250 100 100"; // gameplay, admin/voting, pack/deployable
   fontColors[3] = "70 250 100";   // team chat, spam protection message, client tasks
   fontColors[4] = "97 169 115 255";  // global chat
   fontColors[5] = "200 200 50 200";  // used in single player game
   // WARNING! Colors 6-9 are reserved for name coloring
   autoSizeWidth = true;
   autoSizeHeight = true;
   fontColors[0] = "141 141 141 255";
   fontColorHL = "250 230 100 255";
   fontColorNA = "250 100 100 255";
   fontColorSEL = "70 250 100 255";
   fontColorLink = "97 169 115 255";
   fontColorLinkHL = "200 200 50 200";
};

singleton GuiControlProfile ("notcChatHudScrollProfile")
{
   opaque = false;
   borderThickness = 0;
   borderColor = "0 255 0";
   bitmap = "core/art/gui/images/scrollBar";
   hasBitmapArray = true;
};

