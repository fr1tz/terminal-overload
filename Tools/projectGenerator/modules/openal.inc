<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// OpenAL
addEngineSrcDir('sfx/openal');
addEngineSrcDir('sfx/openal/mac');
addEngineSrcDir('sfx/openal/win32');
addEngineSrcDir('sfx/openal/linux');

if ( TorqueGenerator::$platform == "win32" )
   addIncludePath( getAppLibSrcDir() . 'openal/win32' );

?>
