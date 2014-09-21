
singleton TSShapeConstructor(xa_notc_core_shapes_mgl1_projectile_p2_dts)
{
   baseShape = "./shape.dae";
   loadLights = "0";
   lodType = "TrailingNumber";
};

function xa_notc_core_shapes_mgl1_projectile_p2_dts::onLoad(%this)
{
   %this.addSequence("ambient", "maintain", "0", "9", "1", "0");
   %this.addSequence("maintain", "activate", "0", "8", "1", "0");
}
