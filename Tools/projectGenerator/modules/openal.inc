<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// OpenAL
addEngineSrcDir('sfx/openal');
addEngineSrcDir('sfx/openal/mac');
addEngineSrcDir('sfx/openal/win32');

if ( T3D_Generator::$platform == "win32" )
   addIncludePath( getAppLibSrcDir() . 'openal/win32' );

?>
