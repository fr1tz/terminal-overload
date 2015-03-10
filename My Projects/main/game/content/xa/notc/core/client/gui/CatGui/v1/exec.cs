// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function loadContentModule_notcCatGui()
{
   exec("./CatGui.cs");
   exec("./CatGui.gui");
   exec("./CatGuiOverlay.gui");
}

if(isFunction("unloadContentModule_notcCatGui"))
   unloadContentModule_notcCatGui();

loadContentModule_notcCatGui();

function unloadContentModule_notcCatGui()
{

}

