// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function onServerCreated()
{
   // Server::GameType is sent to the master server.
   // This variable should uniquely identify your game and/or mod.
   $Server::GameType = $appName;

   // Server::MissionType sent to the master server.  Clients can
   // filter servers based on mission type.
   $Server::MissionType = "DM";

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
   %datablockFiles.add( "content/xa/torque3d/3.0/forest/managedItemData.cs" );
   %datablockFiles.add( "content/xa/torque3d/3.0/datablocks/datablockExec.cs" );   
   loadDatablockFiles( %datablockFiles, true );

   exec("./dm/exec.cs");
}

function onServerDestroyed()
{
   // This function is called as part of a server shutdown.

   physicsDestroyWorld( "server" );

   // Clean up the GameCore package here as it persists over the
   // life of the server.
   if (isPackage(GameCore))
   {
      deactivatePackage(GameCore);
   }
}
