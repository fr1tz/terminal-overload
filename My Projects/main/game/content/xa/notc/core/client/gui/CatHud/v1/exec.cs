// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function loadContentModule_notcCatHud()
{
   exec("./CatHud.cs");
   exec("./CatHud.gui");
}

if(isFunction("unloadContentModule_notcCatHud"))
   unloadContentModule_notcCatHud();

loadContentModule_notcCatHud();

function unloadContentModule_notcCatHud()
{

}

