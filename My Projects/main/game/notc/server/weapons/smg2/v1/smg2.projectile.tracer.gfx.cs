// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock MultiNodeLaserBeamData(WpnSMG2ProjectileTracerLaserTrail0)
{
	material = "xa_notc_core_shapes_smg2_tracer_p1_lasertrail0mat";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.10;
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

