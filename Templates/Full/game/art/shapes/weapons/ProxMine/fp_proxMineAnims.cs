// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

   // BEGIN: ProxMine Sequences
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE run", "ProxMine_run");
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE run2sprint", "ProxMine_run2sprint");
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE sprint", "ProxMine_sprint");
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE sprint2run", "ProxMine_sprint2run");
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE idle", "ProxMine_idle");
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE fire", "ProxMine_fire");
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE fire_release", "ProxMine_fire_release");
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE switch_out", "ProxMine_switch_out");
   %this.addSequence("art/shapes/weapons/ProxMine/FP_ProxMine.DAE switch_in", "ProxMine_switch_in");
   
   %this.setSequenceCyclic("ProxMine_fire", "0");
   %this.setSequenceCyclic("ProxMine_fire_release", "0");
   %this.setSequenceCyclic("ProxMine_switch_out", "0");
   %this.setSequenceCyclic("ProxMine_switch_in", "0");
   %this.setSequenceCyclic("ProxMine_run2sprint", "0");
   %this.setSequenceCyclic("ProxMine_sprint2run", "0");
   // END: ProxMine Sequences
