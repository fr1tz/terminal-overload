// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Register a Content Library
//
// Returns : Library Object ID or 0.
//-----------------------------------------------------------------------------
function GuiFormManager::RegisterLibrary( %libraryName, %libraryBasePath )
{
   %libraryPrepend = "GFCM";
   %newLibraryObjectName = %libraryPrepend @ %libraryName;

   // If the library already exists, just return it's object.
   if( isObject( %newLibraryObjectName ) )
      return %newLibraryObjectName.getId();

   // We must have the content manager to continue.
   if( !isObject( FormContentManager ) )
   {
      error("GuiFormManager::RegisterLibrary - Unable to find FormContentManager object!");
      return 0;
   }

   // Create Content Library.
   %newLibrary = new SimGroup( %newLibraryObjectName )
   {
      Name  = %libraryName;
   };

   // Expand Base Path
   %libraryFullPath = getPrefsPath( %libraryBasePath );

   // Store disk base path
   %newLibrary.basePath = %libraryFullPath;

   // Ensure Path Exists
   createPath( %libraryFullPath );

   // Add Library to Content Manager.
   FormContentManager.add( %newLibrary );

   // Create Content Library Ref Group.
   %newLibraryRefGroup = new SimGroup();
   %newLibraryRefGroup.setInternalName("RefGroup");
   %newLibrary.add( %newLibraryRefGroup );

   // Create Content Library Layout Group.
   %newLibraryLayoutGroup = new SimGroup();
   %newLibraryLayoutGroup.setInternalName("LayoutGroup");
   %newLibrary.add( %newLibraryLayoutGroup );

   // Add Library to Content Manager.
   FormContentManager.add( %newLibrary );


   // Add [none] Content.
   GuiFormManager::AddFormContent( %libraryName, $FormClassNoContentCaption );

   // Return Library Object.
   return %newLibrary;

}

//-----------------------------------------------------------------------------
// Unregister a Content Library
//
// Returns : True or False.
//-----------------------------------------------------------------------------
function GuiFormManager::UnregisterLibrary( %libraryName )
{
   // Find Library Object.
   %libraryObj = GuiFormManager::FindLibrary( %libraryName );

   if( !isObject( FormContentManager ) || !isObject( %libraryObj ) )
   {
      error("GuiFormManager::RegisterLibrary - Unable to find GuiFormManager or Library!");
      return false;
   }

   // Remove all Content Reference Objects in this Library.
   while( %libraryObj.getCount() > 0 )
   {
      if( isObject( %libraryObj.getObject( 0 ) ) )
         %libraryObj.getObject( 0 ).delete();
      %libraryObj.remove( 0 );
   }
   // Delete the library
   %libraryObj.delete();

   // Return Success.
   return true;
   
}


//-----------------------------------------------------------------------------
// Find a Content Library
//
// Returns : Library Object ID or 0.
//-----------------------------------------------------------------------------
function GuiFormManager::FindLibrary( %libraryName )
{
   // Generate Library Name.
   %libraryObjectName = "GFCM" @ %libraryName;

   // Find Library by Name.
   if( isObject( %libraryObjectName ) )
      return %libraryObjectName.getId();

   // Didn't find by name, see if this is already a library ID.
   if( isObject( %libraryName ) )
      return %libraryName;

   // Couldn't Find Library
   return 0;
}


function GuiFormManager::Init()
{
   // Create SimGroup.
   new SimGroup( FormContentManager ){};  
}


function GuiFormManager::Destroy()
{
   while( FormContentManager.getCount() > 0 )
   {
      %object = FormContentManager.getObject( 0 );

      if( isObject( %object ) )
         GuiFormManager::BroadcastContentMessage( %object, FormContentManager, "onLibraryDestroyed" );
         
      FormContentManager.remove( %object );
   }
   
   // Destroy SimGroup.
   if( isObject( FormContentManager ) )
      FormContentManager.delete();   
}
