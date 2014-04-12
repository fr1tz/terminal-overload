// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

exec("./cmds.cs");
exec("./default.prefs.cs");
exec("./default.bind.cs");
exec("./catControls.gui");
exec("./catControls.cs");
exec("./controlsRemapDlg.gui");
exec("./controlsRemapDlg.cs");
exec("./misc.gui");
exec("./misc.cs");
exec("./muxer.gui");
exec("./muxer.cs");

if(isFile("notc/client/settings/notc1controls.cs"))
   exec("notc/client/settings/notc1controls.cs");

gameSettingsAddEditor(XaNotcSettings1_MuxerGui);

