// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Game duration in secs, no limit if the duration is set to 0
$Game::Duration = 20 * 60;

// When a client score reaches this value, the game is ended.
$Game::EndGameScore = 30;

// Pause while looking over the end game screen (in secs)
$Game::EndGamePause = 10;

//-----------------------------------------------------------------------------

function onGameDurationEnd()
{
   // This "redirect" is here so that we can abort the game cycle if
   // the $Game::Duration variable has been cleared, without having
   // to have a function to cancel the schedule.

   if ($Game::Duration && !(EditorIsActive() && GuiEditorIsActive()))
      Game.onGameDurationEnd();
}

//-----------------------------------------------------------------------------

function cycleGame()
{
   // This is setup as a schedule so that this function can be called
   // directly from object callbacks.  Object callbacks have to be
   // carefull about invoking server functions that could cause
   // their object to be deleted.

   if (!$Game::Cycling)
   {
      $Game::Cycling = true;
      $Game::Schedule = schedule(0, 0, "onCycleExec");
   }
}

function onCycleExec()
{
   // End the current game and start another one, we'll pause for a little
   // so the end game victory screen can be examined by the clients.

   //endGame();
   endMission();
   $Game::Schedule = schedule($Game::EndGamePause * 1000, 0, "onCyclePauseEnd");
}

function onCyclePauseEnd()
{
   $Game::Cycling = false;

   // Just cycle through the missions for now.

   %search = $Server::MissionFileSpec;
   %oldMissionFile = makeRelativePath( $Server::MissionFile );
      
   for( %file = findFirstFile( %search ); %file !$= ""; %file = findNextFile( %search ) )
   {
      if( %file $= %oldMissionFile )
      {
         // Get the next one, back to the first if there is no next.
         %file = findNextFile( %search );
         if( %file $= "" )
            %file = findFirstFile(%search);
         break;
      }
   }

   if( %file $= "" )
      %file = findFirstFile( %search );

   loadMission(%file);
}

//-----------------------------------------------------------------------------
// GameConnection Methods
// These methods are extensions to the GameConnection class. Extending
// GameConnection makes it easier to deal with some of this functionality,
// but these could also be implemented as stand-alone functions.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

function GameConnection::onLeaveMissionArea(%this)
{
   // The control objects invoke this method when they
   // move out of the mission area.

   messageClient(%this, 'MsgClientJoin', '\c2Now leaving the mission area!');
}

function GameConnection::onEnterMissionArea(%this)
{
   // The control objects invoke this method when they
   // move back into the mission area.

   messageClient(%this, 'MsgClientJoin', '\c2Now entering the mission area.');
}

//-----------------------------------------------------------------------------

function GameConnection::onDeath(%this, %sourceObject, %sourceClient, %damageType, %damLoc)
{
   game.onDeath(%this, %sourceObject, %sourceClient, %damageType, %damLoc);
}

// ----------------------------------------------------------------------------
// weapon HUD
// ----------------------------------------------------------------------------
function GameConnection::setAmmoAmountHud(%client, %amount, %amountInClips )
{
   commandToClient(%client, 'SetAmmoAmountHud', %amount, %amountInClips);
}

function GameConnection::RefreshWeaponHud(%client, %amount, %preview, %ret, %zoomRet, %amountInClips)
{
   commandToClient(%client, 'RefreshWeaponHud', %amount, %preview, %ret, %zoomRet, %amountInClips);
}

//-----------------------------------------------------------------------------

function GameConnection::control(%client, %obj)
{
   %client.setControlObject(%obj);
   
   if(%obj.fovDelta !$= "")
      commandToClient(%client, 'SetFovDelta', %obj.fovDelta);
      
   if(%obj.guiIrisSize !$= "" || %obj.guiIrisDt !$= "" )
      commandToClient(%client, 'GuiSetIris', %obj.guiIrisSize, %obj.guiIrisDt);
      
   if(%obj.viewMotionBlurActive !$= ""
   || %obj.viewMotionBlurVelMul !$= "")
   {
      commandToClient(%client, 'ViewSetMotionBlur',
         %obj.viewMotionBlurActive,
         %obj.viewMotionBlurVelMul
      );
   }
}
