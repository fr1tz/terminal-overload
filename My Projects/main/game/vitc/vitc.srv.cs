// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------

// Variables used by server scripts & code.  The ones marked with (c)
// are accessed from code.  Variables preceeded by Pref:: are server
// preferences and stored automatically in the ServerPrefs.cs file
// in between server sessions.
//
//    (c) Server::ServerType              {SinglePlayer, MultiPlayer}
//    (c) Server::GameType                Unique game name
//    (c) Server::Dedicated               Bool
//    ( ) Server::MissionFile             Mission .mis file name
//    (c) Server::MissionName             DisplayName from .mis file
//    (c) Server::MissionType             Not used
//    (c) Server::PlayerCount             Current player count
//    (c) Server::GuidList                Player GUID (record list?)
//    (c) Server::Status                  Current server status
//
//    (c) Pref::Server::Name              Server Name
//    (c) Pref::Server::Password          Password for client connections
//    ( ) Pref::Server::AdminPassword     Password for client admins
//    (c) Pref::Server::Info              Server description
//    (c) Pref::Server::MaxPlayers        Max allowed players
//    (c) Pref::Server::RegionMask        Registers this mask with master server
//    ( ) Pref::Server::BanTime           Duration of a player ban
//    ( ) Pref::Server::KickBanTime       Duration of a player kick & ban
//    ( ) Pref::Server::MaxChatLen        Max chat message len
//    ( ) Pref::Server::FloodProtectionEnabled Bool

//-----------------------------------------------------------------------------

function destroyServer()
{
   if(isObject($Server::RequiredContent))
      $Server::RequiredContent.delete();
   $Server::ServerType = "";
   allowConnections(false);
   stopHeartbeat();
   sAuthStop();
   $missionRunning = false;

   // End any running levels
   endMission();
   
   physicsDestroyWorld( "server" );

   // Clean up the GameCore package here as it persists over the
   // life of the server.
   if (isPackage(GameCore))
   {
      deactivatePackage(GameCore);
   }

   // Delete all the server objects
   if (isObject(ServerGroup))
      ServerGroup.delete();

   // Delete all the connections:
   while (ClientGroup.getCount())
   {
      %client = ClientGroup.getObject(0);
      %client.delete();
   }

   $Server::GuidList = "";

   // Delete all the data blocks...
   deleteDataBlocks();

   // Save any server settings
   echo( "Exporting server prefs and banlist..." );
   export( "$Pref::Server::*", $SettingsDir@"/vitc.srv.prefs.cs", false );
   BanList::Export($SettingsDir@"/vitc.srv.banlist.cs");

   // Increase the server session number.  This is used to make sure we're
   // working with the server session we think we are.
   $Server::Session++;
}

function createServer(%gameType, %args)
{
   // Server::GameType is sent to the master server.
   // This variable should uniquely identify your game and/or mod.
   $Server::GameType = "VITC" SPC "\c1" @ $GameVersionString;
   
   // Server::Status is returned in the Game Info Query and represents the
   // current status of the server. This string sould be very short.
   $Server::Status = "Unknown";
   
   // Turn on testing/debug script functions
   $Server::TestCheats = false;

   // Specify where the mission files are.
   $Server::MissionFileSpec = "content/*.mis";
   
   %serverType = "MultiPlayer";
   %mode = "ETH";
   %map = "eth1";
   %prefs = "";
   
   $Server::VITC::Mutator::AS = false;
   $Server::VITC::Mutator::AM = false;
   $Server::VITC::Mutator::VAMP = false;
   
   // Parse arguments.
   for(%i = 0; %i < getWordCount(%args); %i++)
   {
      %arg = getWord(%args, %i);
      switch$(%arg)
      {
         case "-sp":
            %serverType = "SinglePlayer";

         case "-mode":
            %nextarg = getWord(%args, %i+1);
            if(%nextarg !$= "")
            {
               %mode = strupr(%nextarg);
               %map = strlwr(%nextarg) @ "1";
            }
               
         case "-map":
            %nextarg = getWord(%args, %i+1);
            if(%nextarg !$= "")
               %map = %nextarg;
               
         case "-srvprefs":
            %nextarg = getWord(%args, %i+1);
            if(%nextarg !$= "")
               %prefs = %nextarg;
               
         case "-as":
            $Server::VITC::Mutator::AS = true;
            
         case "-am":
            $Server::VITC::Mutator::AM = true;
            
         case "-vamp":
            $Server::VITC::Mutator::VAMP = true;
            
         case "-advanced":
            $Server::VITC::Mutator::AS = true;
            $Server::VITC::Mutator::AM = true;
            $Server::VITC::Mutator::VAMP = true;
      }
   }
   
   $Server::VITC::MutatorList = "";
   if($Server::VITC::Mutator::AS)
      $Server::VITC::MutatorList = $Server::VITC::MutatorList SPC "AS";
   if($Server::VITC::Mutator::AM)
      $Server::VITC::MutatorList = $Server::VITC::MutatorList SPC "AM";
   if($Server::VITC::Mutator::VAMP)
      $Server::VITC::MutatorList = $Server::VITC::MutatorList SPC "VAMP";
   $Server::VITC::MutatorList = trim($Server::VITC::MutatorList);
   
   if($Server::VITC::MutatorList $= "")
      $Server::GameType = $Server::GameType SPC "\c2Casual";
   else if($Server::VITC::MutatorList $= "AS AM VAMP")
      $Server::GameType = $Server::GameType SPC "\c5Advanced";
   else
      $Server::GameType = $Server::GameType SPC "\c6Variant";

   %modeVariant = "";
   if($Server::VITC::MutatorList $= "AS AM VAMP")
   {
      %modeVariant = "(Advanced)";
   }
   else if(getWordCount($Server::VITC::MutatorList) == 1)
   {
      if($Server::VITC::MutatorList $= "AS")
         %modeVariant = "(Advanced Shooting)";
      else if($Server::VITC::MutatorList $= "AM")
         %modeVariant = "(Advanced Movement)";
      else if($Server::VITC::MutatorList $= "VAMP")
         %modeVariant = "(V-AMP)";
   }
   else if(getWordCount($Server::VITC::MutatorList) >= 2)
   {
      %modeVariant = "(Multiple Mutators)";
   }

   // The common module provides the basic server functionality
   exec("./common/exec.cs");
   
   exec("./defaults.cs");
   if(isFile(%prefs))
      exec(%prefs);

   // GameStartTime is the sim time the game started. Used to calculated
   // game elapsed time.
   $Game::StartTime = 0;

   // Create the server physics world.
   physicsInitWorld( "server" );

   // Load up any core datablocks
   exec("core/art/datablocks/datablockExec.cs");

   // Load up any objects or datablocks saved to the editor managed scripts
   %datablockFiles = new ArrayObject();
   %datablockFiles.add( "content/cleanup/particleData.cs" );
   %datablockFiles.add( "content/cleanup/particleEmitterData.cs" );
   %datablockFiles.add( "content/cleanup/decalData.cs" );
   %datablockFiles.add( "content/cleanup/datablocks.cs" );
   %datablockFiles.add( "content/cleanup/managedItemData.cs" );
   loadDatablockFiles( %datablockFiles, true );

   $Server::VITC::Mode = %mode;
   $Server::VITC::Prefs = %prefs;

   // Load up game mode scripts
   switch$(%mode)
   {
      case "DM":
         $Server::MissionType = "Deathmatch";
         exec("./dm/exec.cs");
      case "ETH":
         $Server::MissionType = "Tactical Ethernet";
         exec("./eth/exec.cs");
      case "TE":
         $Server::MissionType = "Team Elimination";
         exec("./TE/exec.cs");
      case "CTF":
         $Server::MissionType = "Capture The Flag";
         exec("./ctf/exec.cs");
   }
   
   $Server::MissionType = $Server::MissionType SPC %modeVariant;
   
   %level = "content/vitc/mis/" @ %map @ "/mission.mis";

   // Make sure our level name is relative so that it can send
   // across the network correctly
   %level = makeRelativePath(%level, getWorkingDirectory());

   // Extract mission info from the mission file,
   // including the display name and stuff to send
   // to the client.
   buildLoadInfo(%level);

   if(!isObject(theLevelInfo))
   {
      error("createServer(): no level info");
      return false;
   }

   $missionSequence = 0;
   $Server::PlayerCount = 0;
   $Server::ServerType = %serverType;
   $Server::LoadFailMsg = "";
   $Physics::isSinglePlayer = true;

   // Setup for multi-player, the network must have been
   // initialized before now.
   if (%serverType $= "MultiPlayer")
   {
      $Physics::isSinglePlayer = false;

      echo("Starting multiplayer mode");

      // Make sure the network port is set to the correct pref.
      portInit($Pref::Server::Port);
      allowConnections(true);

      if ($pref::Net::DisplayOnMaster !$= "Never" )
         schedule(0,0,startHeartbeat);
   }

   // Start player authentication facilities
   schedule(0, 0, sAuthStart);

   // Create the ServerGroup that will persist for the lifetime of the server.
   new SimGroup(ServerGroup);
   
   // Create the ControllerGroup and add it to the ServerGroup
   new SimGroup(ControllerGroup);
   ServerGroup.add(ControllerGroup);

   loadMission(%level, true);

   return true;
}

function resetServerDefaults()
{
   echo( "Resetting server defaults..." );
   
   exec( "./defaults.cs" );
   if(isFile($Server::VITC::Prefs))
      exec($Server::VITC::Prefs);

   // Reload the current level
   loadMission( $Server::MissionFile );
}

