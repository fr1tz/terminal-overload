// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(OctahedronMat)
{
   mapTo = "green";

   diffuseMap[0] = "camera";

   translucent = "1";
   translucentBlendOp = "LerpAlpha";
   emissive = "0";
   castShadows = "0";

   colorMultiply[0] = "0 1 0 1";
};

singleton Material(SimpleConeMat)
{
   mapTo = "blue";

   diffuseMap[0] = "blue";
   translucent = "0";
   emissive = "1";
   castShadows = "0";
};

//--- camera.dts MATERIALS BEGIN ---
singleton Material(CameraMat)
{
   mapTo = "pasted__phongE1";

	diffuseMap[0] = "camera";

	diffuseColor[0] = "0 0.627451 1 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 211;
	pixelSpecular[0] = 1;
	emissive[0] = 1;

	doubleSided = 1;
	translucent = true;
	translucentBlendOp = "LerpAlpha";
   castShadows = false;
   materialTag0 = "Miscellaneous";
};

//--- camera.dts MATERIALS END ---
//--- noshape.dts MATERIALS BEGIN ---
singleton Material(noshape_NoShape)
{
   mapTo = "NoShape";

	diffuseMap[0] = "";

	diffuseColor[0] = "0.8 0.003067 0 .8";
	emissive[0] = 0;

	doubleSided = false;
	translucent = 1;
	translucentBlendOp = "LerpAlpha";
	castShadows = false;
};

//--- noshape.dts MATERIALS END ---

//--- noshapetext.dae MATERIALS BEGIN ---
singleton Material(noshapetext_lambert1)
{
   mapTo = "lambert1";

	diffuseMap[0] = "";

	diffuseColor[0] = "0.4 0.4 0.4 1";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = false;
	emissive[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
};

singleton Material(noshapetext_noshape_mat)
{
   mapTo = "noshape_mat";

	diffuseMap[0] = "";

	diffuseColor[0] = "0.4 0.3504 0.363784 0.33058";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = false;
	emissive[0] = true;

	doubleSided = false;
	translucent = true;
	translucentBlendOp = "None";
};

//--- noshapetext.dae MATERIALS END ---

//--- portal MATERIALS BEGIN ---

singleton Material(portal5_portal_top)
{
   mapTo = "portal_top";

	diffuseMap[0] = "top";
   normalMap[0]  = "top-normal";

   diffuseColor[0] = "0.4 0.4 0.4 1";
	specular[0] = "0.5 0.5 0.5 1";
	specularPower[0] = 2;
	pixelSpecular[0] = false;
	emissive[0] = true;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
};

singleton Material(portal5_portal_lightray)
{
   mapTo = "portal_lightray";

	diffuseMap[0] = "lightray";

	diffuseColor[0] = "0.4 0.4 0.4 0.64462";
	specular[0] = "0.5 0.5 0.5 1";
	specularPower[0] = 2;
	pixelSpecular[0] = false;
	emissive[0] = true;

	doubleSided = 1;
	translucent = true;
	translucentBlendOp = "AddAlpha";
   castShadows = "0";
};
//--- portal MATERIALS END ---

