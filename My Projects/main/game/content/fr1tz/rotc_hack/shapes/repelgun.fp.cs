
singleton TSShapeConstructor(Repelgun_fpDts)
{
   baseShape = "./repelgun.fp.dts";
};

function Repelgun_fpDts::onLoad(%this)
{
   %this.removeDetailLevel("50");
   %this.removeDetailLevel("10");
   %this.removeDetailLevel("2");
}
