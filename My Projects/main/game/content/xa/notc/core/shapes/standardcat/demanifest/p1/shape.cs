
singleton TSShapeConstructor(xa_notc_core_shapes_standardcat_demanifest_p1_dts)
{
   baseShape = "./shape.dae";
   loadLights = "0";
};


function xa_notc_core_shapes_standardcat_demanifest_p1_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "ambient", "0", "18", "1", "0");
   %this.setSequenceCyclic("ambient", "0");
}
