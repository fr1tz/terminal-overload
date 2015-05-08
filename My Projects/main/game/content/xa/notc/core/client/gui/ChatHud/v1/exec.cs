// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if(isFunction("unloadContentModule_notcChatHud"))
   unloadContentModule_notcChatHud();

function loadContentModule_notcChatHud()
{
   exec("./ChatHud.cs");
   exec("./ChatHud.gui");
   exec("./MessageHud.gui");
}

function unloadContentModule_notcChatHud()
{

}

loadContentModule_notcChatHud();

