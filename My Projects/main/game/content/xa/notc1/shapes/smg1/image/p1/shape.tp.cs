
singleton TSShapeConstructor(xa_notc1_shapes_smg1_image_p1_tp_dts)
{
   baseShape = "./shape.tp.dae";
};

function xa_notc1_shapes_smg1_image_p1_tp_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "idle", "0", "10", "1", "0");
   %this.addSequence("timeline", "fire", "100", "110", "1", "0");
   %this.setSequenceCyclic("fire", "0");
}

