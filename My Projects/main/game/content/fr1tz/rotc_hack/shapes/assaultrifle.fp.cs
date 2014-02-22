
singleton TSShapeConstructor(Assaultrifle_fpDts)
{
   baseShape = "./assaultrifle.fp.dts";
};

function Assaultrifle_fpDts::onLoad(%this)
{
   %this.removeDetailLevel("50");
   %this.removeDetailLevel("10");
   %this.removeDetailLevel("1");
}
