// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function executeControllersServerScripts()
{
   exec("./controller.cs");
   exec("./widgetGrid.cs");
   exec("./widgetList.cs");
   exec("./smartphoneController.cs");
}

executeControllersServerScripts();

