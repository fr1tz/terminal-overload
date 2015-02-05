
singleton TSShapeConstructor(xa_notc_core_shapes_mgl2_image_p1_fp_dts)
{
   baseShape = "./shape.fp.dae";
   loadLights = "0";
   ignoreNodeScale = "0";
};

function xa_notc_core_shapes_mgl2_image_p1_fp_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "fire", "101", "110", "1", "0");
   %this.setSequenceCyclic("fire", "0");
   %this.addSequence("timeline", "idle", "48", "83", "1", "0");
}
