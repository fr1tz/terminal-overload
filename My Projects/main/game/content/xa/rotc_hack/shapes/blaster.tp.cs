
singleton TSShapeConstructor(Blaster_tpDts)
{
   baseShape = "./blaster.tp.dts";
};

function Blaster_tpDts::onLoad(%this)
{
   %this.setDetailLevelSize("1024", "0");
}
