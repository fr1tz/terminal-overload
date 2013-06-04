<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'lmng' );
	// Source files
	addLibSrcDir( 'lmng' );

	// Additional includes
	addLibIncludePath( 'lmng' );
	addLibIncludePath( 'lpng' );
	addLibIncludePath( 'zlib' );
	addLibIncludePath( 'ljpeg' );
endModule();

?>