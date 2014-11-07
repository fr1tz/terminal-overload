// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeTEServerScripts()
{
   exec("notc/server/base/exec.cs");
   exec("notc/server/eth/aiPlayer.cs");
   exec("notc/server/eth/eth.cs");
   exec("notc/server/eth/ethPlayerList.cs");
   exec("./TE.cs");
   exec("./gameCoreTE.cs");
}

executeTEServerScripts();

