// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function loadDirectory(%path, %type, %dsoType)
{
   if( %type $= "" )
      %type = "ed.cs";
   if( %dsoType $= "" )
      %dsoType = "edso"; 

   %cspath = %path @ "/*." @ %type;

   // Because in a shipping version there will be no .cs files, we can't just
   // find all the cs files and exec them.

   // First we find all the scripts and compile them if there are any
   // In the shipping version, this wont find anything.
   if( !$Scripts::ignoreDSOs )
   {
      %dsoReloc = compileDirectory(%cspath);

      // Finally we find all the dsos and exec them instead

      // If the DSOs are relocated by the engine (which will be the case when
      // running the tools) then we need to look for the scripts again.

      if(! %dsoReloc)
         %dsopath = %path @ "/*." @ %type @ "." @ %dsoType;
      else
         %dsopath = %cspath;
   }
   else
      %dsopath = %cspath;

   //error("Execing Directory " @ %dsopath @ " ...");
   %file = findFirstFile(%dsopath);

   while(%file !$= "")
   {
      //error("  Found File: " @ %file);

      // As we cant exec() a .dso directly, we need to strip that part from the filename
      %pos = strstr(%file, "." @ %dsoType);
      if(%pos != -1)
         %csfile = getSubStr(%file, 0, %pos);
      else
         %csfile = %file;

      exec(%csfile);
      %file = findNextFile(%dsopath);
   }
}

function compileDirectory(%path, %dsoPath)
{
   %saveDSOPath = $Scripts::OverrideDSOPath;
   $Scripts::OverrideDSOPath = %dsoPath;

   %dsoReloc = false;

   %file = findFirstFile(%path);

   //error("Compiling Directory " @ %path @ " ...");
   while(%file !$= "")
   {
      //error("  Found File: " @ %file @ " (" @ getDSOPath(%file) @ ")");
      if(filePath(%file) !$= filePath(getDSOPath(%file)))
         %dsoReloc = true;

      compile(%file);
      %file = findNextFile(%path);
   }

   $Scripts::OverrideDSOPath = %saveDSOPath;

   return %dsoReloc;
}

function listDirectory(%path)
{
   %file = findFirstFile(%path);

   echo("Listing Directory " @ %path @ " ...");
   while(%file !$= "")
   {
      echo("  " @ %file);
      %file = findNextFile(%path);
   }
}
