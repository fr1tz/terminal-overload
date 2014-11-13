// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Load up core script base
loadDir("core"); // Should be loaded at a higher level, but for now leave -- SRZ 11/29/07

//-----------------------------------------------------------------------------
// Package overrides to initialize the mod.
package Shell {

function displayHelp() {
   Parent::displayHelp();
   error(
      "Shell options:\n"@
      "  -dedicated <game>      Start a dedicated server for game <game>\n"@
      "  -connect <address>     For non-dedicated: Connect to a game at <address>\n"
   );
}

function parseArgs()
{
   // Call the parent
   Parent::parseArgs();

   // Arguments, which override everything else.
   for (%i = 1; %i < $Game::argc ; %i++)
   {
      %arg = $Game::argv[%i];
      %nextArg = $Game::argv[%i+1];
      %hasNextArg = $Game::argc - %i > 1;
   
      switch$ (%arg)
      {
         //--------------------
         case "-dedicated":
            $argUsed[%i]++;
            $Server::Dedicated = true;
            enableWinConsole(true);
            if (%hasNextArg) {
               $dedicatedArg = %nextArg;
               $argUsed[%i+1]++;
               %i++;
            }

         //--------------------
         case "-connect":
            $argUsed[%i]++;
            if (%hasNextArg) {
               $JoinGameAddress = %nextArg;
               $argUsed[%i+1]++;
               %i++;
            }
            else
               error("Error: Missing Command Line argument. Usage: -connect <ip_address>");
      }
   }
}

function onStart()
{
   // The core does initialization which requires some of
   // the preferences to loaded... so do that first.  
   exec( "./defaults.cs" );

   Parent::onStart();
   echo("\n--------- Initializing Directory: scripts ---------");

   // Load the script that starts it all...
   exec("./init.cs");

   // Init the physics plugin.
   physicsInit();
      
   // Start up the audio system.
   sfxStartup();

   $SB::WODec = 0.04; // FIXME: find better place for this

   // Start up in either client, or dedicated server mode
   if($Server::Dedicated)
      initDedicated();
   else
      initGUI();
}

function onExit()
{
   // Ensure that we are disconnected and/or the server is destroyed.
   // This prevents crashes due to the SceneGraph being deleted before
   // the objects it contains.
   if ($Server::Dedicated)
      destroyServer();
   else
      disconnect();
   
   // Destroy the physics plugin.
   physicsDestroy();
      
   echo("Exporting client prefs");
   export("$pref::*", $SettingsDir@"/prefs.cs", False);

   echo("Exporting server prefs");
   export("$Pref::Server::*", "notc/prefs.cs", False);
   BanList::Export("notc/banlist.cs");

   Parent::onExit();
}

}; // package Shell

// Activate the game package.
activatePackage(Shell);
