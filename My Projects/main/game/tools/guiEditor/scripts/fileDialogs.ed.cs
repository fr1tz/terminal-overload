// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

$GUI::FileSpec = "Torque Gui Files (*.gui)|*.gui|All Files (*.*)|*.*|";

/// GuiBuilder::getSaveName - Open a Native File dialog and retrieve the
///  location to save the current document.
/// @arg defaultFileName   The FileName to default in the field and to be selected when a path is opened
function GuiBuilder::getSaveName( %defaultFileName )
{
   %defaultPath = GuiEditor.LastPath;
   
   if( %defaultFileName $= "" )
   {
      %prefix = "";
      if( isFunction( "isScriptPathExpando" ) )
      {
         // if we're editing a game, we want to default to the games dir.
         // if we're not, then we default to the tools directory or the base.
         if( isScriptPathExpando( "^game") )
            %prefix = "^game/";
         else if( isScriptPathExpando( "^tools" ) )
            %prefix = "^tools/";
      }
         
      %defaultFileName = expandFilename( %prefix @ "gui/untitled.gui" );
   }
   else
      %defaultPath = filePath( %defaultFileName );
      
   %dlg = new SaveFileDialog()
   {
      Filters           = $GUI::FileSpec;
      DefaultPath       = makeFullPath( %defaultPath );
      DefaultFile       = %defaultFileName;
      ChangePath        = false;
      OverwritePrompt   = true;
   };
         
   if( %dlg.Execute() )
   {
      GuiEditor.LastPath = filePath( %dlg.FileName );
      %filename = %dlg.FileName;
      if( fileExt( %filename ) !$= ".gui" )
         %filename = %filename @ ".gui";
   }
   else
      %filename = "";
      
   %dlg.delete();
      
   return %filename;
}

function GuiBuilder::getOpenName( %defaultFileName )
{
   if( %defaultFileName $= "" )
      %defaultFileName = expandFilename("^game/gui/untitled.gui");
   
   %dlg = new OpenFileDialog()
   {
      Filters        = $GUI::FileSpec;
      DefaultPath    = GuiEditor.LastPath;
      DefaultFile    = %defaultFileName;
      ChangePath     = false;
      MustExist      = true;
   };
         
   if(%dlg.Execute())
   {
      GuiEditor.LastPath = filePath( %dlg.FileName );
      %filename = %dlg.FileName;      
      %dlg.delete();
      return %filename;
   }
   
   %dlg.delete();
   return "";   
}
