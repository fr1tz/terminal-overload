// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function loadContentModule_notcCatSniperGui()
{
   exec("./CatSniperGui.cs");
   exec("./CatSniperGui.gui");
   exec("./CatSniperGuiOverlay.gui");
   exec("./postFx.cs");
}

if(isFunction("unloadContentModule_notcCatSniperGui"))
   unloadContentModule_notcCatSniperGui();

loadContentModule_notcCatSniperGui();

function unloadContentModule_notcCatSniperGui()
{

}

