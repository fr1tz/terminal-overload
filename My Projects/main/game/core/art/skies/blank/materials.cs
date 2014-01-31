// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton CubemapData( BlackSkyCubemap )
{
   cubeFace[0] = "./solidsky_black";
   cubeFace[1] = "./solidsky_black";
   cubeFace[2] = "./solidsky_black";
   cubeFace[3] = "./solidsky_black";
   cubeFace[4] = "./solidsky_black";
   cubeFace[5] = "./solidsky_black";
};

singleton Material( BlackSkyMat )
{
   cubemap = BlackSkyCubemap;
   materialTag0 = "Skies";
};

singleton CubemapData( BlueSkyCubemap )
{
   cubeFace[0] = "./solidsky_blue";
   cubeFace[1] = "./solidsky_blue";
   cubeFace[2] = "./solidsky_blue";
   cubeFace[3] = "./solidsky_blue";
   cubeFace[4] = "./solidsky_blue";
   cubeFace[5] = "./solidsky_blue";
};

singleton Material( BlueSkyMat )
{
   cubemap = BlueSkyCubemap;
   materialTag0 = "Skies";
};

singleton CubemapData( GreySkyCubemap )
{
   cubeFace[0] = "./solidsky_grey";
   cubeFace[1] = "./solidsky_grey";
   cubeFace[2] = "./solidsky_grey";
   cubeFace[3] = "./solidsky_grey";
   cubeFace[4] = "./solidsky_grey";
   cubeFace[5] = "./solidsky_grey";
};

singleton Material( GreySkyMat )
{
   cubemap = GreySkyCubemap;
   materialTag0 = "Skies";
};
