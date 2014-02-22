
singleton TSShapeConstructor(Sniper_fpDts)
{
   baseShape = "./sniper.fp.dts";
};

function Sniper_fpDts::onLoad(%this)
{
   %this.removeDetailLevel("1");
   %this.removeDetailLevel("50");
   %this.removeDetailLevel("10");
}
