// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function requiredContent_getFileExt(%file)
{
   %ext = strrchr(%file, ".");
   if(strchr(%ext, "/") !$= "")
      return "";
   return %ext;
}

function requiredContent_init()
{
   if(isObject($Server::RequiredContent))
      $Server::RequiredContent.delete();
   $Server::RequiredContent = new ArrayObject();
}

function requiredContent_addFile(%file)
{
   //echo("requiredContent_addFile():" SPC %file);
   if(isDirectory(%file))
      return;
   if(!isFile(%file))
   {
      if(requiredContent_getFileExt(%file) $= "")
         requiredContent_addFromPattern(%file @ ".*");
      return;
   }
   if($Server::RequiredContent.getIndexFromKey(%file) >= 0)
      return;
   %crc = getFileCRC(%file);
   if(%crc != 0 && %crc != -1)
   {
      //echo("Required content:" SPC %file SPC "("@%crc@")");
      $Server::RequiredContent.push_back(%file, %crc SPC fileSize(%file));
   }
}

function requiredContent_addFromDataBlocks()
{
   %c = DataBlockGroup.getCount();
   for(%i = 0; %i < %c; %i++)
   {
      %datablock = DataBlockGroup.getObject(%i);
      //echo(%datablock SPC %datablock.getClassName());
      if(%datablock.textureName !$= "")
         requiredContent_addFile(%datablock.textureName);
      if(%datablock.filename !$= "")
         requiredContent_addFile(%datablock.filename);
      if(%datablock.shapeFile !$= "")
         requiredContent_addFile(%datablock.shapeFile);
      if(%datablock.projectileShapeName !$= "")
         requiredContent_addFile(%datablock.projectileShapeName);
      if(%datablock.explosionShape !$= "")
         requiredContent_addFile(%datablock.explosionShape);
   }
}

function requiredContent_addFromMaterials()
{
   %c = ServerMaterialsGroup.getCount();
   for(%i = 0; %i < %c; %i++)
   {
      %mat = ServerMaterialsGroup.getObject(%i);
      for(%layer = 0; %layer < 4; %layer++)
      {
         if(%mat.baseTex[%layer] !$= "")
            requiredContent_addFile(%mat.baseTex[%layer]);
         if(%mat.bumpTex[%layer] !$= "")
            requiredContent_addFile(%mat.bumpTex[%layer]);
         if(%mat.detailMap[%layer] !$= "")
            requiredContent_addFile(%mat.detailMap[%layer]);
         if(%mat.detailNormalMap[%layer] !$= "")
            requiredContent_addFile(%mat.detailNormalMap[%layer]);
         if(%mat.detailTex[%layer] !$= "")
            requiredContent_addFile(%mat.detailTex[%layer]);
         if(%mat.diffuseMap[%layer] !$= "")
            requiredContent_addFile(%mat.diffuseMap[%layer]);
         if(%mat.envMap[%layer] !$= "")
            requiredContent_addFile(%mat.envMap[%layer]);
         if(%mat.envTex[%layer] !$= "")
            requiredContent_addFile(%mat.envTex[%layer]);
         if(%mat.lightMap[%layer] !$= "")
            requiredContent_addFile(%mat.lightMap[%layer]);
         if(%mat.normalMap[%layer] !$= "")
            requiredContent_addFile(%mat.normalMap[%layer]);
         if(%mat.overlayMap[%layer] !$= "")
            requiredContent_addFile(%mat.overlayMap[%layer]);
         if(%mat.overlayTex[%layer] !$= "")
            requiredContent_addFile(%mat.overlayTex[%layer]);
         if(%mat.specularMap[%layer] !$= "")
            requiredContent_addFile(%mat.specularMap[%layer]);
         if(%mat.toneMap[%layer] !$= "")
            requiredContent_addFile(%mat.toneMap[%layer]);
      }
   }
}

function requiredContent_addFromPattern(%pattern)
{
   //echo("requiredContent_addFromPattern():" SPC %pattern);
   %file = findFirstFile(%pattern);
   while(%file !$= "")
   {
      requiredContent_addFile(%file);
      %file = findNextFile(%pattern);
   }
}

function requiredContent_filter()
{
   %filterExt = ".xcf .blend .blend1 .mmpz .svg";
   %n = $Server::RequiredContent.count();
   for(%i = %n-1; %i >= 0; %i--)
   {
      %file = $Server::RequiredContent.getKey(%i);
      %ext = requiredContent_getFileExt(%file);
      if(strstr(%filterExt, %ext) >= 0)
      {
         //echo(%file SPC "("@%ext@")");
         $Server::RequiredContent.erase(%i);
      }
   }
}

function requiredContent_print()
{
   %s = $Server::RequiredContent.count();
   for(%i = 0; %i < %s; %i++)
   {
      %file = $Server::RequiredContent.getKey(%i);
      %val = $Server::RequiredContent.getValue(%i);
      %crc = getWord(%val, 0);
      %size = getWord(%val, 1);
      echo(%file SPC "("@%crc@")");
   }
}

