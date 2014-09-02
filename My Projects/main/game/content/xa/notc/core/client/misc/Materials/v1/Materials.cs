// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function clientCmd_XaNotcMaterials_Clear()
{
   echo("clientCmd_XaNotcMaterials_Clear()");
   
   if(isObject(ServerMaterialsGroup))
   {
      echo(" Have access to ServerMaterialsGroup, no need for action.");
      return;
   }

   if(isObject(XaNotcMaterialsGroup))
      XaNotcMaterialsGroup.delete();
}

function clientCmd_XaNotcMaterials_Load(%pathMask)
{
   echo("clientCmd_XaNotcMaterials_Load():" SPC %pathMask);
   
   if(isObject(ServerMaterialsGroup))
   {
      echo(" Have access to ServerMaterialsGroup, no need for action.");
      return;
   }
   
   %instantGroupStor = $instantGroup;

   if(!isObject(XaNotcMaterialsGroup))
   {
      $instantGroup = MissionCleanup;
      new SimGroup(XaNotcMaterialsGroup);
   }
   
   $instantGroup = XaNotcMaterialsGroup;

   for( %file = findFirstFile( %pathMask @ "/*/materials.cs.dso" );
        %file !$= "";
        %file = findNextFile( %pathMask @ "/*/materials.cs.dso" ))
   {
      // Only execute, if we don't have the source file.
      %csFileName = getSubStr( %file, 0, strlen( %file ) - 4 );
      if( !isFile( %csFileName ) )
         exec( %csFileName );
   }

   // Load all source material files.

   for( %file = findFirstFile( %pathMask @ "/*/materials.cs" );
        %file !$= "";
        %file = findNextFile( %pathMask @ "/*/materials.cs" ))
   {
      exec( %file );
   }
   
   $instantGroup = %instantGroupStor;
}

