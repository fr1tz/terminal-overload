// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if(!isObject(notcHudLightWindowProfile))
new GuiControlProfile(notcHudLightWindowProfile)
{
   opaque = false;
   border = "0";
   fillColor = "255 255 255 200";
   fillColorHL = "221 221 221 255";
   fillColorNA = "200 200 200 255";
   bevelColorHL = "255 255 255 255";
   bevelColorLL = "0 0 0 255";
   text = "untitled";
   bitmap = "./window";
   textOffset = "8 6";
   hasBitmapArray = true;
   justify = "center";
   category = "NOTC";
   fontColors[0] = "0 0 0 255";
   fontColors[5] = "255 0 255 255";
   fontColorLinkHL = "255 0 255 255";
   borderThickness = "0";
   fontType = "Cat5";
   fontSize = "12";
   fontColors[1] = "255 0 0 255";
   fontColors[7] = "Magenta";
};

if(!isObject(notcHudDarkWindowProfile))
new GuiControlProfile(notcHudDarkWindowProfile)
{
   opaque = false;
   border = "0";
   fillColor = "0 0 0 200";
   fillColorHL = "221 221 221 255";
   fillColorNA = "200 200 200 255";
   bevelColorHL = "255 255 255 255";
   bevelColorLL = "0 0 0 255";
   text = "untitled";
   bitmap = "./window";
   textOffset = "8 6";
   hasBitmapArray = true;
   justify = "center";
   category = "NOTC";
   fontColors[0] = "255 255 255 255";
   fontColors[5] = "255 0 255 255";
   fontColorLinkHL = "255 0 255 255";
   borderThickness = "0";
   fontType = "Cat5";
   fontSize = "12";
   fontColors[1] = "255 0 0 255";
   fontColors[7] = "Magenta";
};
