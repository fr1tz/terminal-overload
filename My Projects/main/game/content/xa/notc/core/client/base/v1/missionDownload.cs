// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//----------------------------------------------------------------------------
// Mission Loading
// Server download handshaking.  This produces a number of onPhaseX
// calls so the game scripts can update the game's GUI.
//
// Loading Phases:
// Phase 1: Download Datablocks
// Phase 2: Download Ghost Objects
// Phase 3: Scene Lighting
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Phase 1 
//----------------------------------------------------------------------------

function clientCmdMissionStartPhase1(%seq, %missionName, %musicTrack)
{
   // These need to come after the cls.
   echo ("*** New Mission: " @ %missionName);
   echo ("*** Phase 1: Download Datablocks & Targets");
   onMissionDownloadPhase1(%missionName, %musicTrack);
   commandToServer('MissionStartPhase1Ack', %seq);
}

function onDataBlockObjectReceived(%index, %total)
{
   onPhase1Progress(%index / %total);
}

function onMissionDownloadPhase1(%missionName, %musicTrack)
{
   // Load the post effect presets for this mission.
   %path = "levels/" @ fileBase( %missionName ) @ $PostFXManager::fileExtension;
   if ( isScriptFile( %path ) )
      postFXManager::loadPresetHandler( %path );
   else
      PostFXManager::settingsApplyDefaultPreset();

   // Close and clear the message hud (in case it's open)
   if ( isObject( MessageHud ) )
      MessageHud.close();

   // Reset the loading progress controls:
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue(0);
   LoadingProgressTxt.setValue("LOADING DATABLOCKS");
   Canvas.repaint();
}

function onPhase1Progress(%progress)
{
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue(%progress);
   Canvas.repaint(33);
}

function onPhase1Complete()
{
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue( 1 );
   Canvas.repaint();
}

//----------------------------------------------------------------------------
// Phase 2
//----------------------------------------------------------------------------

function clientCmdMissionStartPhase2(%seq,%missionName)
{
   onPhase1Complete();
   echo ("*** Phase 2: Download Ghost Objects");
   onMissionDownloadPhase2(%missionName);
   commandToServer('MissionStartPhase2Ack', %seq, $pref::Player:PlayerDB);
}

function onGhostAlwaysStarted(%ghostCount)
{
   $ghostCount = %ghostCount;
   $ghostsRecvd = 0;
}

function onGhostAlwaysObjectReceived()
{
   $ghostsRecvd++;
   onPhase2Progress($ghostsRecvd / $ghostCount);
}

function onMissionDownloadPhase2()
{
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue(0);
   LoadingProgressTxt.setValue("LOADING OBJECTS");
   Canvas.repaint();
}

function onPhase2Progress(%progress)
{
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue(%progress);
   Canvas.repaint(33);
}

function onPhase2Complete()
{
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue( 1 );
   Canvas.repaint();
}

function onFileChunkReceived(%fileName, %ofs, %size)
{
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue(%ofs / %size);
   LoadingProgressTxt.setValue("Downloading " @ %fileName @ "...");
}

//----------------------------------------------------------------------------
// Phase 3
//----------------------------------------------------------------------------

function clientCmdMissionStartPhase3(%seq,%missionName)
{
   onPhase2Complete();
   StartClientReplication();
   StartFoliageReplication();
   
   // Load the static mission decals.
   decalManagerLoad( %missionName @ ".decals" );
   
   echo ("*** Phase 3: Mission Lighting");
   $MSeq = %seq;
   $Client::MissionFile = %missionName;

   // Need to light the mission before we are ready.
   // The sceneLightingComplete function will complete the handshake 
   // once the scene lighting is done.
   if (lightScene("sceneLightingComplete", ""))
   {
      echo("Lighting mission....");
      schedule(1, 0, "updateLightingProgress");
      onMissionDownloadPhase3(%missionName);
      $lightingMission = true;
   }
}

function updateLightingProgress()
{
   onPhase3Progress($SceneLighting::lightingProgress);
   if ($lightingMission)
      $lightingProgressThread = schedule(1, 0, "updateLightingProgress");
}

function sceneLightingComplete()
{
   echo("Mission lighting done");
   onPhase3Complete();
   
   // The is also the end of the mission load cycle.
   onMissionDownloadComplete();
   commandToServer('MissionStartPhase3Ack', $MSeq);
}

function onMissionDownloadPhase3()
{
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue(0);
   LoadingProgressTxt.setValue("LIGHTING MISSION");
   Canvas.repaint();
}

function onPhase3Progress(%progress)
{
   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgress.setValue(%progress);
   Canvas.repaint(33);
}

function onPhase3Complete()
{
   $lightingMission = false;

   if ( !isObject( LoadingProgress ) )
      return;

   LoadingProgressTxt.setValue("STARTING MISSION");
   LoadingProgress.setValue( 1 );
   Canvas.repaint();
}

//----------------------------------------------------------------------------
// Mission loading done!
//----------------------------------------------------------------------------

function onMissionDownloadComplete()
{
   // Client will shortly be dropped into the game, so this is
   // good place for any last minute gui cleanup.
}


//------------------------------------------------------------------------------
// Before downloading a mission, the server transmits the mission
// information through these messages.
//------------------------------------------------------------------------------

addMessageCallback( 'MsgLoadInfo', handleLoadInfoMessage );
addMessageCallback( 'MsgLoadDescripition', handleLoadDescriptionMessage );
addMessageCallback( 'MsgLoadInfoDone', handleLoadInfoDoneMessage );
addMessageCallback( 'MsgLoadFailed', handleLoadFailedMessage );

//------------------------------------------------------------------------------

function handleLoadInfoMessage( %msgType, %msgString, %mapName )
{
   // Make sure the LoadingGUI is displayed
   if (Canvas.getContent() != LoadingGui.getId())
   {
      loadLoadingGui("LOADING MISSION FILE");
   }

	// Clear all of the loading info lines:
	for( %line = 0; %line < LoadingGui.qLineCount; %line++ )
		LoadingGui.qLine[%line] = "";
	LoadingGui.qLineCount = 0;
}

//------------------------------------------------------------------------------

function handleLoadDescriptionMessage( %msgType, %msgString, %line )
{
	LoadingGui.qLine[LoadingGui.qLineCount] = %line;
	LoadingGui.qLineCount++;

   // Gather up all the previous lines, append the current one
   // and stuff it into the control
	%text = "<spush><font:Quantico:16>";

	for( %line = 0; %line < LoadingGui.qLineCount - 1; %line++ )
		%text = %text @ LoadingGui.qLine[%line] @ " ";
   %text = %text @ LoadingGui.qLine[%line] @ "<spop>";
}

//------------------------------------------------------------------------------

function handleLoadInfoDoneMessage( %msgType, %msgString )
{
   // This will get called after the last description line is sent.
}

//------------------------------------------------------------------------------

function handleLoadFailedMessage( %msgType, %msgString )
{
   MessageBoxOK( "Mission Load Failed", %msgString NL "Press OK to return to the Main Menu", "disconnect();" );
}


