// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Function to create the Game object.
// Makes use of theLevelInfo object to determine the game type.
// Returns: The Game object
function gameCoreCreateGame()
{
   if($Server::MissionType $= "")
      $Server::MissionType = "DM"; //Default gametype, just in case

   // Note: The Game object will be cleaned up by MissionCleanup.  Therefore its lifetime is
   // limited to that of the mission.
   new ScriptObject(Game)
   {
      class = "GameCore" @ $Server::MissionType;
      superClass = GameCoreBase;
   };

   return Game;
}

// Called by GameCore::cycleGame() when we need to destroy the server
// because we're done playing.  We don't want to call destroyServer()
// directly so we can first check that we're about to destroy the
// correct server session.
function gameCoreDestroyServer(%serverSession)
{
   if (%serverSession == $Server::Session)
   {
      if (isObject(LocalClientConnection))
      {
         // We're a local connection so issue a disconnect.  The server will
         // be automatically destroyed for us.
         disconnect();
      }
      else
      {
         // We're a stand alone server
         destroyServer();
      }
   }
}

// The GameCore package overides functions loadMissionStage2(), endMission(),
// and function resetMission() from "core/scripts/server/missionLoad.cs" in
// order to create our Game object, which allows our gameType functionality to
// be initiated.

package GameCore
{
   function loadMissionStage2()
   {
      //echo("\c4 -> loadMissionStage2() override success");

      echo("*** Stage 2 load");

      // Create the mission group off the ServerGroup
      $instantGroup = ServerGroup;

      // Make sure the mission exists
      %file = $Server::MissionFile;

      if( !isFile( %file ) )
      {
         $Server::LoadFailMsg = "Could not find mission \"" @ %file @ "\"";
      }
      else
      {
         // Calculate the mission CRC.  The CRC is used by the clients
         // to caching mission lighting.
         $missionCRC = getFileCRC( %file );

         // Exec the mission.  The MissionGroup (loaded components) is added to the ServerGroup
         exec(%file);

         if( !isObject(MissionGroup) )
         {
            $Server::LoadFailMsg = "No 'MissionGroup' found in mission \"" @ %file @ "\".";
         }
      }

      if( $Server::LoadFailMsg !$= "" )
      {
         // Inform clients that are already connected
         for (%clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++)
            messageClient(ClientGroup.getObject(%clientIndex), 'MsgLoadFailed', $Server::LoadFailMsg);
         return;
      }

      // Set mission name.

      if( isObject( theLevelInfo ) )
         $Server::MissionName = theLevelInfo.levelName;

      // Mission cleanup group.  This is where run time components will reside.  The MissionCleanup
      // group will be added to the ServerGroup.
      new SimGroup(MissionCleanup);

      // Make the MissionCleanup group the place where all new objects will automatically be added.
      $instantGroup = MissionCleanup;

      // Create the Game object
      gameCoreCreateGame();

      // Construct MOD paths
      pathOnMissionLoadDone();

      // Mission loading done...
      echo("*** Mission loaded");

      // Start all the clients in the mission
      $missionRunning = true;
      for (%clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++)
         ClientGroup.getObject(%clientIndex).loadMission();

      // Go ahead and launch the mission
      Game.onMissionLoaded();
   }

   function endMission()
   {
      //echo("\c4 -> endMission() override success");

      // If there is no MissionGroup then there is no running mission.
      // It may have already been cleaned up.
      if (!isObject(MissionGroup))
         return;

      echo("*** ENDING MISSION");

      // Inform the game code we're done.
      Game.onMissionEnded();

      // Inform the clients
      for (%clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++)
      {
         // clear ghosts and paths from all clients
         %cl = ClientGroup.getObject(%clientIndex);
         %cl.endMission();
         %cl.resetGhosting();
         %cl.clearPaths();
      }

      // Delete everything
      MissionGroup.delete();
      MissionCleanup.delete();   // Note: Will also clean up the Game object

      // With MissionCleanup gone, make the ServerGroup the default place to put objects
      $instantGroup = ServerGroup;

      clearServerpaths();
   }

   // resetMission() is very game specific.  To get the most out of it you'll
   // need to expand on what is here, such as recreating runtime objects etc.
   function resetMission()
   {
      //echo("\c4 -> resetMission() override success");
      echo("*** MISSION RESET");

      // Remove any temporary mission objects
      // NOTE: This will likely remove any player objects as well so
      // use resetMission() with caution.
      MissionCleanup.delete();
      $instantGroup = ServerGroup;
      new SimGroup(MissionCleanup);
      $instantGroup = MissionCleanup;

      clearServerpaths();

      // Recreate the Game object
      gameCoreCreateGame();

      // Construct MOD paths
      pathOnMissionLoadDone();

      // Allow the Game object to reset the mission
      Game.onMissionReset();
   }

   function GameConnection::prepareMission(%this)
   {
      Game.prepareClient(%this);
   }
   
   function GameConnection::onClientEnterGame(%this)
   {
      Game.onClientEnterGame(%this);
   }

   function GameConnection::onClientLeaveGame(%this)
   {
      // If this mission has ended before the client has left the game then
      // the Game object will have already been cleaned up.  See endMission()
      // in the GameCore package.
      if (isObject(Game))
      {
         Game.onClientLeaveGame(%this);
      }
   }

   // Need to supersede this "core" function in order to properly re-spawn a
   // player after he/she is killed.
   // This will also allow the differing gametypes to more easily have a unique
   // method for spawn handling without needless duplication of code.
   function GameConnection::spawnPlayer(%this, %spawnPoint)
   {
      Game.spawnPlayer(%this, %spawnPoint);
   }

   function endGame()
   {
      Game.endGame();
   }
};
// end of our package... now activate it!
activatePackage(GameCore);

