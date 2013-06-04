// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//--- grenade.dae MATERIALS BEGIN ---
singleton Material(grenade_grenade)
{
	mapTo = "grenade";

	diffuseMap[0] = "Grenade2_Diff";
	normalMap[0] = "Grenade2_Norm";
	specularMap[0] = "Grenade2_Spec";

	diffuseColor[0] = "1 1 1 0";
	specular[0] = "1 1 1 1";
	specularPower[0] = 8;
	pixelSpecular[0] = false;
	emissive[0] = false;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
	materialTag0 = "Weapon";
};

//--- grenade.dae MATERIALS END ---


singleton Material(debri_debris)
{
   mapTo = "debris";
   diffuseColor[0] = "0.7 0.7 0.7 1";
   diffuseMap[0] = "rock_diffuse.dds";
   normalMap[0] = "rock_normals.dds";
   specular[0] = "1 1 1 0";
   specularPower[0] = "50";
   specularMap[0] = "rock_specular.dds";
   castShadows = "0";
   translucentBlendOp = "None";
   materialTag0 = "Weapon";
   materialTag0 = "FX";
};
