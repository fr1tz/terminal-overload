// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock LaserBeamData(FrmParrotSpore_LaserTail)
{
	hasLine = true;
	lineStartColor	  = "0.5 1.0 1.0 0.0";
	lineBetweenColor = "0.5 1.0 1.0 0.5";
	lineEndColor	  = "0.5 1.0 1.0 0.5";
	lineWidth		  = 1.0;

	hasInner = true;
	innerStartColor   = "0.5 1.0 1.0 0.0";
	innerBetweenColor = "0.5 1.0 1.0 0.5";
	innerEndColor     = "0.5 1.0 1.0 0.5";
	innerStartWidth   = "0.0";
	innerBetweenWidth = "0.3";
	innerEndWidth     = "0.0";

	hasOuter = false;
	outerStartColor   = "0.00 0.00 0.90 0.0";
	outerBetweenColor = "0.50 0.00 0.90 0.8";
	outerEndColor     = "1.00 1.00 1.00 0.8";
	outerStartWidth   = "0.3";
	outerBetweenWidth = "0.25";
	outerEndWidth     = "0.1";

//	bitmap = "content/rotc/p.5.3/textures/rotc/violetspark";
//	bitmapWidth = 0.10;
//	crossBitmap = "share/shapes/rotc/weapons/blaster/lasertail.red.cross";
//	crossBitmapWidth = 0.10;

	betweenFactor = 0.9;
	blendMode = 1;
};

datablock MultiNodeLaserBeamData(FrmParrotSpore_LaserTrailZero)
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

datablock OrbitProjectileData(FrmParrotSpore)
{
   orbitRadius = 6;
   orbitSpeed = 15;
   maxSpeed = 200;
   maxTrackingAbility = 5;
	laserTail = FrmParrotSpore_LaserTail;
	laserTailLen = 1;
	//laserTrail[0]   = FrmParrotSpore_LaserTrailZero;
   lifetime = 0; // 0 == forever
   //projectileShapeName = "share/shapes/alux/light.dts";
   unlimitedBounces = true;
   bounceElasticity = 0.999;
};
