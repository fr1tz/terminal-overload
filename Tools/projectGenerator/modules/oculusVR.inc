<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'oculusVR' );

   // Look for the optional global from the project.conf.
   global $OCULUSVR_SDK_PATH;
   if (!$OCULUSVR_SDK_PATH)
   {
      // First look for an environment var.
      $OCULUSVR_SDK_PATH = getenv( "TORQUE_OCULUSVR_PATH" );

      if (strlen($OCULUSVR_SDK_PATH) == 0 || !file_exists($OCULUSVR_SDK_PATH))
      {
         // Sometimes users get confused and use this var.
         $OCULUSVR_SDK_PATH = getenv( "OCULUSVR_SDK_PATH" );
      }

      // We need forward slashes for paths.
      $OCULUSVR_SDK_PATH = str_replace( "\\", "/", $OCULUSVR_SDK_PATH);

      // Remove trailing slashes.
      $OCULUSVR_SDK_PATH = rtrim($OCULUSVR_SDK_PATH, " /");
   }

   // If we still don't have the SDK path then let the user know.
   if (!file_exists($OCULUSVR_SDK_PATH))
   {
      trigger_error( 
            "\n*******************************************************************".
            "\n".
            "\n  We were not able to find a valid path to the Oculus Rift SDK!".
            "\n".
            "\n  You must install the latest Oculus VR SDK and set the path via a".
            "\n  \$OCULUSVR_SDK_PATH variable in your buildFiles/project.conf file".
            "\n  or by setting the TORQUE_OCULUSVR_PATH system environment variable".
            "\n  (may require a reboot).".
            "\n".
            "\n*******************************************************************".
            "\n", E_USER_ERROR );
   }

   // Only Windows is supported at this time
   if ( T3D_Generator::$platform == "win32" )
   {
      // Source
      addEngineSrcDir( "platform/input/oculusVR" );

      // Includes
      addIncludePath( $OCULUSVR_SDK_PATH . "/LibOVR/Include" );
      addIncludePath( $OCULUSVR_SDK_PATH . "/LibOVR/Src" );

      // Libs
      addProjectLibDir( $OCULUSVR_SDK_PATH . "/LibOVR/Lib/Win32" );
      addProjectLibInput( "libovr.lib", "libovrd.lib" );
   }

endModule();

?>
