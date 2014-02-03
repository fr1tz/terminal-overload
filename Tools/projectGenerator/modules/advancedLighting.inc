<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'advancedLighting' );

    addProjectDefine( 'TORQUE_ADVANCED_LIGHTING' );

	addEngineSrcDir( 'lighting/advanced' );
	addEngineSrcDir( 'lighting/shadowMap' );

   switch( TorqueGenerator::$platform )
   {
      case "win32":
         addEngineSrcDir( 'lighting/advanced/hlsl' );
		 addEngineSrcDir( 'lighting/advanced/glsl' );
         break;
      case "360":
         addEngineSrcDir( 'lighting/advanced/hlsl' );
         break;
      case "mac":
      case "linux":
      case "linux_dedicated":
         addEngineSrcDir( 'lighting/advanced/glsl' );
         break;
   }

endModule();

?>