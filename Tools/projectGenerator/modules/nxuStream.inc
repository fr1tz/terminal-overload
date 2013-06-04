<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'nxuStream' );
	
   global $PHYSX_SDK_PATH;

   // Defines
	addProjectDefines( 'WIN32' );

	// Source
	addSrcDir( $PHYSX_SDK_PATH . '/Tools/NxuStream2' );

	// Additional includes
	addIncludePath( $PHYSX_SDK_PATH . '/Tools/NxuStream2' );
	addIncludePath( $PHYSX_SDK_PATH . '/SDKs/Physics/include' );
	addIncludePath( $PHYSX_SDK_PATH . '/SDKs/Foundation/include' );
	addIncludePath( $PHYSX_SDK_PATH . '/SDKs/PhysXLoader/include' );
	addIncludePath( $PHYSX_SDK_PATH . '/SDKs/Cooking/include' );

endModule();

?>