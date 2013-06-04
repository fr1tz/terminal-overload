// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function getSaveFilename( %filespec, %callback, %currentFile, %overwrite )
{
   if( %overwrite $= "" )
      %overwrite = true;
   
   %dlg = new SaveFileDialog()
   {
      Filters = %filespec;
      DefaultFile = %currentFile;
      ChangePath = false;
      OverwritePrompt = %overwrite;
   };
   
   if( filePath( %currentFile ) !$= "" )
      %dlg.DefaultPath = filePath( %currentFile );
   else
      %dlg.DefaultPath = getMainDotCSDir();
      
   if( %dlg.Execute() )
   {
      %filename = %dlg.FileName;
      eval( %callback @ "(\"" @ %filename @ "\");" );
   }
   
   %dlg.delete();
}
