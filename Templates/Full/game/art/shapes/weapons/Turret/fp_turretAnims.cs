// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

   // BEGIN: Turret Sequences
   %this.addSequence("art/shapes/weapons/Turret/FP_Turret.DAE run", "Turret_run");
   %this.addSequence("art/shapes/weapons/Turret/FP_Turret.DAE sprint", "Turret_sprint");
   %this.addSequence("art/shapes/weapons/Turret/FP_Turret.DAE idle", "Turret_idle");
   %this.addSequence("art/shapes/weapons/Turret/FP_Turret.DAE fire", "Turret_fire");
   %this.addSequence("art/shapes/weapons/Turret/FP_Turret.DAE switch_out", "Turret_switch_out");
   %this.addSequence("art/shapes/weapons/Turret/FP_Turret.DAE switch_in", "Turret_switch_in");
   
   %this.setSequenceCyclic("Turret_fire", "0");
   %this.setSequenceCyclic("Turret_switch_out", "0");
   %this.setSequenceCyclic("Turret_switch_in", "0");
   // END: Turret Sequences
