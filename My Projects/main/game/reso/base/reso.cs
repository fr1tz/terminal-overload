// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function RESO::spawnDisc(%controller)
{
   %player = new resoPlayer() {
      dataBlock = FrmAlphaDisc;
      client = %controller;
      teamId = %controller.getId();
      isCAT = true;
   };
   MissionCleanup.add(%player);	
   
//   %spawnGroups = $Game::DefaultPlayerSpawnGroups;
//   if(isObject(%client.team))
//   {
//      %teamId = %client.team.teamId;
//      %spawnGroups = "Team"@%teamId@"SpawnPoints" SPC %spawnGroups;
//   }
//   %playerSpawnPoint = pickPlayerSpawnPoint(%spawnGroups);

   %pos = "0 0 10";
   %player.setPosition(%pos);
   
   %colorR = getRandom(255);
   %colorG = getRandom(255);
   %colorB = getRandom(255);
   %colorI = %colorR SPC %colorG SPC %colorB;
   
   %player.paletteColors[0] = %colorI;
   %player.paletteColors[1] = %colorI;   

   %controller.player = %player;
}

