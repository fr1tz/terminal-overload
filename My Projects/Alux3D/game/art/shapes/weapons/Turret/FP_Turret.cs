// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(FP_TurretDAE)
{
   baseShape = "./FP_Turret.DAE";
   neverImport = "EnvironmentAmbientLight	null";
   loadLights = "0";
   lodType = "TrailingNumber";
};

function FP_TurretDAE::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "root", "120", "121", "1", "0");
   %this.addSequence("timeline", "Run", "160", "189", "1", "0");
   %this.addSequence("timeline", "sprint", "160", "189", "1", "0");
   %this.addSequence("timeline", "idle", "70", "129", "1", "0");
   %this.addSequence("timeline", "fire", "230", "250", "1", "0");
   %this.setSequenceCyclic("fire", "0");
   %this.addSequence("timeline", "reload", "52", "53", "1", "0");
   %this.setSequenceCyclic("reload", "0");
   %this.addSequence("timeline", "switch_out", "280", "295", "1", "0");
   %this.setSequenceCyclic("switch_out", "0");
   %this.addSequence("timeline", "switch_in", "10", "30", "1", "0");
   %this.setSequenceCyclic("switch_in", "0");
   %this.addSequence("timeline", "soldier_sprint", "160", "189", "1", "0");
   %this.addSequence("timeline", "soldier_reload", "52", "53", "1", "0");
   %this.setSequenceCyclic("soldier_reload", "0");
   %this.addSequence("timeline", "soldier_run", "160", "189", "1", "0");
   %this.addSequence("timeline", "soldier_idle", "70", "129", "1", "0");
   %this.addSequence("timeline", "soldier_fire", "230", "250", "1", "0");
   %this.setSequenceCyclic("soldier_fire", "0");
   %this.addSequence("timeline", "soldier_switch_out", "280", "295", "1", "0");
   %this.setSequenceCyclic("soldier_switch_out", "0");
   %this.addSequence("timeline", "soldier_switch_in", "10", "30", "1", "0");
   %this.setSequenceCyclic("soldier_switch_in", "0");
}
