
singleton TSShapeConstructor(Repelgun_tpDts)
{
   baseShape = "./repelgun.tp.dts";
};

function Repelgun_tpDts::onLoad(%this)
{
   %this.setDetailLevelSize("1024", "0");
}
