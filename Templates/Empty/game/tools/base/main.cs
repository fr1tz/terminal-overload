// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function initializeBase()
{
   echo(" % - Initializing Base Editor");
   
   // Load Custom Editors
   loadDirectory( expandFilename( "./canvas" ) );
   loadDirectory( expandFilename( "./menuBar" ) );
   loadDirectory( expandFilename( "./utils" ) );
}

function destroyBase()
{
}
