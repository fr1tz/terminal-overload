// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


//-----------------------------------------------------------------------------
// Add Content Reference to RefList
//
// Returns : True or False.
//-----------------------------------------------------------------------------
function GuiFormManager::AddContentReference( %library, %contentName, %control )
{
   // Fetch Content Object.
   %contentObj = GuiFormManager::FindFormContent( %library, %contentName );

   // See if we Found the Library.
   if( %contentObj == 0 || !isObject( %contentObj ) )
   {
      error( "GuiFormManager::AddContentReference - Unable to Find Library by Name or ID!" );
      return false;
   }

   // Validate Ref List.
   if( !isObject( %contentObj.RefList ) )
   {
      error( "GuiFormManager::AddContentReference - Unable to find content RefList!" );
      return false;
   }

   //error("adding ref for object" SPC %control );

   // Add Control Reference.
   %contentObj.RefList.add( %control );

   // Return Success.
   return true;
}

//-----------------------------------------------------------------------------
// Remove Content Reference from RefList
//
// Returns : True or False.
//-----------------------------------------------------------------------------
function GuiFormManager::RemoveContentReference( %library, %contentName, %control )
{
   // Fetch Content Object.
   %contentObj = GuiFormManager::FindFormContent( %library, %contentName );

   // See if we Found the Library.
   if( %contentObj == 0 || !isObject( %contentObj ) )
   {
      error( "GuiFormManager::AddContentReference - Unable to Find Library by Name or ID!" );
      return false;
   }

   // Validate Ref List.
   if( !isObject( %contentObj.RefList ) )
   {
      error( "GuiFormManager::AddContentReference - Unable to find content RefList!" );
      return false;
   }

   //error("removing ref for object" SPC %control );

   // Add Control Reference.
   %contentObj.RefList.remove( %control );
   
   if( %control.isMethod("onFormRemove") )
      %control.onFormRemove();

   // Return Success.
   return true;
}

//-----------------------------------------------------------------------------
// Gets the current number of instances of the specified content that are active
//
// Returns : Number of instances or 0.
//-----------------------------------------------------------------------------
function GuiFormManager::GetContentCount( %library, %contentName )
{
   // Fetch Content Object.
   %contentObj = GuiFormManager::FindFormContent( %library, %contentName );

   // See if we Found the Library.
   if( %contentObj == 0 || !isObject( %contentObj ) )
   {
      error( "GuiFormManager::GetContentCount - Unable to Find Library by Name or ID!" );
      return 0;
   }

   // Validate Ref List.
   if( !isObject( %contentObj.RefList ) )
   {
      error( "GuiFormManager::GetContentCount - Unable to find content RefList!" );
      return 0;
   }

   // Return Count.
   return %contentObj.RefList.getCount();
}
