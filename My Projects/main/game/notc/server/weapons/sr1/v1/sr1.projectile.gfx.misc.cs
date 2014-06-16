// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock ExplosionData(WpnSR1ProjectileMissedEnemyEffect)
{
	soundProfile = WpnSR1ProjectileMissedEnemySound;
};

datablock MultiNodeLaserBeamData(WpnSR1ProjectileLaserTrail0)
{
	material = "xa_notc_core_shapes_sr1_projectile_p1_lasertrail0mat";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.3;
	fadeTime = 100;
	windCoefficient = 0.0;
	//nodeDistance = 3;

   // node x movement...
   nodeMoveMode[0]     = $NodeMoveMode::None;
   nodeMoveSpeed[0]    = -0.002;
   nodeMoveSpeedAdd[0] =  0.004;
   // node y movement...
   nodeMoveMode[1]     = $NodeMoveMode::None;
   nodeMoveSpeed[1]    = -0.002;
   nodeMoveSpeedAdd[1] =  0.004;
   // node z movement...
   nodeMoveMode[2]     = $NodeMoveMode::None;
   nodeMoveSpeed[2]    = 0.5;
   nodeMoveSpeedAdd[2] = 1.0;
};

datablock MultiNodeLaserBeamData(WpnSR1ProjectileLaserTrail1)
{
	material = "xa_notc_core_shapes_sr1_projectile_p1_lasertrail1mat";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.6;
	fadeTime = 200;
	windCoefficient = 0.0;
	//nodeDistance = 3;

   // node x movement...
   nodeMoveMode[0]     = $NodeMoveMode::None;
   nodeMoveSpeed[0]    = -0.002;
   nodeMoveSpeedAdd[0] =  0.004;
   // node y movement...
   nodeMoveMode[1]     = $NodeMoveMode::None;
   nodeMoveSpeed[1]    = -0.002;
   nodeMoveSpeedAdd[1] =  0.004;
   // node z movement...
   nodeMoveMode[2]     = $NodeMoveMode::None;
   nodeMoveSpeed[2]    = 0.5;
   nodeMoveSpeedAdd[2] = 1.0;
};

datablock MultiNodeLaserBeamData(WpnSR1ProjectileLaserTrail2)
{
	material = "xa_notc_core_shapes_sr1_projectile_p1_lasertrail2mat";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 1.5;
	fadeTime = 3000;
	windCoefficient = 0.0;
	nodeDistance = 4;

   // Node x movement
   nodeMoveMode[0]     = $NodeMoveMode::ConstantSpeed;
   nodeMoveSpeed[0]    = -2.0;
   nodeMoveSpeedAdd[0] =  4.0;
   // Node y movement
   nodeMoveMode[1]     = $NodeMoveMode::ConstantSpeed;
   nodeMoveSpeed[1]    = -2.0;
   nodeMoveSpeedAdd[1] =  4.0;
   // Node z movement
   nodeMoveMode[2]     = $NodeMoveMode::ConstantSpeed;
   nodeMoveSpeed[2]    = -2.0;
   nodeMoveSpeedAdd[2] =  4.0;
};


