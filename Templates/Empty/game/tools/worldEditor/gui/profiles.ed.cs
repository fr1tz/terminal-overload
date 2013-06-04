// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton GuiControlProfile (EditorDefaultProfile)
{
   opaque = true;
   category = "Editor";
};

singleton GuiControlProfile (EditorToolButtonProfile)
{
   opaque = true;
   border = 2;
   category = "Editor";
};

singleton GuiControlProfile (EditorTextProfile)
{
   fontType = "Arial Bold";
   fontColor = "0 0 0";
   autoSizeWidth = true;
   autoSizeHeight = true;
   category = "Editor";
};

singleton GuiControlProfile (EditorTextProfileWhite)
{
   fontType = "Arial Bold";
   fontColor = "255 255 255";
   autoSizeWidth = true;
   autoSizeHeight = true;
   category = "Editor";
};

singleton GuiControlProfile (WorldEditorProfile)
{
   canKeyFocus = true;
   category = "Editor";
};

singleton GuiControlProfile (EditorScrollProfile)
{
   opaque = true;
   fillColor = "192 192 192 192";
   border = 3;
   borderThickness = 2;
   borderColor = "0 0 0";
   bitmap = "tools/gui/images/scrollBar";
   hasBitmapArray = true;
   category = "Editor";
};

singleton GuiControlProfile (GuiEditorClassProfile)
{
   opaque = true;
   fillColor = "232 232 232";
   border = true;
   borderColor   = "0 0 0";
   borderColorHL = "127 127 127";
   fontColor = "0 0 0";
   fontColorHL = "50 50 50";
   fixedExtent = true;
   justify = "center";
   bitmap = "tools/gui/images/scrollBar";
   hasBitmapArray = true;
   category = "Editor";
};

singleton GuiControlProfile( EPainterBitmapProfile )
{
   opaque = false;
   border = false;
   borderColor ="243 242 241";
   Color ="230 230 230";
   category = "Editor";
};

singleton GuiControlProfile( EPainterBorderButtonProfile : ToolsGuiDefaultProfile )
{
   border = true;
   borderColor = "0 0 0";
   borderThickness = 2;
   
   fontColorHL = "255 0 0";
   fontColorSEL = "0 0 255";
   category = "Editor";
};

singleton GuiControlProfile( EPainterDragDropProfile )
{
   justify = "center";
   fontColor = "0 0 0";
   border = 0;
   textOffset = "0 0";   
   opaque = true;
   fillColor = "221 221 221 150";
   category = "Editor";
};

singleton GizmoProfile( GlobalGizmoProfile )
{
   // This isnt a GuiControlProfile but fits in well here.
   // Don't really have to initialize this now because that will be done later 
   // based on the saved editor prefs.
   screenLength = 100;
   category = "Editor";
};
