
singleton TSShapeConstructor(xa_notc_core_shapes_smg1_image_p1_fp_dts)
{
   baseShape = "./shape.fp.dae";
   loadLights = "0";
};

function xa_notc_core_shapes_smg1_image_p1_fp_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "idle", "30", "50", "1", "0");
   %this.addSequence("timeline", "fire", "61", "69", "1", "0");
   %this.setSequenceCyclic("fire", "0");
}
