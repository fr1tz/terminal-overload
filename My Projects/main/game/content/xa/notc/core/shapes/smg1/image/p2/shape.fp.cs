
singleton TSShapeConstructor(xa_notc_core_shapes_smg1_image_p2_fp_dts)
{
   baseShape = "./shape.fp.dae";
   loadLights = "0";
};

function xa_notc_core_shapes_smg1_image_p2_fp_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "fire", "100", "110", "1", "0");
   %this.setSequenceCyclic("fire", "0");
   %this.addSequence("timeline", "idle", "50", "80", "1", "0");
}
