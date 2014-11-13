// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeDeathmatchServerScripts()
{
   exec("notc/base/exec.cs");
   exec("./aiPlayer.cs");
   exec("./dm.cs");
   exec("./gameCoreDM.cs");
   exec("./health.cs");
}

executeDeathmatchServerScripts();

