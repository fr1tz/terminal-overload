<?php
// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

    if (!getToolBuild())
    {
        addProjectDefine( 'TORQUE_PLAYER' );
    }
    else
    {
        // 3D Tools
        addEngineSrcDir('gui/worldEditor');
        addEngineSrcDir('environment/editors');
        addEngineSrcDir('forest/editor');

        addEngineSrcDir('gui/editor');
        addEngineSrcDir('gui/editor/inspector');
    }

?>
