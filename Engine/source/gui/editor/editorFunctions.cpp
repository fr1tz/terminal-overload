// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gui/editor/editorFunctions.h"

#include "console/simObject.h"


bool validateObjectName( const char *data, const SimObject *object )
{
   if( !data || !data[ 0 ] )
      return true;

   bool isValidId = true;
   if( !dIsalpha( data[ 0 ] ) && data[ 0 ] != '_' )
      isValidId = false;
   else
   {
      for( U32 i = 1; data[ i ] != '\0'; ++ i )
      {
         if( !dIsalnum( data[ i ] ) && data[ i ] != '_' )
         {
            isValidId = false;
            break;
         }
      }
   }

   if( !isValidId )
   {
      Platform::AlertOK( "Invalid Object Name", avar( "'%s' is not a valid "
         "object name.  Please choose a name that begins with a letter or "
         "underscore and is otherwise comprised exclusively of letters, "
         "digits, and/or underscores.", data ) );
      return false;
   }

   SimObject *pTemp = NULL;
   if ( Sim::findObject( data, pTemp ) && pTemp != object )
   {
      const char* filename = pTemp->getFilename();
      if ( !filename || !filename[0] )
         filename = "an unknown file";

      Platform::AlertOK( "Invalid Object Name", avar( "Object names must be unique, "
         "and there is an existing %s object with the name '%s' (defined in %s).  "
         "Please choose another name.", pTemp->getClassName(), data, filename ) );
      return false;
   }

   if ( AbstractClassRep::findClassRep( data ) )
   {
      Platform::AlertOK( "Invalid Object Name", avar( "'%s' is the name of an "
         "existing TorqueScript class.  Please choose another name.", data ) );
      return false;
   }

   return true;
}