// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock DecalData(WpnSG1ProjectileDecal)
{
   Material = "xa_notc_core_shapes_sg1_projectile_p1_decalmat";
   size = "1";
   lifeSpan = "0";
   randomize = "0";
   texRows = "1";
   texCols = "1";
   screenStartRadius = "20";
   screenEndRadius = "5";
   clippingAngle = "180";
   textureCoordCount = "0";
   textureCoords[0] = "0 0 1 1";
   textureCoords[1] = "0 0 1 1";
   textureCoords[2] = "0 0 1 1";
   textureCoords[3] = "0 0 1 1";
   textureCoords[4] = "0 0 1 1";
   textureCoords[5] = "0 0 1 1";
   textureCoords[6] = "0 0 1 1";
   textureCoords[7] = "0 0 1 1";
   textureCoords[8] = "0 0 1 1";
   textureCoords[9] = "0 0 1 1";
   textureCoords[10] = "0 0 1 1";
   fadeTime = "3000";
   paletteSlot = "0";
};

datablock MultiNodeLaserBeamData(WpnSG1ProjectileLaserTrail)
{
	material = "xa_notc_core_shapes_sg1_projectile_p1_lasertrail0mat";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 0.25;
	fadeTime = 100;
	windCoefficient = 0.0;

	// node x movement...
	nodeMoveMode[0]     = $NodeMoveMode::DynamicSpeed;
	nodeMoveSpeed[0]    = 6.0;
	nodeMoveSpeedAdd[0] = -12.0;
	// node y movement...
	nodeMoveMode[1]     = $NodeMoveMode::DynamicSpeed;
	nodeMoveSpeed[1]    = 6.0;
	nodeMoveSpeedAdd[1] = -12.0;
	// node z movement...
	nodeMoveMode[2]     = $NodeMoveMode::DynamicSpeed;
	nodeMoveSpeed[2]    = 6.0;
	nodeMoveSpeedAdd[2] = -12.0;

   nodeDistance = 5;
};


