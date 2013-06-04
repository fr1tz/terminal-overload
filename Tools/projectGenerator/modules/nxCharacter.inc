<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'nxCharacter' );
	
   global $PHYSX_SDK_PATH;

   // Defines
   addProjectDefines( 'WIN32' );
   addProjectDefines( 'NXCHARACTER_STATIC' );

   // Source
   addSrcDir( $PHYSX_SDK_PATH . '/SDKs/NxCharacter/src' );
   addSrcDir( $PHYSX_SDK_PATH . '/SDKs/NxCharacter/include' );

   // Additional includes
   addIncludePath( $PHYSX_SDK_PATH . '/SDKs/NxCharacter/include' );
   addIncludePath( $PHYSX_SDK_PATH . '/SDKs/Physics/include' );
   addIncludePath( $PHYSX_SDK_PATH . '/SDKs/Foundation/include' );
   addIncludePath( $PHYSX_SDK_PATH . '/SDKs/PhysXLoader/include' );
   addIncludePath( $PHYSX_SDK_PATH . '/SDKs/Cooking/include' );
   
endModule();

?>