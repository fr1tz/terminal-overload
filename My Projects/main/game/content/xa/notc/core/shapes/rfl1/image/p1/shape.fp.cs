
singleton TSShapeConstructor(Shape_fpDae2)
{
   baseShape = "./shape.fp.dae";
   loadLights = "0";
};

function Shape_fpDae2::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "idle", "30", "50", "1", "0");
   %this.addSequence("timeline", "fire", "62", "69", "1", "0");
   %this.setSequenceCyclic("fire", "0");
}
