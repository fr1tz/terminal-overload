
singleton TSShapeConstructor(xa_notc_core_shapes_sg2_projectile_p1_dts)
{
   baseShape = "./shape.dae";
   loadLights = "0";
   lodType = "TrailingNumber";
};

function xa_notc_core_shapes_sg2_projectile_p1_dts::onLoad(%this)
{
   %this.addSequence("ambient", "maintain", "0", "9", "1", "0");
   %this.addSequence("maintain", "activate", "0", "9", "1", "0");
   %this.setSequenceCyclic("activate", "0");
}
