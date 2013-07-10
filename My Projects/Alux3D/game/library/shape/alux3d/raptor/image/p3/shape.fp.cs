
singleton TSShapeConstructor(Shape_Alux3D_Raptor_Image_P3_FP)
{
   baseShape = "./shape.fp.dae";
};

function Shape_Alux3D_Raptor_Image_P3_FP::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "root", "25", "35", "1", "0");
   %this.addSequence("timeline", "idle", "25", "35", "1", "0");
   %this.addSequence("timeline", "fire", "40", "50", "1", "0");
   %this.addSequence("timeline", "reload", "80", "163", "1", "0");
   %this.setSequenceCyclic("fire", "0");
}
