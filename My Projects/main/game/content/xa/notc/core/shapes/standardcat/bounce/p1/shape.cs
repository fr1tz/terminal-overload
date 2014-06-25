
singleton TSShapeConstructor(xa_notc_core_shapes_standardcat_bounce_p1_dts)
{
   baseShape = "./shape.dae";
   loadLights = "0";
   lodType = "TrailingNumber";
};

function xa_notc_core_shapes_standardcat_bounce_p1_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "fire", "0", "19", "1", "0");
   %this.setSequenceCyclic("fire", "0");
}
