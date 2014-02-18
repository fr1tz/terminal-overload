
singleton TSShapeConstructor(fr1tz_notc1_shapes_standardcat_etherboard_p1_dts)
{
   baseShape = "./shape.dae";
};

function fr1tz_notc1_shapes_standardcat_etherboard_p1_dts::onLoad(%this)
{
   %this.addSequence("ambient", "deactivate", "11", "19", "1", "0");
   %this.addSequence("ambient", "activate", "24", "31", "1", "0");
   %this.setSequenceCyclic("activate", "0");
   %this.setSequenceCyclic("deactivate", "0");
}
