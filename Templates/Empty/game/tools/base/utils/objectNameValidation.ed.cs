// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


function Editor::validateObjectName( %name, %mustHaveName )
{
   if( %mustHaveName && %name $= "" )
   {
      MessageBoxOK( "Missing Object Name", "No name given for object.  Please enter a valid object name." );
      return false;
   }
   if( !isValidObjectName( %name ) )
   {
      MessageBoxOK( "Invalid Object Name", "'" @ %name @ "' is not a valid object name." NL
         "" NL
         "Please choose a name that begins with a letter or underscore and is otherwise comprised " @
         "exclusively of letters, digits, and/or underscores."
      );
      return false;
   }
   if( isObject( %name ) )
   {
      %filename = %name.getFilename();
      if ( %filename $= "" )
         %filename = "an unknown file";

      MessageBoxOK( "Invalid Object Name", "Object names must be unique, and there is an " @
         "existing " @ %name.getClassName() @ " object with the name '" @ %name @ "' (defined " @
         "in " @ %filename @ ").  Please choose another name." );
      return false;
   }
   if( isClass( %name ) )
   {
      MessageBoxOK( "Invalid Object Name", "'" @ %name @ "' is the name of an existing TorqueScript " @
         "class.  Please choose another name." );
      return false;
   }

   return true;
}
