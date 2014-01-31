// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function Spawn_Crackpack(%transform, %teamId)
{
   //echo("Spawn_Crackpack("@%transform@","@%teamId@")");
   
   %obj = new Item() {
	  dataBlock = WpnCrackpack;
     teamId = %teamId;
   };

   MissionCleanup.add(%obj);
   %obj.setTransform(%transform);

   return %obj;
}
