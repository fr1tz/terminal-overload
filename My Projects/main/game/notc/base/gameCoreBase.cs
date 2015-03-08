// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// ----------------------------------------------------------------------------
// GameCoreBase
// ----------------------------------------------------------------------------
// This is the core of the gametype functionality. The "Default Game". All of
// the gametypes share or over-ride the scripted controls for the default game.
// ----------------------------------------------------------------------------

function GameCoreBase::onAdd(%game)
{
   //echo (%game @"\c4 -> onAdd");
}

function GameCoreBase::onRemove(%game)
{
   //echo (%game @"\c4 -> onRemove");
}

function GameCoreBase::prepareMissionLoad(%game)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> GameCoreBase::prepareMissionLoad");
   
   requiredContent_init();
   
   requiredContent_addFromDataBlocks();
   requiredContent_addFromPattern("content/xa/notc/core/*");
   requiredContent_addFromPattern("content/xa/rotc_hack/*");
   requiredContent_addFromPattern(filePath($Server::MissionFile)@"/*");
   
   %game.zMaterialPaths = "content/xa/notc/core" SPC
      "content/xa/rotc_hack" SPC
      filePath($Server::MissionFile);
      
   %levelInfo = getLevelInfo($Server::MissionFile);
   if(%levelInfo != 0)
   {
      for(%i = 0; %i < 99; %i++)
      {
         if(%levelInfo.dep[%i] !$= "")
            %game.zMaterialPaths = %game.zMaterialPaths SPC %levelInfo.dep[%i];
         else
            break;
      }
      %levelInfo.delete();
   }

   %instantGroupStor = $instantGroup;

   if(!isObject(ServerMaterialsGroup))
   {
      $instantGroup = MissionCleanup;
      new SimGroup(ServerMaterialsGroup);
   }

   $instantGroup = ServerMaterialsGroup;
   
   for(%i = 0; %i < getWordCount(%game.zMaterialPaths); %i++)
   {
      %pathMask = getWord(%game.zMaterialPaths, %i);
      
      echo("Searching for materials for ServerMaterialsGroup:" SPC %pathMask);

      for( %file = findFirstFile( %pathMask @ "/*/materials.cs.dso" );
           %file !$= "";
           %file = findNextFile( %pathMask @ "/*/materials.cs.dso" ))
      {
         // Only execute, if we don't have the source file.
         %csFileName = getSubStr( %file, 0, strlen( %file ) - 4 );
         if(!isFile(%csFileName))
         {
            echo(" Found" SPC %file);
            exec(%file);
         }
      }

      for( %file = findFirstFile( %pathMask @ "/*/materials.cs" );
           %file !$= "";
           %file = findNextFile( %pathMask @ "/*/materials.cs" ))
      {
         echo(" Found" SPC %file);
         requiredContent_addFile(%file);
         exec(%file);
      }
   }
   
   echo("ServerMaterialsGroup has" SPC ServerMaterialsGroup.getCount() SPC "materials.");

   $instantGroup = %instantGroupStor;
   
   requiredContent_addFromMaterials();
   requiredContent_filter();
}

function GameCoreBase::onMissionLoaded(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onMissionLoaded");

   //set up the game and game variables
   %game.initGameVars(%game);

   $Game::Duration = %game.duration;
   $Game::EndGameScore = %game.endgameScore;
   $Game::EndGamePause = %game.endgamePause;

   physicsStartSimulation("server");
   %game.startGame();
}

function GameCoreBase::onMissionEnded(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onMissionEnded");

   // Called by endMission(), right before the mission is destroyed

   // Normally the game should be ended first before the next
   // mission is loaded, this is here in case loadMission has been
   // called directly.  The mission will be ended if the server
   // is destroyed, so we only need to cleanup here.

   physicsStopSimulation("server");
   %game.endGame();

   cancel($Game::Schedule);
   $Game::Running = false;
   $Game::Cycling = false;
}

function GameCoreBase::onMissionReset(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onMissionReset");
}

function GameCoreBase::startGame(%game)
{
   // This is where the game play should start

   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onStartGame");
   if ($Game::Running)
   {
      error("startGame: End the game first!");
      return;
   }
   
   // Keep track of when the game started
   $Game::StartTime = $Sim::Time;

   // Inform the client we're starting up
   for (%clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++)
   {
      %cl = ClientGroup.getObject(%clientIndex);
      commandToClient(%cl, 'GameStart');

      // Other client specific setup..
      %cl.score = 0;
      %cl.kills = 0;
      %cl.deaths = 0;
   }

   // Start the game timer
   if ($Game::Duration)
      $Game::Schedule = %game.schedule($Game::Duration * 1000, "onGameDurationEnd");
   $Game::Running = true;

//    // Start the AI on the specified path
//    AIPlayer::spawn("Path1");
}

function GameCoreBase::endGame(%game, %client)
{
   // This is where the game play should end

   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::endGame");

   if (!$Game::Running)
   {
      error("endGame: No game running!");
      return;
   }

   // Stop any game timers
   cancel($Game::Schedule);

   for (%clientIndex = 0; %clientIndex < ClientGroup.getCount(); %clientIndex++)
   {
      %cl = ClientGroup.getObject(%clientIndex);
      commandToClient(%cl, 'GameEnd', $Game::EndGamePause);
   }

   $Game::Running = false;
}

function GameCoreBase::cycleGame(%game)
{
   if (%game.allowCycling)
   {
      // Cycle to the next mission
      cycleGame();
   }
   else
   {
      // We're done with the whole game
      endMission();
      
      // Destroy server to remove all connected clients after they've seen the
      // end game GUI.
      schedule($Game::EndGamePause * 1000, 0, "gameCoreDestroyServer", $Server::Session);
   }
}

function GameCoreBase::onGameDurationEnd(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onGameDurationEnd");
   if ($Game::Duration && (!EditorIsActive() && !GuiEditorIsActive()))
      %game.cycleGame();
}

// ----------------------------------------------------------------------------
//  Game Setup
// ----------------------------------------------------------------------------

function GameCoreBase::initGameVars(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::initGameVars");

   //-----------------------------------------------------------------------------
   // What kind of "player" is spawned is either controlled directly by the
   // SpawnSphere or it defaults back to the values set here. This also controls
   // which SimGroups to attempt to select the spawn sphere's from by walking down
   // the list of SpawnGroups till it finds a valid spawn object.
   //-----------------------------------------------------------------------------
   $Game::DefaultPlayerClass = "Player";
   $Game::DefaultPlayerDataBlock = "DefaultPlayerData";
   $Game::DefaultPlayerSpawnGroups = "PlayerSpawnPoints";

   //-----------------------------------------------------------------------------
   // What kind of "camera" is spawned is either controlled directly by the
   // SpawnSphere or it defaults back to the values set here. This also controls
   // which SimGroups to attempt to select the spawn sphere's from by walking down
   // the list of SpawnGroups till it finds a valid spawn object.
   //-----------------------------------------------------------------------------
   $Game::DefaultCameraClass = "Camera";
   $Game::DefaultCameraDataBlock = "Observer";
   $Game::DefaultCameraSpawnGroups = "CameraSpawnPoints PlayerSpawnPoints";

   // Set the gameplay parameters
   %game.duration = $Game::Duration;
   %game.endgameScore = $Game::EndGameScore;
   %game.endgamePause = $Game::EndGamePause;
   %game.allowCycling = false;   // Is mission cycling allowed?
}

// ----------------------------------------------------------------------------
//  Client Management
// ----------------------------------------------------------------------------

function GameCoreBase::prepareClient(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::prepareClient");
   
   %client.paletteColors[0] = "125 125 125 255";
   %client.paletteColors[1] = "210 210 210 255";
   
   %game.queryClientSettings(%client, "prepareClient");
   
   %files = "xa/notc/core/client/base/v1/exec" TAB
            "xa/notc/core/client/settings/notc1/exec" TAB
            "xa/notc/core/client/audio/Descriptions/v1/exec" TAB
            "xa/notc/core/client/audio/Hearing/v1/exec" TAB
            "xa/notc/core/client/audio/HitSound/v1/exec" TAB
            "xa/notc/core/client/gui/LoadingGui/v1/exec" TAB
            "xa/notc/core/client/gui/CatHud/v1/exec" TAB
            "xa/notc/core/client/gui/CatGui/v1/exec" TAB
            "xa/notc/core/client/gui/CatGuiSniper/v1/exec" TAB
            "xa/notc/core/client/gui/EtherformGui/v1/exec" TAB
            "xa/notc/core/client/gui/ChatHud/v1/exec" TAB
            "xa/notc/core/client/gui/GuiChanger/v1/exec" TAB
            "xa/notc/core/client/gui/VitalsHud/v1/exec" TAB
            "xa/notc/core/client/gui/MinimapHud/v1/exec" TAB
            "xa/notc/core/client/gui/LoadoutHud/v1/exec" TAB
            "xa/notc/core/client/gui/MiscHud/v1/exec" TAB
            "xa/notc/core/client/gui/HudIcons/v1/exec" TAB
            "xa/notc/core/client/gui/PlayerList/v1/exec" TAB
            "xa/notc/core/client/misc/Commands/v1/exec" TAB
            "xa/notc/core/client/misc/Materials/v1/exec" TAB
            "xa/notc/core/client/postfx/Blur/v1/exec" TAB
            "xa/notc/core/client/postfx/Pixelate/v1/exec" TAB
            "xa/notc/core/client/postfx/ChromaticLens/v1/exec" TAB
            "xa/notc/deathmatch/client/gui/EndGameGui/v1/exec" TAB
            "xa/notc/deathmatch/client/gui/PlayerList/v1/exec";

   %fieldCount = getFieldCount(%files);
   for(%i = 0; %i < %fieldCount; %i++)
   {
      %file = getField(%files, %i);
      commandToClient(%client, 'ExecContentScript', %file);
   }

   %client.Materials_Clear();
   for(%i = 0; %i < getWordCount(%game.zMaterialPaths); %i++)
   {
      %pathMask = getWord(%game.zMaterialPaths, %i);
      %client.Materials_Load(%pathMask);
   }

   // Setup LoadingGui background.
   %background = filePath($Server::MissionFile)@"/mission_preview.png";
   commandToClient(%client, '_XaNotcLoadingGui_SetBackground', %background);
}

function GameCoreBase::onClientEnterGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onClientEntergame");

   commandToClient(%client, 'GameStart');
  	%client.ingame = true;

   // Sync the client's clocks to the server's
   commandToClient(%client, 'SyncClock', $Sim::Time - $Game::StartTime);
   
   // Find a spawn point for the camera
   // This function currently relies on some helper functions defined in
   // core/scripts/server/spawn.cs. For custom spawn behaviors one can either
   // override the properties on the SpawnSphere's or directly override the
   // functions themselves.
   %cameraSpawnPoint = pickCameraSpawnPoint($Game::DefaultCameraSpawnGroups);
   // Spawn a camera for this client using the found %spawnPoint
   %client.spawnCamera(%cameraSpawnPoint);
   
   %client.deathCamera = new Camera() {
      dataBlock = DeathCamera;
      position = "0 0 0 1 0 0 0";
      client = %client;
   };
   %client.deathCamera.scopeToClient(%client);
   
   %client.packetLineCamera = new PathCamera() {
      dataBlock = PacketLineCamera;
      position = "0 0 0 1 0 0 0";
      client = %client;
   };

   // Setup game parameters, the onConnect method currently starts
   // everyone with a 0 score.
   %client.score = 0;
   %client.kills = 0;
   %client.deaths = 0;

   // Inform the client of all the other clients
   %count = ClientGroup.getCount();
   for (%cl = 0; %cl < %count; %cl++)
   {
      %other = ClientGroup.getObject(%cl);
      if ((%other != %client))
      {
         // These should be "silent" versions of these messages...
         messageClient(%client, 'MsgClientJoin', "",
            %other.playerName,
            %other,
            %other.sendGuid,
            %other.team,
            %other.score,
            %other.kills,
            %other.deaths,
            %other.isAIControlled(),
            %other.isAdmin,
            %other.isSuperAdmin);
      }
   }

   // Inform the client we've joined up
   messageClient(%client,
      'MsgClientJoin', '\c2Welcome to Terminal Overload %1.',
      %client.playerName,
      %client,
      %client.sendGuid,
      %client.team,
      %client.score,
      %client.kills,
      %client.deaths,
      %client.isAiControlled(),
      %client.isAdmin,
      %client.isSuperAdmin);

   // Inform all the other clients of the new guy
   messageAllExcept(%client, -1, 'MsgClientJoin', '\c1%1 joined the game.',
      %client.playerName,
      %client,
      %client.sendGuid,
      %client.team,
      %client.score,
      %client.kills,
      %client.deaths,
      %client.isAiControlled(),
      %client.isAdmin,
      %client.isSuperAdmin);
}

function GameCoreBase::onClientLeaveGame(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onClientLeaveGame");

   // Cleanup the cameras
   if(isObject(%client.camera))
      %client.camera.delete();
   if(isObject(%client.deathCamera))
      %client.deathCamera.delete();
      
   // Cleanup the player
   if (isObject(%client.player))
      %client.player.delete();
}

function GameCoreBase::queryClientSettings(%game, %client, %settings)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::queryClientSettings");
   
}

function GameCoreBase::processClientSettingsReply(%game, %client, %setting, %value)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::processClientSettingsReply");
}

function GameCoreBase::clientRecordingDemo(%game, %client, %isRecording)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::clientRecordingDemo");
}

function GameCoreBase::updateClientPlayerList(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::updateClientPlayerList");
}

// Added this stage to creating a player so game types can override it easily.
// This is a good place to initiate team selection.
function GameCoreBase::preparePlayer(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::preparePlayer");

   // Find a spawn point for the player
   // This function currently relies on some helper functions defined in
   // core/scripts/spawn.cs. For custom spawn behaviors one can either
   // override the properties on the SpawnSphere's or directly override the
   // functions themselves.
   %spawnGroups = $Game::DefaultPlayerSpawnGroups;
   if(isObject(%client.team))
   {
      %teamId = %client.team.teamId;
      %spawnGroups = "Team"@%teamId@"SpawnPoints" SPC %spawnGroups;
   }
   %playerSpawnPoint = pickPlayerSpawnPoint(%spawnGroups);
   // Spawn a camera for this client using the found %spawnPoint
   //%client.spawnPlayer(%playerSpawnPoint);
   %game.spawnPlayer(%client, %playerSpawnPoint);
   MissionCleanup.add(%client.player);

   // Starting equipment
   %game.loadOut(%client.player);
}

function GameCoreBase::loadOut(%game, %player)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::loadOut");
}

// Customized kill message for falling deaths
function sendMsgClientKilled_Impact( %msgType, %client, %sourceClient, %damLoc )
{
   messageAll( %msgType, '%1 fell to his death!', %client.playerName );
}

// Customized kill message for suicides
function sendMsgClientKilled_Suicide( %msgType, %client, %sourceClient, %damLoc )
{
   messageAll( %msgType, '%1 takes his own life!', %client.playerName );
}

// Default death message
function sendMsgClientKilled_Default( %msgType, %client, %sourceClient, %damLoc )
{
   if ( %sourceClient == %client )
      sendMsgClientKilled_Suicide(%client, %sourceClient, %damLoc);
   else if ( %sourceClient.team !$= "" && %sourceClient.team $= %client.team )
      messageAll( %msgType, '%1 killed by %2 - friendly fire!', %client.playerName, %sourceClient.playerName );
   else
      messageAll( %msgType, '%1 gets nailed by %2!', %client.playerName, %sourceClient.playerName );
}

function GameCoreBase::onUnitDestroyed(%game, %obj)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onUnitDestroyed");
   %obj.zCalledOnUnitDestroyed = true;
}

// ----------------------------------------------------------------------------
// Scoring
// ----------------------------------------------------------------------------

function GameCoreBase::incKills(%game, %client, %kill, %dontMessageAll)
{
   %client.kills += %kill;
   
   if( !%dontMessageAll )
      messageAll('MsgClientScoreChanged', "", %client.score, %client.kills, %client.deaths, %client);
}

function GameCoreBase::incDeaths(%game, %client, %death, %dontMessageAll)
{
   %client.deaths += %death;

   if( !%dontMessageAll )
      messageAll('MsgClientScoreChanged', "", %client.score, %client.kills, %client.deaths, %client);
}

function GameCoreBase::incScore(%game, %client, %score, %dontMessageAll)
{
   %client.score += %score;

   if( !%dontMessageAll )
      messageAll('MsgClientScoreChanged', "", %client.score, %client.kills, %client.deaths, %client);
}

function GameCoreBase::getScore(%client) { return %client.score; }
function GameCoreBase::getKills(%client) { return %client.kills; }
function GameCoreBase::getDeaths(%client) { return %client.deaths; }

function GameCoreBase::getTeamScore(%client)
{
   %score = %client.score;
   if ( %client.team !$= "" )
   {
      // Compute team score
      for (%i = 0; %i < ClientGroup.getCount(); %i++)
      {
         %other = ClientGroup.getObject(%i);
         if ((%other != %client) && (%other.team $= %client.team))
            %score += %other.score;
      }
   }
   return %score;
}

// ----------------------------------------------------------------------------
// Spawning
// ----------------------------------------------------------------------------

function GameCoreBase::suicide(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::suicide");
   if(isObject(%client.player))
      %client.player.kill("Suicide");
}

function GameCoreBase::etherformManifest(%game, %obj)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::etherformManifest");
}

function GameCoreBase::spawnPlayer(%game, %client, %spawnPoint, %noControl)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::spawnPlayer");

   if (isObject(%client.player))
   {
      // The client should not already have a player. Assigning
      // a new one could result in an uncontrolled player object.
      warn("Creating a player for a client that already has one! Deleting old player.");
      %client.player.delete();
   }

   // Attempt to treat %spawnPoint as an object
   if (getWordCount(%spawnPoint) == 1 && isObject(%spawnPoint))
   {
      // Defaults
      %spawnClass      = $Game::DefaultPlayerClass;
      %spawnDataBlock  = $Game::DefaultPlayerDataBlock;

      // Overrides by the %spawnPoint
      if (isDefined("%spawnPoint.spawnClass"))
      {
         %spawnClass = %spawnPoint.spawnClass;
         %spawnDataBlock = %spawnPoint.spawnDatablock;
      }
      else if (isDefined("%spawnPoint.spawnDatablock"))
      {
         // This may seem redundant given the above but it allows
         // the SpawnSphere to override the datablock without
         // overriding the default player class
         %spawnDataBlock = %spawnPoint.spawnDatablock;
      }

      %spawnProperties = %spawnPoint.spawnProperties;
      %spawnProperties = %spawnProperties SPC "client="@%client@";";
      %spawnScript     = %spawnPoint.spawnScript;

      // Spawn with the engine's Sim::spawnObject() function
      %player = spawnObject(%spawnClass, %spawnDatablock, "",
                            %spawnProperties, %spawnScript);

      // If we have an object do some initial setup
      if (isObject(%player))
      {
         // Pick a location within the spawn sphere.
         %spawnLocation = GameCoreBase::pickPointInSpawnSphere(%player, %spawnPoint);
         %player.setTransform(%spawnLocation);
         
      }
      else
      {
         // If we weren't able to create the player object then warn the user
         // When the player clicks OK in one of these message boxes, we will fall through
         // to the "if (!isObject(%player))" check below.
         if (isDefined("%spawnDatablock"))
         {
               MessageBoxOK("Spawn Player Failed",
                             "Unable to create a player with class " @ %spawnClass @
                             " and datablock " @ %spawnDatablock @ ".\n\nStarting as an Observer instead.",
                             "");
         }
         else
         {
               MessageBoxOK("Spawn Player Failed",
                              "Unable to create a player with class " @ %spawnClass @
                              ".\n\nStarting as an Observer instead.",
                              "");
         }
      }
   }
   else
   {
      
      // Create a default player
      %player = spawnObject($Game::DefaultPlayerClass, $Game::DefaultPlayerDataBlock);
      
      if (!%player.isMemberOfClass("Player"))
         warn("Trying to spawn a class that does not derive from Player.");

      // Treat %spawnPoint as a transform
      %player.setTransform(%spawnPoint);
   }

   // If we didn't actually create a player object then bail
   if (!isObject(%player))
   {
      // Make sure we at least have a camera
      %client.spawnCamera(%spawnPoint);

      return;
   }

   // Update the default camera to start with the player
   if (isObject(%client.camera) && !isDefined("%noControl"))
   {
      if (%player.getClassname() $= "Player")
         %client.camera.setTransform(%player.getEyeTransform());
      else
         %client.camera.setTransform(%player.getTransform());
   }

   // Add the player object to MissionCleanup so that it
   // won't get saved into the level files and will get
   // cleaned up properly
   MissionCleanup.add(%player);
   
   // Default team ID is ID of the client connection.
   %player.teamId = %client.getID();

   // Store the client object on the player object for
   // future reference
   %player.client = %client;
   
   // If the player's client has some owned turrets, make sure we let them
   // know that we're a friend too.
   if (%client.ownedTurrets)
   {
      for (%i=0; %i<%client.ownedTurrets.getCount(); %i++)
      {
         %turret = %client.ownedTurrets.getObject(%i);
         %turret.addToIgnoreList(%player);
      }
   }

   // Player setup...
   if (%player.isMethod("setShapeName"))
      %player.setShapeName(%client.playerName);

   if (%player.isMethod("setEnergyLevel"))
      %player.setEnergyLevel(%player.getDataBlock().maxEnergy);
      
   // Setup view & hearing
   %player.fovDelta = 0;
   %player.viewIrisSizeX = 8;
   %player.viewIrisSizeY = 8;
   %player.viewIrisDtX = 0;
   %player.viewIrisDtY = 0;
   %player.viewMotionBlurActive = false;
   %player.hearingDeafness = 0;
   %player.hearingDeafnessDt = 0;
   %player.hearingTinnitusEnabled = false;
   
   if (!isDefined("%client.skin"))
   {
      // Determine which character skins are not already in use
      %availableSkins = %player.getDatablock().availableSkins;             // TAB delimited list of skin names
      %count = ClientGroup.getCount();
      for (%cl = 0; %cl < %count; %cl++)
      {
         %other = ClientGroup.getObject(%cl);
         if (%other != %client)
         {
            %availableSkins = strreplace(%availableSkins, %other.skin, "");
            %availableSkins = strreplace(%availableSkins, "\t\t", "");     // remove empty fields
         }
      }

      // Choose a random, unique skin for this client
      %count = getFieldCount(%availableSkins);
      %client.skin = addTaggedString( getField(%availableSkins, getRandom(%count)) );
   }

   copyPalette(%client, %player);
   %player.setSkinName(%client.skin);

   // Give the client control of the player
   %client.player = %player;

   // Give the client control of the camera if in the editor
   if( $startWorldEditor )
   {
      %control = %client.camera;
      %control.mode = "Fly";
      EditorGui.syncCameraGui();
   }
   else
      %control = %player;

   // Allow the player/camera to receive move data from the GameConnection.  Without this
   // the user is unable to control the player/camera.
   if (!isDefined("%noControl"))
      %client.control(%control);
}

function GameCoreBase::pickPointInSpawnSphere(%objectToSpawn, %spawnSphere)
{
   %SpawnLocationFound = false;
   %attemptsToSpawn = 0;
   while(!%SpawnLocationFound && (%attemptsToSpawn < 5))
   {
      %sphereLocation = %spawnSphere.getTransform();
      
      // Attempt to spawn the player within the bounds of the spawnsphere.
      %angleY = mDegToRad(getRandom(0, 100) * m2Pi());
      %angleXZ = mDegToRad(getRandom(0, 100) * m2Pi());

      %sphereLocation = setWord( %sphereLocation, 0, getWord(%sphereLocation, 0) + (mCos(%angleY) * mSin(%angleXZ) * getRandom(-%spawnSphere.radius, %spawnSphere.radius)));
      %sphereLocation = setWord( %sphereLocation, 1, getWord(%sphereLocation, 1) + (mCos(%angleXZ) * getRandom(-%spawnSphere.radius, %spawnSphere.radius)));
      
      %SpawnLocationFound = true;

      // Now have to check that another object doesn't already exist at this spot.
      // Use the bounding box of the object to check if where we are about to spawn in is
      // clear.
      %boundingBoxSize = %objectToSpawn.getDatablock().boundingBox;
      %searchRadius = getWord(%boundingBoxSize, 0);
      %boxSizeY = getWord(%boundingBoxSize, 1);
      
      // Use the larger dimention as the radius to search
      if (%boxSizeY > %searchRadius)
         %searchRadius = %boxSizeY;
         
      // Search a radius about the area we're about to spawn for players.
      initContainerRadiusSearch( %sphereLocation, %searchRadius, $TypeMasks::PlayerObjectType );
      while ( (%objectNearExit = containerSearchNext()) != 0 )
      {
         // If any player is found within this radius, mark that we need to look
         // for another spot.
         %SpawnLocationFound = false;
         break;
      }
         
      // If the attempt at finding a clear spawn location failed
      // try no more than 5 times.
      %attemptsToSpawn++;
   }
      
   // If we couldn't find a spawn location after 5 tries, spawn the object
   // At the center of the sphere and give a warning.
   if (!%SpawnLocationFound)
   {
      %sphereLocation = %spawnSphere.getTransform();
      warn("WARNING: Could not spawn player after" SPC %attemptsToSpawn 
      SPC "tries in spawnsphere" SPC %spawnSphere SPC "without overlapping another player. Attempting spawn in center of sphere.");
   }
   
   return %sphereLocation;
}

// ----------------------------------------------------------------------------
// Observer
// ----------------------------------------------------------------------------

function GameCoreBase::spawnObserver(%game, %client)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::spawnObserver");

   // Position the camera on one of our observer spawn points
   %client.camera.setTransform(%game.pickObserverSpawnPoint());

   // Set control to the camera
   %client.setControlObject(%client.camera);
}

function GameCoreBase::pickObserverSpawnPoint(%game)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::pickObserverSpawnPoint");

   %groupName = "MissionGroup/ObserverSpawnPoints";
   %group = nameToID(%groupName);

   if (%group != -1)
   {
      %count = %group.getCount();
      if (%count != 0)
      {
         %index = getRandom(%count-1);
         %spawn = %group.getObject(%index);
         return %spawn.getTransform();
      }
      else
         error("No spawn points found in "@ %groupName);
   }
   else
      error("Missing spawn points group "@ %groupName);

   // Could be no spawn points, in which case we'll stick the
   // player at the center of the world.
   return "0 0 300 1 0 0 0";
}

function GameCoreBase::F(%game, %client, %nr)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::F");
}

function GameCoreBase::onZoneOwnerChanged(%game, %zone)
{
   //echo (%game @"\c4 -> "@ %game.class @" -> GameCoreBase::onZoneOwnerChanged");
}
