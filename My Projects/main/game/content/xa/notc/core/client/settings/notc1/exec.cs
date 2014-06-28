// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

exec("./cmds.cs");
exec("./default.prefs.cs");
exec("./default.bind.cat.cs");
exec("./default.bind.etherform.cs");
exec("./default.bind.misc.cs");
exec("./catControls.cs");
exec("./catControls.gui");
exec("./etherformControls.cs");
exec("./etherformControls.gui");
exec("./controlsRemapDlg.cs");
exec("./controlsRemapDlg.gui");
exec("./misc.cs");
exec("./misc.gui");
exec("./miscControls.cs");
exec("./miscControls.gui");
exec("./muxer.cs");
exec("./muxer.gui");

if(isFile("notc/client/settings/XaNotc1CatMoveMap.cs"))
   exec("notc/client/settings/XaNotc1CatMoveMap.cs");
   
if(isFile("notc/client/settings/XaNotc1EtherformMoveMap.cs"))
   exec("notc/client/settings/XaNotc1EtherformMoveMap.cs");
   
if(isFile("notc/client/settings/XaNotc1MiscMoveMap.cs"))
   exec("notc/client/settings/XaNotc1MiscMoveMap.cs");

gameSettingsAddEditor(XaNotcSettings1_MuxerGui);

