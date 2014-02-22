
singleton TSShapeConstructor(Blaster_fpDts)
{
   baseShape = "./blaster.fp.dts";
};

function Blaster_fpDts::onLoad(%this)
{
   %this.removeDetailLevel("2");
   %this.removeDetailLevel("10");
   %this.removeDetailLevel("50");
}
