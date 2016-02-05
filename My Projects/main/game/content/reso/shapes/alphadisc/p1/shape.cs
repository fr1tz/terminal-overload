
singleton TSShapeConstructor(ShapeDae2)
{
   baseShape = "./shape.dae";
};

function ShapeDae2::onLoad(%this)
{
   %this.addSequence("content/xa/notc/core/shapes/standardcat/oldanims/nm/root.dsq", "root", "0", "-1", "1", "0");
}
