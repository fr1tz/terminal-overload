// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeEthernetServerScripts()
{
   exec("notc/server/base/exec.cs");

   exec("./aiPlayer.cs");
   exec("./commands.cs");
   exec("./eth.cs");
   exec("./gameCoreETH.cs");
   exec("./territoryZone.cs");
   exec("./ethPlayerList.cs");
}

executeEthernetServerScripts();

