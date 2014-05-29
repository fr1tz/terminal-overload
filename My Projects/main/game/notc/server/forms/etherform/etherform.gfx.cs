// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LightFlareData(FrmEtherformLightFlare)
{
   losMask = $TypeMasks::TerrainObjectType |
             $TypeMasks::StaticShapeObjectType |
             $TypeMasks::PlayerObjectType |
             $TypeMasks::TurretObjectType |
             $TypeMasks::VehicleObjectType;

   overallScale = "1";
   flareEnabled = true;
   renderReflectPass = true;
   flareTexture = "content/xa/torque3d/3.0/lights/lensFlareSheet1.png";

   elementRect[0] = "512 512 512 512";
   elementDist[0] = 0.0;
   elementScale[0] = 0.5;
   elementTint[0] = "1.0 1.0 1.0";
   elementRotate[0] = true;
   elementUseLightColor[0] = true;

   elementRect[1] = "512 0 512 512";
   elementDist[1] = 0.0;
   elementScale[1] = 2.0;
   elementTint[1] = "0.698039 0.698039 0.698039 1";
   elementRotate[1] = true;
   elementUseLightColor[1] = true;

   elementRect[2] = "1152 0 128 128";
   elementDist[2] = 0.3;
   elementScale[2] = 0.5;
   elementTint[2] = "1.0 1.0 1.0";
   elementRotate[2] = true;
   elementUseLightColor[2] = true;

   elementRect[3] = "1024 0 128 128";
   elementDist[3] = 0.5;
   elementScale[3] = 0.25;
   elementTint[3] = "1.0 1.0 1.0";
   elementRotate[3] = true;
   elementUseLightColor[3] = true;

   elementRect[4] = "1024 128 128 128";
   elementDist[4] = 0.8;
   elementScale[4] = 0.6;
   elementTint[4] = "1.0 1.0 1.0";
   elementRotate[4] = true;
   elementUseLightColor[4] = true;

   elementRect[5] = "1024 0 128 128";
   elementDist[5] = 1.18;
   elementScale[5] = 0.5;
   elementTint[5] = "0.698039 0.698039 0.698039 1";
   elementRotate[5] = true;
   elementUseLightColor[5] = true;

   elementRect[6] = "1152 128 128 128";
   elementDist[6] = 1.25;
   elementScale[6] = 0.35;
   elementTint[6] = "0.8 0.8 0.8";
   elementRotate[6] = true;
   elementUseLightColor[6] = true;

   elementRect[7] = "1024 0 128 128";
   elementDist[7] = 2.0;
   elementScale[7] = 0.25;
   elementTint[7] = "1.0 1.0 1.0";
   elementRotate[7] = true;
   elementUseLightColor[7] = true;
};

datablock MultiNodeLaserBeamData(FrmEtherformLaserTrail0)
{
	material = "xa_notc_core_shapes_etherform_p2_lasertrail0mat";
	renderMode = $MultiNodeLaserBeamRenderMode::FaceViewer;
   width = 1.0;
	fadeTime = 1000;
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

