// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function onMissionDownloadPhase1(%missionName, %musicTrack)
{
   // Load the post effect presets for this mission.
   %path = "levels/" @ fileBase( %missionName ) @ $PostFXManager::fileExtension;
   if ( isScriptFile( %path ) )
      postFXManager::loadPresetHandler( %path );
   else
      PostFXManager::settingsApplyDefaultPreset();

   // Close and clear the message hud (in case it's open)
   //if ( isObject( MessageHud ) )
   //   MessageHud.close();

   // Reset the loading progress controls:
   XaNotcLoadingGui-->LoadingProgress.setValue(0);
   XaNotcLoadingGui-->LoadingText.setValue("LOADING DATABLOCKS");

   Canvas.setContent(XaNotcLoadingGui);
   
   Canvas.repaint();
}

function onPhase1Progress(%progress)
{
   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingProgress.setValue(%progress);
   Canvas.repaint(33);
}

function onPhase1Complete()
{
   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingProgress.setValue( 1 );
   Canvas.repaint();
}

function onMissionDownloadPhase2()
{
   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingProgress.setValue(0);
   XaNotcLoadingGui-->LoadingText.setValue("LOADING OBJECTS");
   Canvas.repaint();
}

function onPhase2Progress(%progress)
{
   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingProgress.setValue(%progress);
   Canvas.repaint(33);
}

function onPhase2Complete()
{
   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingProgress.setValue( 1 );
   Canvas.repaint();
}

function onFileChunkReceived(%fileName, %ofs, %size)
{
   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingProgress.setValue(%ofs / %size);
   XaNotcLoadingGui-->LoadingText.setValue("Downloading " @ %fileName @ "...");
}

function onMissionDownloadPhase3()
{
   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingProgress.setValue(0);
   XaNotcLoadingGui-->LoadingText.setValue("LIGHTING MISSION");
   Canvas.repaint();
}

function onPhase3Progress(%progress)
{
   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingProgress.setValue(%progress);
   Canvas.repaint(33);
}

function onPhase3Complete()
{
   $lightingMission = false;

   if ( !isObject( XaNotcLoadingGui-->LoadingProgress ) )
      return;

   XaNotcLoadingGui-->LoadingText.setValue("STARTING MISSION");
   XaNotcLoadingGui-->LoadingProgress.setValue( 1 );
   Canvas.repaint();
}

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
   if (Canvas.getContent() != XaNotcLoadingGui.getId())
   {
      loadXaNotcLoadingGui("LOADING MISSION FILE");
   }

	// Clear all of the loading info lines:
	for( %line = 0; %line < XaNotcLoadingGui.qLineCount; %line++ )
		XaNotcLoadingGui.qLine[%line] = "";
	XaNotcLoadingGui.qLineCount = 0;
}

//------------------------------------------------------------------------------

function handleLoadDescriptionMessage( %msgType, %msgString, %line )
{
	XaNotcLoadingGui.qLine[XaNotcLoadingGui.qLineCount] = %line;
	XaNotcLoadingGui.qLineCount++;

   // Gather up all the previous lines, append the current one
   // and stuff it into the control
	%text = "<spush><font:Quantico:16>";

	for( %line = 0; %line < XaNotcLoadingGui.qLineCount - 1; %line++ )
		%text = %text @ XaNotcLoadingGui.qLine[%line] @ " ";
   %text = %text @ XaNotcLoadingGui.qLine[%line] @ "<spop>";
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


