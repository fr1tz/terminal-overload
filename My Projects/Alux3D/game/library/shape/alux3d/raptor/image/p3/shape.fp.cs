
singleton TSShapeConstructor(Shape_Alux3D_Raptor_Image_P3_FP)
{
   baseShape = "./shape.fp.dae";
};

function Shape_Alux3D_Raptor_Image_P3_FP::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "root", "25", "35", "1", "0");
   %this.addSequence("timeline", "ready", "25", "35", "1", "0");
   %this.addSequence("timeline", "empty", "60", "70", "1", "0");
   %this.addSequence("timeline", "ready_moving", "190", "230", "1", "0");
   %this.addSequence("timeline", "empty_moving", "260", "300", "1", "0");
   %this.addSequence("timeline", "fire", "350", "360", "1", "0");
   %this.addSequence("timeline", "reload", "500", "583", "1", "0");
   %this.setSequenceCyclic("fire", "0");
}
