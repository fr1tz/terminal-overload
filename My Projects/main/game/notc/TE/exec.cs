// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeTEServerScripts()
{
   exec("notc/base/exec.cs");
   exec("notc/eth/aiPlayer.cs");
   exec("notc/eth/eth.cs");
   exec("notc/eth/ethPlayerList.cs");
   exec("./TE.cs");
   exec("./gameCoreTE.cs");
}

executeTEServerScripts();

