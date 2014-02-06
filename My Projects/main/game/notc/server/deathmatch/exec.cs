// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeDeathmatchServerScripts()
{
   exec("notc/server/base/exec.cs");
   
   exec("notc/server/forms/standardcat/exec.cs");

   exec("./gameDM.cs");
   exec("./health.cs");
}

executeDeathmatchServerScripts();

