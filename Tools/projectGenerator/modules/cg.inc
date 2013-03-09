<?php
//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

beginModule( 'cg' );

   // Look for the optional global from the project.conf.
   global $CG_SDK_PATH;
   if (!$CG_SDK_PATH)
   {
      // First look for an environment var.
      $CG_SDK_PATH = getenv( "TORQUE_CG_PATH" );

      if (strlen($CG_SDK_PATH) == 0 || !file_exists($CG_SDK_PATH))
      {
         // Sometimes users get confused and use this var.
         $CG_SDK_PATH = getenv( "CG_SDK_PATH" );

         if (strlen($CG_SDK_PATH) == 0 || !file_exists($CG_SDK_PATH))
         {
            // Since neither environment var worked try for the default CG SDK install location.
            $CG_SDK_PATH = getenv("ProgramFiles") . "/NVIDIA Corporation/Cg";

            // try the x86 default install path.
            if (!file_exists($CG_SDK_PATH))
               $CG_SDK_PATH = getenv("ProgramFiles(x86)") . "/NVIDIA Corporation/Cg";
              
            // try the default linux install path
            if (!file_exists($CG_SDK_PATH))
            {
                if( file_exists("/usr/include/Cg/cg.h") )
                  $CG_SDK_PATH = "/usr/";
            }
         }
      }

      // We need forward slashes for paths.
      $CG_SDK_PATH = str_replace( "\\", "/", $CG_SDK_PATH);

      // Remove trailing slashes.
      $CG_SDK_PATH = rtrim($CG_SDK_PATH, " /");
   }

   // If we still don't have the SDK path then let the user know.
   if (!file_exists($CG_SDK_PATH))
   {
      trigger_error( 
            "\n*******************************************************************".
            "\n".
            "\n  We were not able to find a valid path to the Cg SDK!".
            "\n".
            "\n  You must install the latest Cg SDK and set the path via a".
            "\n  \$CG_SDK_PATH variable in your buildFiles/project.conf file".
            "\n  or by setting the TORQUE_CG_PATH system environment variable".
            "\n  (may require a reboot).".
            "\n".
            "\n*******************************************************************".
            "\n", E_USER_ERROR );
   }

   // Includes
   addIncludePath( $CG_SDK_PATH . "/include/Cg" );
   addIncludePath( $CG_SDK_PATH . "/include" );

   // Libs
   addProjectLibDir( $CG_SDK_PATH . "/lib" );
   switch( Generator::$platform )
   {
      case "360":         
      case "win32":
         addProjectLibInput( "cg.lib" );
         addProjectLibInput( "cgD3D9.lib" );
         addProjectLibInput( "cgGL.lib" );
         break;
   
      case "ps3":         
      case "mac":
      case "linux":
      case "linux_dedicated":
         addProjectLibInput( "Cg" );
         addProjectLibInput( "CgGL" );
         break;
   }

endModule();

?>
