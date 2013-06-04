// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
$FormClassNoContentCaption = "None";

//-----------------------------------------------------------------------------
// Add Form Content to a Library or Update if it Already Exists
//
// Returns : Content ID or 0.
//-----------------------------------------------------------------------------
function GuiFormManager::AddFormContent( %library, %contentName, %contentCreate, %contentSave, %contentMargin )
{
   // See if we were passed a library ID.
   if( !isObject( %library ) )
      %libraryObj = GuiFormManager::FindLibrary( %library );
   else
      %libraryObj = %library;

   // See if we Found the Library.
   if( %libraryObj == 0 || !isObject( %libraryObj ) )
   {
      error( "GuiFormManager::AddFormContent - Unable to Find Library by Name or ID!" );
      return 0;
   }

   // See if this reference already exists.
   %contentRef = GuiFormManager::FindFormContent( %libraryObj, %contentName );

   // If it exists, just update it's create/save functions.
   if( %contentRef != 0 )
   {
      // Echo Update.
      //echo( "GuiFormManager::AddFormContent - Found Existent Content Reference, Updating Create/Save Functions" );

      // Apply Update.
      %contentRef.CreateFunction = %contentCreate;
      %contentRef.SaveFunction   = %contentSave;
      %contentRef.Margin         = %contentMargin;
      
      // Return Success.
      return %contentRef;
   }

   // Create Content Reference List.
   %refList = new SimSet();

   // Add Reference List to Library.
   %libraryObj.getObject(0).add( %refList );

   // Create Content Reference Object.
   %newContentRef = new ScriptObject()
   {
      Name           = %contentName;
      CreateFunction = %contentCreate;
      SaveFunction   = %contentSave; 
      Margin         = %contentMargin;
      RefList        = %refList;
   };

   // Add to library.
   %libraryObj.add( %newContentRef );

   // Return Success.
   return %newContentRef;
}

//-----------------------------------------------------------------------------
// Remove Form Content from a Library
//
// Returns : True or False.
//-----------------------------------------------------------------------------
function GuiFormManager::RemoveFormContent( %library, %contentName )
{
   // See if we were passed a library ID.
   if( !isObject( %library ) )
      %libraryObj = GuiFormManager::FindLibrary( %library );
   else
      %libraryObj = %library;

   // See if we Found the Library.
   if( %libraryObj == 0 || !isObject( %libraryObj ) )
      return false;

   // See if this reference already exists.
   %contentRef = GuiFormManager::FindFormContent( %libraryObj, %contentName );

   // If it doesn't exist, just return success.
   if( %contentRef == 0 || !isObject( %contentRef ) )
      return true;

   // Remove From Library.
   %libraryObj.remove( %contentRef );

   // Return Success.
   return true;
}


//-----------------------------------------------------------------------------
// Find Form Content in a Library
//
// Returns : Content Reference Object ID or 0.
//-----------------------------------------------------------------------------
function GuiFormManager::FindFormContent( %library, %contentName )
{
   // See if we were passed a library ID.
   if( !isObject( %library ) )
      %libraryObj = GuiFormManager::FindLibrary( %library );
   else
      %libraryObj = %library;

   // See if we Found the Library.
   if( %libraryObj == 0 || !isObject( %libraryObj ) )
      return 0;

   // Look for the content by name in our library.
   for( %i = 0; %i < %libraryObj.getCount(); %i++ )
   {
      %object = %libraryObj.getObject( %i );
      if( %object.Name $= %contentName )
         return %object;
   }

   // Return Failure.
   return 0;
}

//-----------------------------------------------------------------------------
// Get Form Content in a Library by Index
//
// Returns : Content Reference Object ID or 0.
//-----------------------------------------------------------------------------
function GuiFormManager::GetFormContentByIndex( %library, %index )
{
   // See if we were passed a library ID.
   if( !isObject( %library ) )
      %libraryObj = GuiFormManager::FindLibrary( %library );
   else
      %libraryObj = %library;

   // See if we Found the Library.
   if( %libraryObj == 0 || !isObject( %libraryObj ) )
      return 0;

   if( %index < %libraryObj.getCount() )
      return %libraryObj.getObject( %index );

}


//-----------------------------------------------------------------------------
// Get Form Content Count in a Library
//
// Returns : Number of content objects in this library or 0
//-----------------------------------------------------------------------------
function GuiFormManager::GetFormContentCount( %library )
{
   // See if we were passed a library ID.
   if( !isObject( %library ) )
      %libraryObj = GuiFormManager::FindLibrary( %library );
   else
      %libraryObj = %library;

   // See if we Found the Library.
   if( %libraryObj == 0 || !isObject( %libraryObj ) )
   {
      return 0;
   }

   // Return Count.
   return %libraryObj.getCount();
}
