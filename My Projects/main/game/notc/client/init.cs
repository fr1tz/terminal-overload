// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Variables used by client scripts & code.  The ones marked with (c)
// are accessed from code.  Variables preceeded by Pref:: are client
// preferences and stored automatically in the ~/client/prefs.cs file
// in between sessions.
//
//    (c) Client::MissionFile             Mission file name
//    ( ) Client::Password                Password for server join

//    (?) Pref::Player::CurrentFOV
//    (?) Pref::Player::DefaultFov
//    ( ) Pref::Input::KeyboardTurnSpeed

//    (c) pref::Master[n]                 List of master servers
//    (c) pref::Net::RegionMask
//    (c) pref::Client::ServerFavoriteCount
//    (c) pref::Client::ServerFavorite[FavoriteCount]
//    .. Many more prefs... need to finish this off

// Moves, not finished with this either...
//    (c) firstPerson
//    $mv*Action...

//-----------------------------------------------------------------------------
// These are variables used to control the shell scripts and
// can be overriden by mods:
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
function initClient()
{
   echo("\n--------- Initializing " @ $appName @ ": Client Scripts ---------");
   
   // Set actual window title.
   if(isObject(Canvas))
      Canvas.setWindowTitle($appName @ " (" @ $GameVersionString @ ")");

   // Make sure this variable reflects the correct state.
   $Server::Dedicated = false;

   // Game information used to query the master server
   $Client::GameTypeQuery = "Any";
   $Client::MissionTypeQuery = "Any";

   // These should be game specific GuiProfiles.  Custom profiles are saved out
   // from the Gui Editor.  Either of these may override any that already exist.
   exec("notc/client/shell/defaultGameProfiles.cs");
   exec("notc/client/shell/customProfiles.cs");
   
   // The common module provides basic client functionality
   initBaseClient();

   // Use our prefs to configure our Canvas/Window
   configureCanvas();

   // Load up the Game GUIs
   exec("notc/client/shell/defaultGameProfiles.cs");
   exec("notc/client/shell/hudlessGui.gui");

   // Gui scripts
   exec("notc/client/shell/hilight.cs");
   exec("notc/client/shell/mainMenuGui.cs");
   exec("notc/client/shell/startupGui.cs");
   exec("notc/client/shell/chooseLevelDlg.cs");
   exec("notc/client/shell/loadingGui.cs");
   exec("notc/client/shell/optionsDlg.cs");
   exec("notc/client/shell/optPlayer.cs");
   exec("notc/client/shell/optGraphics.cs");
   exec("notc/client/shell/optAudio.cs");
   exec("notc/client/shell/optGame.cs");
   exec("notc/client/shell/motdDlg.cs");
   exec("notc/client/shell/ingameMenuDlg.cs");

   // Load up the shell GUIs
   exec("notc/client/shell/mainMenuGui.gui");
   exec("notc/client/shell/recordingsDlg.gui");
   exec("notc/client/shell/joinServerDlg.gui");
   exec("notc/client/shell/StartupGui.gui");
   exec("notc/client/shell/chooseLevelDlg.gui");
   exec("notc/client/shell/loadingGui.gui");
   exec("notc/client/shell/optionsDlg.gui");
   exec("notc/client/shell/optPlayer.gui");
   exec("notc/client/shell/optGraphics.gui");
   exec("notc/client/shell/optAudio.gui");
   exec("notc/client/shell/optGame.gui");
   exec("notc/client/shell/motdDlg.gui");
   exec("notc/client/shell/ingameMenuDlg.gui");

   // Client scripts
   exec("./client.cs");
   exec("./missionDownload.cs");
   exec("./serverConnection.cs");
   
   loadAutoexec("ClientInit");

   // Really shouldn't be starting the networking unless we are
   // going to connect to a remote server, or host a multi-player
   // game.
   setNetPort(0);

   // Copy saved script prefs into C++ code.
   setDefaultFov( $pref::Player::defaultFov );
   setZoomSpeed( $pref::Player::zoomSpeed );

   if( isFile( "./audioData.cs" ) )
      exec( "./audioData.cs" );

   // Start up the main menu... this is separated out into a
   // method for easier mod override.

   if ($startWorldEditor || $startGUIEditor) {
      // Editor GUI's will start up in the primary main.cs once
      // engine is initialized.
      return;
   }

   // Connect to server if requested.
   if ($JoinGameAddress !$= "") {
      // If we are instantly connecting to an address, load the
      // loading GUI then attempt the connect.
      loadLoadingGui();
      connect($JoinGameAddress, "", $Pref::Player::Name);
   }
   else {
      // Otherwise go to the splash screen.
      Canvas.setCursor("DefaultCursor");
      loadMainMenu();
   }   
}


//-----------------------------------------------------------------------------

function loadMainMenu()
{
   // Startup the client with the Main menu...
   if (isObject( MainMenuGui ))
      Canvas.setContent( MainMenuGui );
   
   Canvas.setCursor("DefaultCursor");

   // first check if we have a level file to load
   if ($levelToLoad !$= "")
   {
      %levelFile = "levels/";
      %ext = getSubStr($levelToLoad, strlen($levelToLoad) - 3, 3);
      if(%ext !$= "mis")
         %levelFile = %levelFile @ $levelToLoad @ ".mis";
      else
         %levelFile = %levelFile @ $levelToLoad;

      // Clear out the $levelToLoad so we don't attempt to load the level again
      // later on.
      $levelToLoad = "";
      
      // let's make sure the file exists
      %file = findFirstFile(%levelFile);

      if(%file !$= "")
         createAndConnectToLocalServer( "SinglePlayer", %file );
   }
}

function loadLoadingGui(%displayText)
{
   Canvas.setContent("LoadingGui");
   LoadingProgress.setValue(1);

   if (%displayText !$= "")
   {
      LoadingProgressTxt.setValue(%displayText);
   }
   else
   {
      LoadingProgressTxt.setValue("WAITING FOR SERVER");
   }

   Canvas.repaint();
}
