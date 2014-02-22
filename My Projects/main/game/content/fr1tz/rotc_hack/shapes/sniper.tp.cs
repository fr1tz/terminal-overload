
singleton TSShapeConstructor(Sniper_tpDts)
{
   baseShape = "./sniper.tp.dts";
};

function Sniper_tpDts::onLoad(%this)
{
   %this.setDetailLevelSize("1024", "0");
}
