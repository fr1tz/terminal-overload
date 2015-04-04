
singleton TSShapeConstructor(Shape_fpDae3)
{
   baseShape = "./shape.fp.dae";
   loadLights = "0";
};

function Shape_fpDae3::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "idle", "31", "50", "1", "0");
}
