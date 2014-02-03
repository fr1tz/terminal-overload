<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'lpng' );
	// Source
	addLibSrcDir( 'lpng' );

	// Additional includes
	addLibIncludePath( 'zlib' );
	addLibIncludePath( 'lpng' );
	
	// Defines
	if ( TorqueGenerator::$platform == "360" )
      addProjectDefines( 'PNG_NO_ASSEMBLER_CODE' );
	
endModule();
?>