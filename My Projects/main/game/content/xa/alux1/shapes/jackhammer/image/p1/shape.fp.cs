// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(xa_alux1_shapes_raptor_image_p1_fp)
{
   baseShape = "./shape.fp.dae";
   loadLights = "0";
};

function xa_alux1_shapes_raptor_image_p1_fp::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "switch_in", "0", "25");
   %this.setSequenceCyclic("switch_in", "0");
   %this.addSequence("timeline", "ready", "25", "35");
   %this.addSequence("timeline", "empty", "60", "70");
   %this.addSequence("timeline", "ready_moving", "190", "230");
   %this.addSequence("timeline", "empty_moving", "260", "300");
   %this.addSequence("timeline", "fire", "350", "360");
   %this.setSequenceCyclic("fire", "0");
   
   // Reload
   %this.addSequence("timeline", "reload", "500", "583");
   %this.setSequenceCyclic("reload", "0");
   %this.addSequence("timeline", "reload_start", "500", "510");
   %this.setSequenceCyclic("reload_start", "0");
   %this.addSequence("timeline", "reload_releasemagazine", "510", "525");
   %this.setSequenceCyclic("reload_releasemagazine", "0");
   %this.addSequence("timeline", "reload_insertmagazine", "525", "550");
   %this.setSequenceCyclic("reload_insertmagazine", "0");
   %this.addSequence("timeline", "reload_chamber", "550", "583");
   %this.setSequenceCyclic("reload_chamber", "0");
}
