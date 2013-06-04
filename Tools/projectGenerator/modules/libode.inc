<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'libode' );
	
  // Source
  addLibSrcDir( 'ode' );

  // Additional includes
  addLibIncludePath( 'opcode' );
  addLibIncludePath( 'ode' );
  addLibIncludePath( '' );

endModule();

?>