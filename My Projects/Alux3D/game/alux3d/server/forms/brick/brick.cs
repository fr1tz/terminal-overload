// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock StaticShapeData(BrickVolumeCollisionShape)
{
   shapeFile = "content/fr1tz/alux1/shapes/brick/brick-team1.dae";
};

datablock HexagonVolumeData(BrickVolume)
{
   renderShapeFile[0] = "content/fr1tz/alux1/shapes/brick/brick.dae";
   renderShapeFile[1] = "content/fr1tz/alux1/shapes/brick/brick-team1.dae";
   renderShapeFile[2] = "content/fr1tz/alux1/shapes/brick/brick-team2.dae";
   collisionShape[0] = BrickVolumeCollisionShape;
   collisionShape[1] = BrickVolumeCollisionShape;
   collisionShape[2] = BrickVolumeCollisionShape;
   mode = 2;
};
