// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'testing' );

   addProjectDefine( 'TORQUE_TESTS_ENABLED' );
   addProjectDefine( '_VARIADIC_MAX', 10 );
   addSrcDir(getEngineSrcDir() . 'testing', true);

   addLibIncludePath( 'gtest/fused-src/' );

endModule();

?>
