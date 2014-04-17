
singleton TSShapeConstructor(xa_notc_core_shapes_standardcat_impshield_p1_dts)
{
   baseShape = "./shape.dae";
   loadLights = "0";
};

function xa_notc_core_shapes_standardcat_impshield_p1_dts::onLoad(%this)
{
   %this.renameSequence("ambient", "level");
   %this.setSequenceCyclic("level", "0");
}

