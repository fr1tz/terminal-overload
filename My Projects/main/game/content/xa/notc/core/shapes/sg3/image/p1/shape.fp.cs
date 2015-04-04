
singleton TSShapeConstructor(Shape_fpDae)
{
   baseShape = "./shape.fp.dae";
};

function Shape_fpDae::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "idle", "30", "50", "1", "0");
   %this.addSequence("timeline", "fire", "63", "69", "1", "0");
   %this.setSequenceCyclic("fire", "0");
}
