// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeCTFServerScripts()
{
   exec("reso/base/exec.cs");
   exec("reso/eth/aiPlayer.cs");
   exec("reso/eth/eth.cs");
   exec("reso/eth/ethPlayerList.cs");
   exec("./sounds.cs");
   exec("./commands.cs");
   exec("./ctf.cs");
   exec("./flag.cs");
   exec("./flagstand.cs");
   exec("./gameCoreCTF.cs");
}

executeCTFServerScripts();

