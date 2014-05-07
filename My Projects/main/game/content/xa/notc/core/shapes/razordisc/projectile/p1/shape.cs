
singleton TSShapeConstructor(ShapeDae2)
{
   baseShape = "./shape.dae";
};

function ShapeDae2::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "activate", "0", "24", "1", "0");
   %this.addSequence("activate", "maintain", "0", "24", "1", "0");
}
