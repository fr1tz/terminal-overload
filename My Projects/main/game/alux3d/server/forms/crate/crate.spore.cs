// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LaserBeamData(FrmCrateSpore_LaserTail)
{
	hasLine = true;
	lineStartColor	= "1.00 0.75 0.50 0.0";
	lineBetweenColor = "1.00 0.75 0.50 1.0";
	lineEndColor	  = "1.00 0.75 0.50 1.0";
	lineWidth		  = 1.0;

	hasInner = true;
	innerStartColor = "1.00 0.75 0.50 0.0";
	innerBetweenColor = "1.00 0.75 0.50 1.0";
	innerEndColor = "1.00 0.75 0.50 1.0";
	innerStartWidth = "0.00";
	innerBetweenWidth = "0.10";
	innerEndWidth = "0.00";

	hasOuter = false;
	outerStartColor = "0.00 0.00 0.90 0.0";
	outerBetweenColor = "0.50 0.00 0.90 0.8";
	outerEndColor = "1.00 1.00 1.00 0.8";
	outerStartWidth = "0.3";
	outerBetweenWidth = "0.25";
	outerEndWidth = "0.1";

//	bitmap = "content/xa/rotc/p.5.3/textures/rotc/violetspark";
//	bitmapWidth = 0.10;
//	crossBitmap = "share/shapes/rotc/weapons/blaster/lasertail.red.cross";
//	crossBitmapWidth = 0.10;

	betweenFactor = 0.9;
	blendMode = 1;
};

datablock MultiNodeLaserBeamData(FrmCrateSpore_LaserTrailZero)
{
	hasLine = true;
	lineColor	= "0.5 1.0 0.5 0.7";

	hasInner = true;
	innerColor = "0.5 1.0 0.5 0.7";
	innerWidth = "0.1";

	hasOuter = false;
	outerColor = "1.00 0.00 1.00 0.1";
	outerWidth = "0.10";

	//bitmap = "share/shapes/rotc/vehicles/team1scoutflyer/lasertrail";
	//bitmapWidth = 1;

	blendMode = 1;
	fadeTime = 200;
};

datablock OrbitProjectileData(FrmCrateSpore)
{
   orbitRadius = 5;
   orbitSpeed = 15;
   maxSpeed = 200;
   maxTrackingAbility = 6;
	laserTail = FrmCrateSpore_LaserTail;
	laserTailLen = 0.5;
	//laserTrail[0]   = FrmCrateSpore_LaserTrailZero;
   lifetime = 0; // 0 == forever
   //projectileShapeName = "share/shapes/alux/light.dts";
   unlimitedBounces = true;
   bounceElasticity = 0.999;
};
