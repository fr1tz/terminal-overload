// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// ----------------------------------------------------------------------------
// This is the default save location for any GuiProfiles created in the
// Gui Editor
// ----------------------------------------------------------------------------

if( !isObject( TolGuiWindowProfile ) )
new GuiControlProfile (TolGuiWindowProfile)
{
   opaque = false;
   border = "0";
   fillColor = "67 135 124 230";
   fillColorHL = "221 221 221 255";
   fillColorNA = "200 200 200 255";
   fontColor = "255 255 255 200";
   fontColorHL = "255 0 0 255";
   bevelColorHL = "255 255 255 255";
   bevelColorLL = "0 0 0 255";
   text = "untitled";
   bitmap = "notc/client/shell/images/window";
   textOffset = "8 4";
   hasBitmapArray = true;
   justify = "center";
   category = "TOL";
   fontColors[0] = "255 255 255 200";
   fontColors[5] = "255 0 255 255";
   fontColorLinkHL = "255 0 255 255";
   borderThickness = "0";
   fontSize = "30";
   fontColors[1] = "255 0 0 255";
   fontColors[7] = "Magenta";
};

if( !isObject( TolGuiMenuBackgroundProfile ) )
new GuiControlProfile (TolGuiMenuBackgroundProfile)
{
   category = "TOL";

   tab = false;
   canKeyFocus = false;
   hasBitmapArray = false;
   mouseOverSelected = false;

   // fill color
   opaque = false;
   fillColor = "67 135 124 255";
   //fillColorHL ="228 228 235";
   //fillColorSEL = "98 100 137";
   //fillColorNA = "255 255 255 ";

   // border color
   border = "0";
   borderColor   = "100 100 100 255"; 
   borderColorHL = "50 50 50 50";
   borderColorNA = "75 75 75 255"; 

   // font
   fontType = "Quantico";
   fontSize = "14";
   fontCharset = ANSI;

   fontColor = "0 0 0 255";
   fontColorHL = "0 0 0 255";
   fontColorNA = "0 0 0 255";
   fontColorSEL= "255 255 255 255";

   // bitmap information
   bitmapBase = "";
   textOffset = "0 0";

   // used by guiTextControl
   modal = true;
   justify = "left";
   autoSizeWidth = false;
   autoSizeHeight = false;
   returnTab = false;
   numbersOnly = false;
   cursorColor = "0 0 0 255";
   fillColorHL = "67 135 124 255";
   fillColorNA = "67 135 124 255";

   // sounds
   //soundButtonDown = "";
   //soundButtonOver = "";
};

if( !isObject( TolGuiMenuButtonProfile ) )
new GuiControlProfile( TolGuiMenuButtonProfile )
{
   opaque = true;
   border = "0";
   fontSize = "30";
   fontType = "Quantico";
   fontColor = "255 255 255 200";
   fontColorHL = "255 255 255 255";
   fontColorNA = "255 255 255 50";
   //fontColorSEL ="0 0 0";
   fixedExtent = 0;
   justify = "center";
   canKeyFocus = "1";
	bitmap = "notc/client/shell/images/selector-button";
   hasBitmapArray = false;
   category = "TOL";
   fontColors[0] = "255 255 255 200";
   fontColors[2] = "255 255 255 50";
   fillColor = "255 255 255 0";
   fillColorHL = "255 255 255 30";
   fillColorNA = "255 255 255 100";
   fillColorSEL = "255 255 255 80";
   borderThickness = "0";
   fontColors[1] = "255 255 255 255";
   fontColors[3] = "255 255 255 255";
   fontColors[6] = "255 0 255 255";
   fontColorSEL = "255 255 255 255";
   tab = "1";
   mouseOverSelected = "1";
};


if( !isObject( TolGuiMenuButtonItalicProfile ) )
new GuiControlProfile( TolGuiMenuButtonItalicProfile )
{
   opaque = true;
   border = "0";
   fontSize = "30";
   fontType = "Quantico Italic";
   fontColor = "255 255 255 200";
   fontColorHL = "255 255 255 255";
   fontColorNA = "255 255 255 50";
   //fontColorSEL ="0 0 0";
   fixedExtent = 0;
   justify = "center";
   canKeyFocus = false;
	bitmap = "notc/client/shell/images/selector-button";
   hasBitmapArray = false;
   category = "TOL";
   fontColors[0] = "255 255 255 200";
   fontColors[2] = "255 255 255 50";
   fillColor = "255 255 255 0";
   fillColorHL = "255 255 255 30";
   fillColorNA = "255 255 255 0";
   fillColorSEL = "255 255 255 80";
   borderThickness = "0";
   fontColors[1] = "255 255 255 255";
};

if( !isObject( TolMenuTextProfile ) )
new GuiControlProfile (TolMenuTextProfile)
{
   justify = "center";
   fontSize = "17";
   fontType = "Quantico";
   fontColor = "255 255 255 63";
   category = "TOL";
   fontColors[0] = "255 255 255 63";
};

if( !isObject( TolGuiOverlayProfile ) )
new GuiControlProfile( TolGuiOverlayProfile )
{
   opaque = true;
   fillcolor = "255 255 255";
   fontColor = "0 0 0";
   fontColorHL = "255 255 255";
	fillColor = "0 0 0 124";
   category = "TOL";
};

if( !isObject( TolGuiProgressBitmapProfile ) )
new GuiControlProfile( TolGuiProgressBitmapProfile )
{
   border = "0";
   hasBitmapArray = true;
   bitmap = "notc/client/shell/images/loadingbar.png";
   category = "TOL";
};

if( !isObject( TolGuiButtonProfile ) )
new GuiControlProfile( TolGuiButtonProfile )
{
   opaque = true;
   border = "0";
	 
   fontColor = "0 0 0 140";
   fontColorHL = "0 0 0 170";
	 fontColorNA = "0 0 0 50";
	 //fontColorSEL ="0 0 0";
   fixedExtent = 0;
   justify = "center";
   canKeyFocus = false;
	bitmap = "notc/client/shell/images/button";
   hasBitmapArray = false;
   category = "TOL";
   borderThickness = "0";
   fontSize = "25";
   fontColors[0] = "0 0 0 140";
   fontColors[2] = "0 0 0 50";
   fillColor = "255 255 255 140";
   fillColorHL = "228 0 235 255";
   fillColorNA = "255 255 255 2";
   fillColorSEL = "255 255 255 255";
   fontColors[3] = "0 0 0 170";
   fontColorSEL = "0 0 0 170";
   fontColors[1] = "0 0 0 170";
};

