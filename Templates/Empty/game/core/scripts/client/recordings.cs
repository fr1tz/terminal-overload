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
   %filespec = $currentMod @ "/recordings/*.rec";
   echo(%filespec);
   for(%file = findFirstFile(%filespec); %file !$= ""; %file = findNextFile(%filespec)) 
      RecordingsDlgList.addRow(%i++, fileBase(%file));
   RecordingsDlgList.sort(0);
   RecordingsDlgList.setSelectedRow(0);
   RecordingsDlgList.scrollVisible(0);
}

function StartSelectedDemo()
{
   // first unit is filename
   %sel = RecordingsDlgList.getSelectedId();
   %rowText = RecordingsDlgList.getRowTextById(%sel);

   %file = $currentMod @ "/recordings/" @ getField(%rowText, 0) @ ".rec";

   new GameConnection(ServerConnection);
   RootGroup.add(ServerConnection);

   // Start up important client-side stuff, such as the group
   // for particle emitters.  This doesn't get launched during a demo
   // as we short circuit the whole mission loading sequence.
   clientStartMission();

   if(ServerConnection.playDemo(%file))
   {
      Canvas.setContent(PlayGui);
      Canvas.popDialog(RecordingsDlg);
      ServerConnection.prepDemoPlayback();
   }
   else 
   {
      MessageBoxOK("Playback Failed", "Demo playback failed for file '" @ %file @ "'.");
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
   
   for(%i = 0; %i < 1000; %i++)
   {
      %num = %i;
      if(%num < 10)
         %num = "0" @ %num;
      if(%num < 100)
         %num = "0" @ %num;

      %file = $currentMod @ "/recordings/demo" @ %num @ ".rec";
      if(!isfile(%file))
         break;
   }
   if(%i == 1000)
      return;

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
}

function stopDemoRecord()
{
   // make sure we are recording
   if(ServerConnection.isDemoRecording())
   {
      ChatHud.AddLine( "\c4Recording file [\c2" @ $DemoFileName @ "\cr] finished.");
      ServerConnection.stopRecording();
   }
}

function demoPlaybackComplete()
{
   disconnect();

   // Clean up important client-side stuff, such as the group
   // for particle emitters and the decal manager.  This doesn't get 
   // launched during a demo as we short circuit the whole mission 
   // handling functionality.
   clientEndMission();

   if (isObject( MainMenuGui ))
      Canvas.setContent( MainMenuGui );

   Canvas.pushDialog(RecordingsDlg);
}
