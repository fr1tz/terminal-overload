
singleton TSShapeConstructor(Assaultrifle_tpDts)
{
   baseShape = "./assaultrifle.tp.dts";
};

function Assaultrifle_tpDts::onLoad(%this)
{
   %this.setDetailLevelSize("1024", "0");
}
