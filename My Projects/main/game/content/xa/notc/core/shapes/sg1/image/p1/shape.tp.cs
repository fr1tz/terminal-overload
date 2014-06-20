
singleton TSShapeConstructor(xa_notc_core_shapes_sg1_image_p1_tp_dts)
{
   baseShape = "./shape.tp.dae";
   lodType = "TrailingNumber";
   loadLights = "0";
};

function xa_notc_core_shapes_sg1_image_p1_tp_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.setSequenceCyclic("timeline", "0");
   %this.addSequence("timeline", "idle", "0", "10", "1", "0");
   %this.addSequence("timeline", "reload", "50", "60", "1", "0");
   %this.addSequence("timeline", "empty", "40", "45", "1", "0");
   %this.setSequenceCyclic("empty", "1");
   %this.setSequenceCyclic("idle", "1");
   %this.addSequence("timeline", "fire", "30", "40", "1", "0");
}
