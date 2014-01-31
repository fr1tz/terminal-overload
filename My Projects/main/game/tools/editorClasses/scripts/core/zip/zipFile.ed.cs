// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function ZipObject::addPath( %this, %path, %pathInZip )
{
   %beginPath = expandFilename( %path );
   %path = pathConcat(%path, "*");
   %file = findFirstFile( %path );

   while(%file !$= "")
   {
      %zipRel = makeRelativePath( %file, %beginPath );
      %finalZip = pathConcat(%pathInZip, %zipRel);
      
      %this.addFile( %file, %finalZip );

      %file = findNextFile(%path);
   }   
}