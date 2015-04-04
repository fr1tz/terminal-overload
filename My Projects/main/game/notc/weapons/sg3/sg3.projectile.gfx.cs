// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(WpnSG3ProjectileDecal)
{
   Material = "xa_notc_core_shapes_smg2_decal_p1_mat0";
   size = "1";
   lifeSpan = "2000";
   randomize = "1";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
   textureCoordCount = "0";
   textureCoords[0] = "0 0 1 1";
   paletteSlot = 0;
   textureCoords[1] = "0.25 0 0.25 0.5";
   textureCoords[2] = "0.5 0 0.25 0.5";
   textureCoords[3] = "0.75 0 0.25 0.5";
   textureCoords[4] = "0 0.5 0.25 0.5";
   textureCoords[5] = "0.25 0.5 0.25 0.5";
   textureCoords[6] = "0.5 0.5 0.25 0.5";
   textureCoords[7] = "0.75 0.5 0.25 0.5";
};

datablock MultiNodeLaserBeamData(WpnSG3ProjectileLaserTrail0)
{
	material[0] = "xa_notc_core_shapes_sg3_trail_p1_lasertrail0mat0";
   width[0] = "0.00001";
	material[1] = "xa_notc_core_shapes_sg3_trail_p1_lasertrail0mat1";
   width[1] = "0.025";
	material[2] = "xa_notc_core_shapes_sg3_trail_p1_lasertrail0mat2";
   width[2] = "0.1";
   
	fadeTime = 150;

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
   
   //nodeDistance = 2;
};

datablock MultiNodeLaserBeamData(WpnSG3ProjectileLaserTrail1)
{
	material = "xa_notc_core_shapes_smg2_beam_p1_mat1";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.1;
	fadeTime = 75;
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

datablock MultiNodeLaserBeamData(WpnSG3ProjectileLaserTrail2)
{
	material = "xa_notc_core_shapes_smg2_beam_p1_mat2";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.6;
	fadeTime = 150;
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


