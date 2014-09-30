// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// SceneObject collision masks

$CollisionMask::Normal  = 1;
$CollisionMask::Stealth = 2;
$CollisionMask::Free1   = 4;
$CollisionMask::Free2   = 8;
$CollisionMask::Free3   = 16;
$CollisionMask::Free4   = 32;
$CollisionMask::Free5   = 64;
$CollisionMask::Free6   = 128;

//-----------------------------------------------------------------------------
// HudInfo Dataset types

$HudInfoDatasetType::DiscTarget = 1;
// string field: unused
//    int field: unused
//  float field: unused
//   bool field: true

$HudInfoDatasetType::TeamID = 2;
// string field: unused
//    int field: the team ID
//  float field: unused
//   bool field: unused

$HudInfoDatasetType::IconID = 3;
// string field: unused
//    int field: the icon ID
//  float field: unused
//   bool field: unused

$HudInfoDatasetType::Name = 4;
// string field: the name
//    int field: unused
//  float field: unused
//   bool field: unused

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

   //messageClient(%this, 'MsgClientJoin', '\c2Now leaving the mission area!');
}

function GameConnection::onEnterMissionArea(%this)
{
   // The control objects invoke this method when they
   // move back into the mission area.

   //messageClient(%this, 'MsgClientJoin', '\c2Now entering the mission area.');
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
//-----------------------------------------------------------------------------

function GameConnection::control(%client, %obj)
{
   %client.setControlObject(%obj);
   
   if(%obj.fovDelta !$= "")
      commandToClient(%client, 'SetFovDelta', %obj.fovDelta);
      
   %hud = "CatGui";
   if(%obj.viewHud !$= "")
      %hud = %obj.viewHud;
   commandToClient(%client, 'SetPlayGui', %hud);
   commandToClient(%client, 'CanvasSetContent', %hud);
      
   if(%obj.viewIrisSizeX !$= ""
   || %obj.viewIrisSizeY !$= ""
   || %obj.viewIrisDtX !$= ""
   || %obj.viewIrisDtY !$= "" )
   {
      commandToClient(%client, 'ViewSetIris',
         %obj.viewIrisSizeX,
         %obj.viewIrisDtX,
         %obj.viewIrisSizeY,
         %obj.viewIrisDtY);
   }
      
   if(%obj.viewMotionBlurActive !$= ""
   || %obj.viewMotionBlurVelMul !$= "")
   {
      commandToClient(%client, 'ViewSetMotionBlur',
         %obj.viewMotionBlurActive,
         %obj.viewMotionBlurVelMul
      );
   }
   
   if(%obj.hearingDeafness !$= ""
   || %obj.hearingDeafnessDt !$= "")
   {
      commandToClient(%client, 'HearingSetDeafness',
         %obj.hearingDeafness,
         %obj.hearingDeafnessDt
      );
   }
   
   if(%obj.hearingTinnitusEnabled !$= ""
   || %obj.hearingTinnitusVolume !$= ""
   || %obj.hearingTinnitusVolumeDt !$= "")
   {
      commandToClient(%client, 'HearingSetTinnitus',
         %obj.hearingTinnitusEnabled,
         %obj.hearingTinnitusVolume,
         %obj.hearingTinnitusVolumeDt
      );
   }
   
   if(%obj.getDataBlock().isMethod("onControl"))
      %obj.getDataBlock().onControl(%obj, %client);
}

