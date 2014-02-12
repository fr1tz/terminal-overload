
singleton TSShapeConstructor(fr1tz_notc1_shapes_mgl1_image_p2_fp_dts)
{
   baseShape = "./shape.fp.dae";
   loadLights = "0";
};

function fr1tz_notc1_shapes_mgl1_image_p2_fp_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "fire", "60", "69", "1", "0");
   %this.setSequenceCyclic("fire", "0");
   %this.addSequence("timeline", "idle", "30", "60", "1", "0");
}
