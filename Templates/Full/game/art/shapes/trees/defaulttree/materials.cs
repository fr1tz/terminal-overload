// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


singleton Material(defaultTree_bark_material)
{
	mapTo = "defaulttree_bark-material";

	diffuseMap[0] = "art/shapes/trees/defaulttree/defaulttree_bark_diffuse.dds";
	normalMap[0] = "art/shapes/trees/defaulttree/defaulttree_bark_normal_specular.dds";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0.9 0.9 0.9 1";
	specularPower[0] = 10;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "1";
};

singleton Material(defaulttree_material)
{
	mapTo = "defaulttree-material";

	diffuseMap[0] = "art/shapes/trees/defaulttree/defaulttree_diffuse_transparency.dds";
	normalMap[0] = "art/shapes/trees/defaulttree/defaulttree_normal_specular.dds";
	specularMap[0] = "";

	diffuseColor[0] = "1 1 1 1";
	specular[0] = "0.9 0.9 0.9 1";
	specularPower[0] = 10;

	doubleSided = false;
	translucent = false;
	translucentBlendOp = "None";
   pixelSpecular[0] = "1";
   alphaTest = "1";
   alphaRef = "127";
};

singleton Material(defaultTree_fronds_material)
{
   mapTo = "defaulttree_fronds-material";
   diffuseMap[0] = "art/shapes/trees/defaulttree/defaulttree_frond_diffuse_transparency.dds";
   normalMap[0] = "art/shapes/trees/defaulttree/defaulttree_frond_normal_specular.dds";
   specular[0] = "0.9 0.9 0.9 1";
   specularPower[0] = "10";
   pixelSpecular[0] = "1";
   translucentBlendOp = "None";
   alphaTest = "1";
   alphaRef = "114";
   translucent = "1";
};
