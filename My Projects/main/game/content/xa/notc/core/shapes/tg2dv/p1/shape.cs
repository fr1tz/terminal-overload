
singleton TSShapeConstructor(ShapeDae4)
{
   baseShape = "./shape.dae";
};

function ShapeDae4::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "Run", "13", "38", "1", "0");
   %this.addSequence("timeline", "Root", "0", "1", "1", "0");
   %this.addSequence("timeline", "Back", "56", "80", "1", "0");
   %this.addSequence("timeline", "Side", "101", "125", "1", "0");
}
