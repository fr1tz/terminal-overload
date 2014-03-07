
singleton TSShapeConstructor(xa_notc_core_shapes_standardcat_ballast_p1_dts)
{
   baseShape = "./shape.dae";
};

function xa_notc_core_shapes_standardcat_ballast_p1_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "level");
   %this.setSequenceCyclic("level", "0");
}

