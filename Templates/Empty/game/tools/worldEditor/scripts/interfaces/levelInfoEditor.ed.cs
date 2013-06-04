// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
// Define the field types for objects that link to the namespace LevelInfo
function LevelInfo::onDefineFieldTypes( %this )
{
   %this.setFieldType("Desc", "TypeString");
   %this.setFieldType("DescLines", "TypeS32");
}
