// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function loadContentModule_notcUserGui()
{
   exec("./UserGui.cs");
   exec("./UserGui.gui");
}

if(isFunction("unloadContentModule_notcUserGui"))
   unloadContentModule_notcUserGui();

loadContentModule_notcUserGui();

function unloadContentModule_notcUserGui()
{

}

