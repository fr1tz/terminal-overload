// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// RecordingsGui is the main TSControl through which the a demo game recording
// is viewed. 
//-----------------------------------------------------------------------------

function recordingsDlg::onWake()
{
	RecordingsDlgList.clear();
	%i = 0;
	%filespec = "recordings/*.rec";
	//echo(%filespec);
	for(%file = findFirstFile(%filespec); %file !$= ""; %file = findNextFile(%filespec))
	{
		%fileName = %file;

      %display = "";
      %str = strreplace(%fileName, "__", " ");
      for(%j = 0; %j < getWordCount(%str); %j++)
      {
         %seg = getWord(%str, %j);
         if(getSubStr(%seg,0,5) $= "DATE_")
         {
            %seg = strreplace(%seg, "DATE_", "");
            %seg = strreplace(%seg, "_", ".");
         }
         else if(getSubStr(%seg,0,5) $= "TIME_")
         {
            %seg = strreplace(%seg, "TIME_", "");
            %seg = strreplace(%seg, "_", ":");
         }
         %display = %display SPC %seg;
      }
      //echo("filename: '" @ %filename @ "'");
		RecordingsDlgList.addRow(%i++, %display TAB %filename);
	}
	RecordingsDlgList.sort(0);
	RecordingsDlgList.setSelectedRow(0);
	RecordingsDlgList.scrollVisible(0);
}

function StartSelectedDemo()
{
   // first unit is filename
   %sel = RecordingsDlgList.getSelectedId();
   %rowText = RecordingsDlgList.getRowTextById(%sel);

   %demoFile = getField(%rowText, 1);

   new GameConnection(ServerConnection);
   RootGroup.add(ServerConnection);
   
   // Execute content scripts.
   %files = "xa/notc/core/client/audio/Descriptions/v1/exec.cs" TAB
            "xa/notc/core/client/audio/Hearing/v1/exec.cs" TAB
            "xa/notc/core/client/audio/HitSound/v1/exec.cs" TAB
            "xa/notc/core/client/gui/CatGui/v1/exec.cs" TAB
            "xa/notc/core/client/gui/EtherformGui/v1/exec.cs" TAB
            "xa/notc/core/client/gui/ChatHud/v1/exec.cs" TAB
            "xa/notc/core/client/gui/GuiChanger/v1/exec.cs" TAB
            "xa/notc/core/client/gui/VitalsHud/v1/exec.cs" TAB
            "xa/notc/core/client/gui/MinimapHud/v1/exec.cs" TAB
            "xa/notc/core/client/gui/LoadoutHud/v1/exec.cs" TAB
            "xa/notc/core/client/gui/MiscHud/v1/exec.cs" TAB
            "xa/notc/core/client/gui/HudIcons/v1/exec.cs" TAB
            "xa/notc/core/client/misc/Commands/v1/exec.cs" TAB
            "xa/notc/core/client/misc/Materials/v1/exec.cs" TAB
            "xa/notc/core/client/postfx/ChromaticLens/v1/exec.cs" TAB
            "xa/notc/deathmatch/client/gui/EndGameGui/v1/exec.cs" TAB
            "xa/notc/deathmatch/client/gui/PlayerList/v1/exec.cs";
   %fieldCount = getFieldCount(%files);
   for(%i = 0; %i < %fieldCount; %i++)
   {
      %file = getField(%files, %i);
      clientCmdExecContentScript(%file);
   }
   
   // Just load all materials.
   if(isObject(RecordingMaterialsGroup))
      RecordingMaterialsGroup.delete();
   new SimGroup(RecordingMaterialsGroup);
   %instantGroupStor = $instantGroup;
   $instantGroup = RecordingMaterialsGroup;
   loadMaterials();
   $instantGroup = %instantGroupStor;

   // Start up important client-side stuff, such as the group
   // for particle emitters.  This doesn't get launched during a demo
   // as we short circuit the whole mission loading sequence.
   clientStartMission();

   if(ServerConnection.playDemo(%demoFile))
   {
      Canvas.setContent(HudlessPlayGui);
      Canvas.popDialog(RecordingsDlg);
      ServerConnection.prepDemoPlayback();
   }
   else 
   {
      MessageBoxOK("Playback Failed", "Demo playback failed for file '" @ %demoFile @ "'.");
      if (isObject(ServerConnection)) {
         ServerConnection.delete();
      }
   }
}

function startDemoRecord()
{
   // make sure that current recording stream is stopped
   ServerConnection.stopRecording();
   
   // make sure we aren't playing a demo
   if(ServerConnection.isDemoPlaying())
      return;
      
   %player = strreplace(cGetPlayerName(), "/", "");
   %player = strreplace(%player, " ", "");

   %time = "DATE_" @ getDateAndTime();
   %time = strreplace(%time, ".", "_");
   %time = strreplace(%time, "-", "__TIME_");
   %time = strreplace(%time, ".", "_");
   %time = strreplace(%time, ":", "_");
   
   %file = "recordings/"
			@ %player @ "__"
         @ $GameVersionString @ "__"
         @ %time
         @ ".rec";

   $DemoFileName = %file;

   ChatHud.AddLine( "\c4Recording to file [\c2" @ $DemoFileName @ "\cr].");

   ServerConnection.prepDemoRecord();
   ServerConnection.startRecording($DemoFileName);

   // make sure start worked
   if(!ServerConnection.isDemoRecording())
   {
      deleteFile($DemoFileName);
      ChatHud.AddLine( "\c3 *** Failed to record to file [\c2" @ $DemoFileName @ "\cr].");
      $DemoFileName = "";
   }
   else
      commandToServer('RecordingDemo', true);
}

function stopDemoRecord()
{
   // make sure we are recording
   if(ServerConnection.isDemoRecording())
   {
      ChatHud.AddLine( "\c4Recording file [\c2" @ $DemoFileName @ "\cr] finished.");
      ServerConnection.stopRecording();
      commandToServer('RecordingDemo', false);
   }
}

function toggleDemoRecord()
{
   if(ServerConnection.isDemoRecording())
      stopDemoRecord();
   else
      startDemoRecord();
}

function demoPlaybackComplete()
{
   disconnect();

   // Clean up important client-side stuff, such as the group
   // for particle emitters and the decal manager.  This doesn't get 
   // launched during a demo as we short circuit the whole mission 
   // handling functionality.
   clientEndMission();
   
   if(isObject(RecordingMaterialsGroup))
      RecordingMaterialsGroup.delete();

   if (isObject( MainMenuGui ))
      Canvas.setContent( MainMenuGui );

   Canvas.pushDialog(RecordingsDlg);
}
