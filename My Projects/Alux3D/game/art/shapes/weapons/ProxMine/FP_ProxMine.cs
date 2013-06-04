// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton TSShapeConstructor(FP_ProxMineDAE)
{
   baseShape = "./FP_ProxMine.DAE";
   loadLights = "0";
};

function FP_ProxMineDAE::onLoad(%this)
{
   %this.renameSequence("ambient", "timeline");
   %this.addSequence("timeline", "idle", "146", "205", "1", "0");
   %this.addSequence("timeline", "Run", "236", "295", "1", "0");
   %this.addSequence("timeline", "run2sprint", "326", "341", "1", "0");
   %this.addSequence("timeline", "sprint", "376", "395", "1", "0");
   %this.addSequence("timeline", "sprint2run", "426", "441", "1", "0");
   %this.addSequence("timeline", "fire", "476", "500", "1", "0");
   %this.addSequence("timeline", "switch_out", "546", "561", "1", "0");
   %this.addSequence("timeline", "switch_in", "10", "98", "1", "0");
   %this.setSequenceCyclic("switch_in", "0");
   %this.addSequence("timeline", "fire_release", "500", "521", "1", "0");
   %this.setSequenceCyclic("fire_release", "0");
   %this.addSequence("timeline", "soldier_idle", "146", "205", "1", "0");
   %this.addSequence("timeline", "soldier_run", "236", "295", "1", "0");
   %this.addSequence("timeline", "soldier_run2sprint", "326", "341", "1", "0");
   %this.setSequenceCyclic("soldier_run2sprint", "0");
   %this.addSequence("timeline", "soldier_sprint", "376", "395", "1", "0");
   %this.addSequence("timeline", "soldier_sprint2run", "426", "441", "1", "0");
   %this.setSequenceCyclic("soldier_sprint2run", "0");
   %this.addSequence("timeline", "soldier_switch_out", "546", "561", "1", "0");
   %this.setSequenceCyclic("soldier_switch_out", "0");
   %this.addSequence("timeline", "soldier_switch_in", "10", "98", "1", "0");
   %this.setSequenceCyclic("soldier_switch_in", "0");
   %this.addSequence("timeline", "soldier_fire", "476", "500", "1", "0");
   %this.setSequenceCyclic("soldier_fire", "0");
   %this.addSequence("timeline", "soldier_fire_release", "500", "521", "1", "0");
   %this.setSequenceCyclic("soldier_fire_release", "0");
}
