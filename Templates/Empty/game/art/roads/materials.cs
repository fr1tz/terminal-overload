// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton Material(DefaultDecalRoadMaterial)
{
   diffuseMap[0] = "art/roads/defaultRoadTextureTop.png";
   mapTo = "unmapped_mat";
   materialTag0 = "RoadAndPath";
};

singleton Material(DefaultRoadMaterialTop)
{
   mapTo = "unmapped_mat";
   diffuseMap[0] = "art/roads/defaultRoadTextureTop.png";
   materialTag0 = "RoadAndPath";
};

singleton Material(DefaultRoadMaterialOther)
{
   mapTo = "unmapped_mat";
   diffuseMap[0] = "art/roads/defaultRoadTextureOther.png";
   materialTag0 = "RoadAndPath";
};