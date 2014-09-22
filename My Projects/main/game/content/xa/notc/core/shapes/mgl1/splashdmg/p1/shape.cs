
singleton TSShapeConstructor(ShapeDae)
{
   baseShape = "./shape.dae";
   loadLights = "0";
};

function ShapeDae::onLoad(%this)
{
   %this.setSequenceCyclic("ambient", "0");
}
