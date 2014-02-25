// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(xa_alux1_shapes_raptor_image_p1_mat1)
{
   mapTo = "xa_alux1_shapes_raptor_image_p1_mat1";
   diffuseColor[0] = "0.996078 0.996078 0.996078 1";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "50";
   doubleSided = "1";
   translucentBlendOp = "None";
   diffuseMap[0] = "content/xa/alux1/textures/placeholder.png";
};

singleton Material(xa_alux1_shapes_raptor_image_p1_mat2)
{
   mapTo = "xa_alux1_shapes_raptor_image_p1_mat2";
   diffuseColor[0] = "0.0416922 0.607387 0.64 1";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "50";
   doubleSided = "0";
   translucentBlendOp = "AddAlpha";
   diffuseMap[0] = "content/xa/alux1/shapes/raptor/image/p1/muzzleflash.png";
   glow[0] = "1";
   emissive[0] = "1";
   castShadows = "0";
   translucent = "1";
   showFootprints = "0";
};

singleton Material(shape_fp_xa_alux1_shapes_raptor_image_p1_mat2)
{
   mapTo = "xa_alux1_shapes_raptor_image_p1_mat2";
   diffuseColor[0] = "0.0416922 0.607387 0.64 1";
   diffuseMap[0] = "content/xa/alux1/shapes/raptor/image/p1/muzzleflash.png";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "50";
   glow[0] = "1";
   emissive[0] = "1";
   doubleSided = "1";
   castShadows = "0";
   translucent = "1";
   translucentBlendOp = "AddAlpha";
   showFootprints = "0";
};
