
singleton TSShapeConstructor(Minigun_tpDts)
{
   baseShape = "./minigun.tp.dts";
};

function Minigun_tpDts::onLoad(%this)
{
   %this.setDetailLevelSize("1024", "0");
}
