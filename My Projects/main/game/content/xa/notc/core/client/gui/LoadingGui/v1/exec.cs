// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function execXaNotcLoadingGui()
{
   exec("./loadingGui.cs");
   exec("./loadingGui.gui");
   exec("./missionDownload.cs");
   exec("./commands.cs");
}

execXaNotcLoadingGui();

