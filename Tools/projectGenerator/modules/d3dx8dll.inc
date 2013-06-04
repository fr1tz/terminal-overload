<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'd3dx8dll' );

   // Source
   addLibSrcDir( 'd3dx8dll' );

   // Additional includes
   addLibIncludePath( 'd3dxdll' );    
   addLibIncludePath( 'directx8' );

   // Libs
   addProjectLibDir( 'directx8' );
   
   // Defines
   addProjectDefines( '_WINDOWS', '_USRDLL', 'D3DX8DLL_EXPORTS' );
   
endModule();

?>