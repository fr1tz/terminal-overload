<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'opcode' );

   // Defines
   addProjectDefine( 'TORQUE_OPCODE' );
	addProjectDefine( 'ICE_NO_DLL' );

	// Source
	addLibSrcDir( 'opcode' );
	addLibSrcDir( 'opcode/Ice' );

	// Additional includes
	addLibIncludePath( 'opcode' );

endModule();

?>