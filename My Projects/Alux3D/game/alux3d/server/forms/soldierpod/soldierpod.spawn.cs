// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function Spawn_Soldierpod(%transform, %teamId)
{
   //echo("Spawn_Soldierpod("@%transform@","@%teamId@")");
   
	%obj = new FlyingVehicle() {
		dataBlock = FrmSoldierpod;
		teamId = %teamId;
	};
   MissionCleanup.add(%obj);
   
   %obj.setTransform(%transform);
	//%player.playAudio(0, CatSpawnSound);
   createExplosion(FrmCrateDematerializeExplosion, %obj.getPosition(), "0 0 1");

   return %obj;
}
