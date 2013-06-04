<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

beginModule( 'basicLighting' );

   addProjectDefine( 'TORQUE_BASIC_LIGHTING' );

   addEngineSrcDir( 'lighting/basic' );
   addEngineSrcDir( 'lighting/shadowMap' );

endModule();

?>