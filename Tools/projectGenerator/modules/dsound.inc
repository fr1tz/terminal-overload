<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'dsound' );

   if ( T3D_Generator::$platform == "win32" )
   {
      addEngineSrcDir('sfx/dsound');
      addEngineSrcDir('sfx/xaudio');
      addProjectLibInput('x3daudio.lib');
   }
   else if ( T3D_Generator::$platform == "360" )
      addEngineSrcDir('sfx/xaudio');

endModule();

?>