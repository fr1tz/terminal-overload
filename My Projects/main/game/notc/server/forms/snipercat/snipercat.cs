// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock PlayerData(FrmSnipercat : FrmStandardcat)
{
   className = "FrmStandardcat";
   maxDamage = 60;
   damageBuffer = 0;
//	skidSpeed = 25;
//	skidFactor = 0.8;
};

// callback function: called by engine
function FrmSnipercat::onAdd(%this, %obj)
{
   //echo("FrmSnipercat::onAdd()");
   Parent::onAdd(%this, %obj);
   
//   %obj.setMeshHidden("innerwing_left", true);
//   %obj.setMeshHidden("innerwing_right", true);
//   %obj.setMeshHidden("outerwing_left", true);
//   %obj.setMeshHidden("outerwing_right", true);
}

