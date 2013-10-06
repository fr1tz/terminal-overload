// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeBaseServerScripts()
{
   exec("./bleedfx.cs");
   exec("./commands.cs");
   exec("./gameCore.cs");
   exec("./game.cs");
   exec("./misc.cs");
}

executeBaseServerScripts();

