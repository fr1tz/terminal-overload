// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function loadContentModule_NotcCatGui()
{
   exec("./CatGui.cs");
   exec("./CatHud.gui");
   exec("./CatGui.gui");
}

if(isFunction("unloadContentModule_NotcCatGui"))
   unloadContentModule_NotcCatGui();

loadContentModule_NotcCatGui();

function unloadContentModule_NotcCatGui()
{

}

