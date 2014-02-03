<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'ljpeg' );	

// Source
addLibSrcDir( 'ljpeg' );

// Additional includes
addLibIncludePath( 'ljpeg' );

// Defines
	if ( TorqueGenerator::$platform == "360" )
      addProjectDefines( 'NO_GETENV;' );

endModule();
?>