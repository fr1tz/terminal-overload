<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'libtheora' );

addLibSrcDir( 'libtheora/include/theora' );
addLibSrcDir( 'libtheora/lib' );
addLibSrcDir( 'libtheora/lib/dec' );

switch( T3D_Generator::$platform )
{
   case "win32":
      addLibSrcDir( 'libtheora/lib/dec/x86_vc' );
      break;
      
   default:
      addLibSrcDir( 'libtheora/lib/dec/x86' );
      break;
}

// As we don't use the encoder, disable this for now.
addLibSrcDir( 'libtheora/lib/enc' );

switch( T3D_Generator::$platform )
{
   case "win32":
      addLibSrcDir( 'libtheora/lib/enc/x86_32_vs' );
      break;
   default:
      addLibSrcDir( 'libtheora/lib/enc/x86_32' );
      break;
}

addLibIncludePath( 'libtheora/include' );
addLibIncludePath( 'libogg/include' );

endModule();
?>
