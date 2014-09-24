
singleton TSShapeConstructor(xa_notc_core_shapes_smg2_image_fp_p1_dts)
{
   baseShape = "./shape.dae";
   loadLights = "0";
};

function xa_notc_core_shapes_smg2_image_fp_p1_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "fire", "100", "110", "1", "0");
   %this.setSequenceCyclic("fire", "0");
   %this.addSequence("timeline", "idle", "50", "80", "1", "0");
   %this.addSequence("timeline", "reload", "130", "160", "1", "0");
   %this.setSequenceCyclic("reload", "0");
   %this.addSequence("timeline", "empty", "125", "126", "1", "0");
}
