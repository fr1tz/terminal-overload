
singleton TSShapeConstructor(ShapeDae3)
{
   baseShape = "./shape.dae";
   lodType = "TrailingNumber";
   loadLights = "0";
};

function ShapeDae3::onLoad(%this)
{
   //%this.renameSequence("ambient", "timeline");
   //%this.addSequence("timeline", "activate", "0", "12", "1", "0");
   //%this.addSequence("activate", "maintain", "0", "12", "1", "0");
}
