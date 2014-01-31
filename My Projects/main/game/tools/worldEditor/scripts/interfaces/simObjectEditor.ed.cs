// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
// Define the field types for objects that link to the namespace MissionInfo
function SimObject::onDefineFieldTypes( %this )
{
   %this.setFieldType("Locked", "TypeBool");   
}