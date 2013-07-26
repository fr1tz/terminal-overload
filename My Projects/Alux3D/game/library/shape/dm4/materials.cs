


singleton Material(beam_shape_dm4_beam_mat1)
{
   mapTo = "shape_dm4_beam_mat1";
   diffuseColor[0] = "0.00801464 0.64 0.055923 1";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "50";
   doubleSided = "0";
   translucentBlendOp = "AddAlpha";
   glow[0] = "1";
   emissive[0] = "1";
   castShadows = "0";
   translucent = "1";
};

singleton Material(beamstruct_shape_dm4_metal1)
{
   mapTo = "shape_dm4_metal1";
   diffuseColor[0] = "0.64 0.64 0.64 1";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "50";
   doubleSided = "1";
   translucentBlendOp = "None";
};

singleton Material(beamstruct_shape_dm4_metal1_001)
{
   mapTo = "shape_dm4_metal1_001";
   diffuseColor[0] = "0.403922 0.403922 0.403922 1";
   specular[0] = "0.5 0.5 0.5 1";
   specularPower[0] = "6";
   doubleSided = "1";
   translucentBlendOp = "None";
   glow[0] = "0";
   emissive[0] = "0";
   pixelSpecular[0] = "1";
   materialTag0 = "Miscellaneous";
   detailScale[0] = "8 8";
   footstepSoundId = "2";
};
