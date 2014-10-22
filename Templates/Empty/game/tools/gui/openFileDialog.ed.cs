// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function getLoadFilename(%filespec, %callback, %currentFile)
{   
   %dlg = new OpenFileDialog()
   {
      Filters = %filespec;
      DefaultFile = %currentFile;
      ChangePath = false;
      MustExist = true;
      MultipleFiles = false;
   };
   
   if ( filePath( %currentFile ) !$= "" )
      %dlg.DefaultPath = filePath(%currentFile);  
      
   if ( %dlg.Execute() )
   {
      eval(%callback @ "(\"" @ %dlg.FileName @ "\");");
      $Tools::FileDialogs::LastFilePath = filePath( %dlg.FileName );
   }
   
   %dlg.delete();
}

// Opens a choose file dialog with format filters already loaded
// in. This avoids the issue of passing a massive list of format 
// filters into a function as an arguement.
function getLoadFormatFilename(%callback, %currentFile)
{   
   %dlg = new OpenFileDialog()
   {
      Filters = getFormatFilters() @ "(All Files (*.*)|*.*|";
      DefaultFile = %currentFile;
      ChangePath = false;
      MustExist = true;
      MultipleFiles = false;
   };
   
   if ( filePath( %currentFile ) !$= "" )
      %dlg.DefaultPath = filePath(%currentFile);  
      
   if ( %dlg.Execute() )
   {
      eval(%callback @ "(\"" @ %dlg.FileName @ "\");");
      $Tools::FileDialogs::LastFilePath = filePath( %dlg.FileName );
   }
   
   %dlg.delete();
}
