// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LaserBeamData(FrmSoldierSpore_LaserTail)
{
	hasLine = true;
	lineStartColor	  = "1.0 0.5 0.5 0.0";
	lineBetweenColor = "1.0 0.5 0.5 0.5";
	lineEndColor	  = "1.0 0.5 0.5 0.5";
	lineWidth		  = 4.0;

	hasInner = true;
	innerStartColor   = "1.0 0.5 0.5 0.0";
	innerBetweenColor = "1.0 0.5 0.5 0.5";
	innerEndColor     = "1.0 0.5 0.5 0.5";
	innerStartWidth   = "0.0";
	innerBetweenWidth = "0.6";
	innerEndWidth     = "0.0";

	hasOuter = false;
	outerStartColor   = "0.00 0.00 0.90 0.0";
	outerBetweenColor = "0.50 0.00 0.90 0.8";
	outerEndColor     = "1.00 1.00 1.00 0.8";
	outerStartWidth   = "0.3";
	outerBetweenWidth = "0.25";
	outerEndWidth     = "0.1";

//	bitmap = "content/xa/rotc/p.5.4/textures/rotc/violetspark";
//	bitmapWidth = 0.10;
//	crossBitmap = "share/shapes/rotc/weapons/blaster/lasertail.red.cross";
//	crossBitmapWidth = 0.10;

	betweenFactor = 0.8;
	blendMode = 1;
};

datablock MultiNodeLaserBeamData(FrmSoldierSpore_LaserTrailZero)
{
	hasLine = true;
	lineColor	= "1.0 0.0 0.0 0.5";

	hasInner = true;
	innerColor = "1.0 0.0 0.0 0.5";
	innerWidth = "0.1";

	hasOuter = false;
	outerColor = "1.00 0.00 1.00 0.1";
	outerWidth = "0.10";

	//bitmap = "share/shapes/rotc/vehicles/team1scoutflyer/lasertrail";
	//bitmapWidth = 1;

	blendMode = 1;
	fadeTime = 200;
};

datablock OrbitProjectileData(FrmSoldierSpore)
{
   orbitRadius = 7;
   orbitSpeed = 15;
   maxSpeed = 200;
   maxTrackingAbility = 4;
	laserTail = FrmSoldierSpore_LaserTail;
	laserTailLen = 2.0;
	//laserTrail[0] = FrmSoldierSpore_LaserTrailZero;
   lifetime = 0; // 0 == forever
   //projectileShapeName = "share/shapes/alux/light.dts";
   unlimitedBounces = true;
   bounceElasticity = 0.999;
};
