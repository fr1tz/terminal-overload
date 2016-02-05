// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if($AUTOEXEC_CONTEXT $= "ClientInit")
{
   exec("./startServer.cs");
   exec("./startServer.gui");
   StartServerGui_RESO.gameType = "RESO" SPC $GameVersionString;
   shellAddStartServerGui(StartServerGui_RESO);
}


