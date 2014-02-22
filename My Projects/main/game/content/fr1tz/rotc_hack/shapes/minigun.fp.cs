
singleton TSShapeConstructor(Minigun_fpDts)
{
   baseShape = "./minigun.fp.dts";
};

function Minigun_fpDts::onLoad(%this)
{
   %this.removeDetailLevel("50");
   %this.removeDetailLevel("10");
   %this.removeDetailLevel("1");
}
