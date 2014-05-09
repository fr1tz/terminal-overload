
singleton TSShapeConstructor(xa_notc_core_shapes_repeldisc_projectile_p1_dts)
{
   baseShape = "./shape.dae";
};

function xa_notc_core_shapes_repeldisc_projectile_p1_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "activate", "0", "24", "1", "0");
   %this.addSequence("activate", "maintain", "0", "24", "1", "0");
}
