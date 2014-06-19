
singleton TSShapeConstructor(xa_notc_core_shapes_smg1_image_p2_tp_dts)
{
   baseShape = "./shape.tp.dae";
   lodType = "TrailingNumber";
   loadLights = "0";
};

function xa_notc_core_shapes_smg1_image_p2_tp_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.setSequenceCyclic("timeline", "0");
   %this.addSequence("timeline", "idle", "0", "10", "1", "0");
   %this.addSequence("timeline", "fire", "50", "60", "1", "0");
}
