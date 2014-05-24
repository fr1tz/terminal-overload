// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

exec("./cmds.cs");
exec("./default.prefs.cs");
exec("./default.bind.cs");
exec("./default.bind.etherform.cs");
exec("./catControls.gui");
exec("./catControls.cs");
exec("./etherformControls.gui");
exec("./etherformControls.cs");
exec("./controlsRemapDlg.gui");
exec("./controlsRemapDlg.cs");
exec("./misc.gui");
exec("./misc.cs");
exec("./muxer.gui");
exec("./muxer.cs");

if(isFile("notc/client/settings/XaNotc1CatMoveMap.cs"))
   exec("notc/client/settings/XaNotc1CatMoveMap.cs");
   
if(isFile("notc/client/settings/XaNotc1EtherformMoveMap.cs"))
   exec("notc/client/settings/XaNotc1EtherformMoveMap.cs");

gameSettingsAddEditor(XaNotcSettings1_MuxerGui);

