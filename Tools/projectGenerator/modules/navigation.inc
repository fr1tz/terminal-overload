<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'navigation' );

   addProjectDefine( 'TORQUE_NAVIGATION_ENABLED' );
   addSrcDir(getEngineSrcDir() . 'navigation', true);

   includeLib( 'librecast' );
   addLibIncludePath( 'recast/DebugUtils/Include' );
   addLibIncludePath( 'recast/Recast/Include' );
   addLibIncludePath( 'recast/Detour/Include' );
   addLibIncludePath( 'recast/DetourTileCache/Include' );
   addLibIncludePath( 'recast/DetourCrowd/Include' );

   if (inProjectConfig())
   {
      addProjectDependency( 'librecast' );
      addSolutionProjectRef( 'librecast' );
   }

endModule();

?>
