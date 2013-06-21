// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(FP_BadgerDAE)
{
   baseShape = "./FP_Badger.DAE";
   loadLights = "0";
   lodType = "TrailingNumber";
};

function FP_BadgerDAE::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "Run", "230", "259", "1", "0");
   %this.addSequence("timeline", "fire", "410", "420", "1", "0");
   %this.setSequenceCyclic("fire", "0");
   %this.addSequence("timeline", "reload", "450", "518", "1", "0");
   %this.setSequenceCyclic("reload", "0");
   %this.addSequence("timeline", "switch_in", "10", "55", "1", "0");
   %this.setSequenceCyclic("switch_in", "0");
   %this.addSequence("timeline", "switch_out", "550", "565", "1", "0");
   %this.setSequenceCyclic("switch_out", "0");
   %this.addSequence("timeline", "sprint", "300", "319", "1", "0");
   %this.addSequence("timeline", "soldier_run", "230", "259", "1", "0");
   %this.addSequence("timeline", "soldier_idle", "80", "199", "1", "0");
   %this.addSequence("timeline", "soldier_fire", "410", "420", "1", "0");
   %this.setSequenceCyclic("soldier_fire", "0");
   %this.addSequence("timeline", "soldier_reload", "450", "518", "1", "0");
   %this.setSequenceCyclic("soldier_reload", "0");
   %this.addSequence("timeline", "soldier_switch_in", "10", "55", "1", "0");
   %this.setSequenceCyclic("soldier_switch_in", "0");
   %this.addSequence("timeline", "soldier_switch_out", "550", "565", "1", "0");
   %this.setSequenceCyclic("soldier_switch_out", "0");
   %this.addSequence("timeline", "soldier_sprint", "300", "319", "1", "0");
   %this.addSequence("timeline", "idle", "80", "199", "1", "0");
}
