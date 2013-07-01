// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeServerScripts()
{
   exec("./base/commands.cs");
   exec("./base/misc.cs");
   exec("./base/bleedfx.cs");
   exec("./base/etherform.cs");
   exec("./forms/light/exec.cs");
   exec("./weapons/badger/v1/exec.cs");
   exec("./weapons/raptor/v1/exec.cs");
   exec("./weapons/bulldog/v1/exec.cs");
}
