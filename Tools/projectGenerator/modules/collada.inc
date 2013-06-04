<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'collada' );

	// Collada Loader
	addProjectDefine( 'TORQUE_COLLADA' );
	addProjectDefine( 'DOM_INCLUDE_TINYXML' );
	addProjectDefine( 'PCRE_STATIC' );

	addEngineSrcDir( 'ts/collada' );
	addEngineSrcDir( 'ts/loader' );

	addLibIncludePath( 'collada/include' );
	addLibIncludePath( 'collada/include/1.4' );

endModule();

?>