// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Send a Message to all instances of a Content.
//
// Returns : The Number of Objects Communicated With or (0 if None).
//-----------------------------------------------------------------------------
function GuiFormManager::SendContentMessage( %contentObj, %sender, %message )
{
   // See if we Found the content object.
   if( %contentObj == 0 || !isObject( %contentObj ) )
   {
      //error( "GuiFormManager::SendContentMessage - Invalid Content Specified!" );
      return 0;
   }

   // Validate Ref List.
   if( !isObject( %contentObj.RefList ) )
   {
      //error( "GuiFormManager::SendContentMessage - Unable to find content RefList!" );
      return 0;
   }

   %refListObj = %contentObj.RefList.getID();

   %messagedObjects = 0;
   // Look for the content by name in our library.
   for( %i = 0; %i < %refListObj.getCount(); %i++ )
   {
      %object = %refListObj.getObject( %i );

      // Check for alternate MessageControl
      if( isObject( %object.MessageControl ) && %object.MessageControl.isMethod("onContentMessage") )
         %object.MessageControl.onContentMessage( %sender, %message );
      else if( %object.isMethod("onContentMessage") ) // Check for Default
         %object.onContentMessage( %sender, %message );
      else
         continue;
      %messagedObjects++;
   }

   // Return Success.
   return %messagedObjects;
}



//-----------------------------------------------------------------------------
// Send a Message to all instances of all Content.
//
// Returns : The Number of Objects Communicated With or (0 if None).
//-----------------------------------------------------------------------------
function GuiFormManager::BroadcastContentMessage( %libraryName, %sender, %message )
{
   %libraryObj = GuiFormManager::FindLibrary( %libraryName );
   // See if we Found the content object.
   if( %libraryObj == 0 || !isObject( %libraryObj ) )
   {
      //error( "GuiFormManager::BroadcastContentMessage - Invalid Library Specified!" );
      return 0;
   }

   // In a library the 0 object is always the ref group.
   %contentRefGroup = %libraryObj.getObject( 0 );

   // Validate Ref Group.
   if( !isObject( %contentRefGroup ) )
   {
      //error( "GuiFormManager::BroadcastContentMessage - Unable to find library RefGroup!" );
      return 0;
   }

   // Clear messaged object count
   %messagedObjects = 0;

   // Iterate over all contents ref lists and message everyone
   for( %refGroupIter = 0; %refGroupIter < %contentRefGroup.getCount(); %refGroupIter++ )
   {      

      // Fetch the Object Reference List Set
      %refListSet = %contentRefGroup.getObject( %refGroupIter );

    
      // Look for the content by name in our library.
      for( %i = 0; %i < %refListSet.getCount(); %i++ )
      {
         %object = %refListSet.getObject( %i );

         // Check for alternate MessageControl
         if( isObject( %object.MessageControl ) && %object.MessageControl.isMethod("onContentMessage") )
            %object.MessageControl.onContentMessage( %sender, %message );
         else if( %object.isMethod("onContentMessage") ) // Check for Default
            %object.onContentMessage( %sender, %message );
         else
            continue;

         // Increment Messaged Object Count.
         %messagedObjects++;
      }

   }

   // Return Success.
   return %messagedObjects;
}

