
singleton TSShapeConstructor(xa_notc_core_shaapes_standardcat_old_dts)
{
   baseShape = "./old.dts";
};

function xa_notc_core_shaapes_standardcat_old_dts::onLoad(%this)
{
   %this.addSequence("./oldanims/nm/root.dsq", "root", "0", "10", "1", "0");
   %this.addSequence("./oldanims/nm/run.dsq", "run", "0", "10", "1", "0");
   %this.addSequence("./oldanims/nm/back.dsq", "back", "0", "10", "1", "0");
   %this.addSequence("./oldanims/nm/side.dsq", "side", "0", "8", "1", "0");
   %this.addSequence("./oldanims/nm/root.dsq", "rootMarching", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/run.dsq", "runMarching", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/back.dsq", "backMarching", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/side.dsq", "sideMarching", "0", "7", "1", "0");
   %this.addSequence("./oldanims/a/holdnoweapon.dsq", "look", "0", "7", "1", "0");
   %this.setSequenceCyclic("look", "0");
   %this.addSequence("./oldanims/a/holdgun_onehand.dsq", "look2", "0", "7", "1", "0");
   %this.addSequence("./oldanims/a/holdblaster.dsq", "holdblaster", "0", "7", "1", "0");
   %this.setSequenceCyclic("holdblaster", "0");
   %this.setSequenceBlend("holdblaster", "0", "", "0");
   %this.addSequence("./oldanims/ub/aimblaster.dsq", "aimblaster", "0", "7", "1", "0");
   %this.addSequence("./oldanims/ub/holdrifle.dsq", "holdrifle", "0", "7", "1", "0");
   %this.setSequencePriority("holdrifle", "0");
   %this.addSequence("./oldanims/ub/aimrifle.dsq", "aimrifle", "0", "7", "1", "0");
   %this.setSequencePriority("aimrifle", "0");
   %this.addSequence("./oldanims/nm/diehead.dsq", "death1", "0", "7", "1", "0");
   %this.setSequenceBlend("death1", "0", "", "0");
   %this.addSequence("./oldanims/nm/diechest.dsq", "death2", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/dieback.dsq", "death3", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/diesidelf.dsq", "death4", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/diesidert.dsq", "death5", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/dieleglf.dsq", "death6", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/dielegrt.dsq", "death7", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/dieslump.dsq", "death8", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/dieknees.dsq", "death9", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/dieforward.dsq", "death10", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/diespin.dsq", "death11", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/headside.dsq", "headside", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/recoilde.dsq", "light_recoil", "0", "7", "1", "0");
   %this.setSequencePriority("light_recoil", "0");
   %this.addSequence("./oldanims/nm/standjump.dsq", "standjump", "0", "7", "1", "0");
   %this.setSequenceBlend("standjump", "0", "", "0");
   %this.addSequence("./oldanims/nm/head.dsq", "head", "0", "7", "1", "0");
   %this.addSequence("./oldanims/nm/fall.dsq", "fall", "0", "7", "1", "0");
   %this.setSequenceBlend("fall", "0", "", "0");
   %this.addSequence("./oldanims/nm/land.dsq", "land", "0", "4", "1", "0");
   %this.addSequence("./oldanims/nm/jump.dsq", "jump", "0", "4", "1", "0");
   %this.addSequence("./oldanims/b/slide.dsq", "slide", "0", "4", "1", "0");
}
