<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'bullet' );
	           
   addProjectDefine( "TORQUE_PHYSICS_BULLET" );
   addProjectDefine( "TORQUE_PHYSICS_ENABLED" );

   addEngineSrcDir( "T3D/physics/bullet" );

   includeLib( 'libbullet' );
   addLibIncludePath( "bullet/src" );

   if (inProjectConfig())
   {
      addProjectDependency( 'libbullet' );

      addSolutionProjectRef( 'libbullet' );
   }
   
endModule();

?>