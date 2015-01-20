// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeCTFServerScripts()
{
   exec("notc/base/exec.cs");
   exec("notc/eth/aiPlayer.cs");
   exec("notc/eth/eth.cs");
   exec("notc/eth/ethPlayerList.cs");
   exec("./sounds.cs");
   exec("./commands.cs");
   exec("./ctf.cs");
   exec("./flag.cs");
   exec("./flagstand.cs");
   exec("./gameCoreCTF.cs");
}

executeCTFServerScripts();

