// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

   // BEGIN: General pistol Sequences
   // Extracted from Ryder
   %this.addSequence("art/shapes/weapons/Ryder/FP_Ryder.DAE run", "Pistol_run");
   %this.addSequence("art/shapes/weapons/Ryder/FP_Ryder.DAE sprint", "Pistol_sprint");
   %this.addSequence("art/shapes/weapons/Ryder/FP_Ryder.DAE idle", "Pistol_idle");
   %this.addSequence("art/shapes/weapons/Ryder/FP_Ryder.DAE fire", "Pistol_fire");
   %this.addSequence("art/shapes/weapons/Ryder/FP_Ryder.DAE reload", "Pistol_reload");
   %this.addSequence("art/shapes/weapons/Ryder/FP_Ryder.DAE switch_out", "Pistol_switch_out");
   %this.addSequence("art/shapes/weapons/Ryder/FP_Ryder.DAE switch_in", "Pistol_switch_in");
   
   %this.setSequenceCyclic("Pistol_fire", "0");
   %this.setSequenceCyclic("Pistol_reload", "0");
   %this.setSequenceCyclic("Pistol_switch_out", "0");
   %this.setSequenceCyclic("Pistol_switch_in", "0");
   // END: General pistol Sequences