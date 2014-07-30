
new CubemapData(xa_notc_core_cubemaps_x1)
{
   cubeFace[0] = "content/xa/notc/core/cubemaps/x1/skybox_right.png";
   cubeFace[1] = "content/xa/notc/core/cubemaps/x1/skybox_left.png";
   cubeFace[2] = "content/xa/notc/core/cubemaps/x1/skybox_back.png";
   cubeFace[3] = "content/xa/notc/core/cubemaps/x1/skybox_front.png";
   cubeFace[4] = "content/xa/notc/core/cubemaps/x1/skybox_top.png";
   cubeFace[5] = "content/xa/notc/core/cubemaps/x1/skybox_top.png";
};

singleton Material(xa_notc_core_cubemaps_x1_mat)
{
   cubemap = "xa_notc_core_cubemaps_x1";
   materialTag0 = "Skies";
};

