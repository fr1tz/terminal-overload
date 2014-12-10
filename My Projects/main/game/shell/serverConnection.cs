// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Functions dealing with connecting to a server


//-----------------------------------------------------------------------------
// Server connection error
//-----------------------------------------------------------------------------

addMessageCallback( 'MsgConnectionError', handleConnectionErrorMessage );

function handleConnectionErrorMessage(%msgType, %msgString, %msgError)
{
   // On connect the server transmits a message to display if there
   // are any problems with the connection.  Most connection errors
   // are game version differences, so hopefully the server message
   // will tell us where to get the latest version of the game.
   $ServerConnectionErrorMessage = %msgError;
}


//----------------------------------------------------------------------------
// GameConnection client callbacks
//----------------------------------------------------------------------------

function GameConnection::initialControlSet(%this)
{
   echo ("*** Initial Control Object");

   // The first control object has been set by the server
   // and we are now ready to go.
   
   // first check if the editor is active
   if (!isToolBuild() || !Editor::checkActiveLoadDone())
   {
      if (Canvas.getContent() != $PlayGui.getId())
      {
         Canvas.setContent($PlayGui);
      }
   }
}

function GameConnection::onControlObjectChange(%this)
{
   echo ("*** Control Object Changed");
   
   // Reset the current FOV to match the new object
   // and turn off any current zoom.
   resetCurrentFOV();
   turnOffZoom();
   
   // Use instant input unless we're playing back a recording
   %control = %this.getControlObject();
   if(isObject(%control) && !%this.isDemoPlaying())
      %control.instantInput_init(true);
}

function GameConnection::setLagIcon(%this, %state)
{
   if (%this.getAddress() $= "local")
      return;
   LagIcon.setVisible(%state $= "true");
}

function GameConnection::onFlash(%this, %state)
{
   if (isObject(FlashFx))
   {
      if (%state)
      {
         FlashFx.enable();
      }
      else
      {
         FlashFx.disable();
      }
   }
}

// Called on the new connection object after connect() succeeds.
function GameConnection::onConnectionAccepted(%this)
{
   // Called on the new connection object after connect() succeeds.
   LagIcon.setVisible(false);
   
   // Startup the physics world on the client before any
   // datablocks and objects are ghosted over.
   physicsInitWorld( "client" );   
}

function GameConnection::onConnectionTimedOut(%this)
{
   // Called when an established connection times out
   disconnectedCleanup();
   MessageBoxOK( "TIMED OUT", "The server connection has timed out.");
}

function GameConnection::onConnectionDropped(%this, %msg)
{
   // Established connection was dropped by the server
   disconnectedCleanup();
   MessageBoxOK( "DISCONNECT", "The server has dropped the connection: " @ %msg);
}

function GameConnection::onConnectionError(%this, %msg)
{
   // General connection error, usually raised by ghosted objects
   // initialization problems, such as missing files.  We'll display
   // the server's connection error message.
   disconnectedCleanup();
   MessageBoxOK( "DISCONNECT", $ServerConnectionErrorMessage @ " (" @ %msg @ ")" );
}


//----------------------------------------------------------------------------
// Connection Failed Events
//----------------------------------------------------------------------------

function GameConnection::onConnectRequestRejected( %this, %msg )
{
   switch$(%msg)
   {
      case "CR_INVALID_PROTOCOL_VERSION":
         %error = "Incompatible protocol version: Your game version is not compatible with this server.";
      case "CR_INVALID_CONNECT_PACKET":
         %error = "Internal Error: badly formed network packet";
      case "CR_YOUAREBANNED":
         %error = "You are not allowed to play on this server.";
      case "CR_SERVERFULL":
         %error = "This server is full.";
      case "CHR_PASSWORD":
         // XXX Should put up a password-entry dialog.
         if ($Client::Password $= "")
            MessageBoxOK( "REJECTED", "That server requires a password.");
         else {
            $Client::Password = "";
            MessageBoxOK( "REJECTED", "That password is incorrect.");
         }
         return;
      case "CHR_PROTOCOL":
         %error = "Incompatible protocol version: Your game version is not compatible with this server.";
      case "CHR_CLASSCRC":
         %error = "Incompatible game classes: Your game version is not compatible with this server.";
      case "CHR_INVALID_CHALLENGE_PACKET":
         %error = "Internal Error: Invalid server response packet";
      default:
         %error = "Connection error.  Please try another server.  Error code: (" @ %msg @ ")";
   }
   disconnectedCleanup();
   MessageBoxOK( "REJECTED", %error);
}

function GameConnection::onConnectRequestTimedOut(%this)
{
   disconnectedCleanup();
   MessageBoxOK( "TIMED OUT", "Your connection to the server timed out." );
}


//-----------------------------------------------------------------------------
// Disconnect
//-----------------------------------------------------------------------------

function disconnect()
{
   // We need to stop the client side simulation
   // else physics resources will not cleanup properly.
   physicsStopSimulation( "client" );

   // Delete the connection if it's still there.
   if (isObject(ServerConnection))
      ServerConnection.delete();
      
   disconnectedCleanup();

   // Call destroyServer in case we're hosting
   destroyServer();
}

function disconnectedCleanup()
{
   // End mission, if it's running.
   
   if( $Client::missionRunning )
      clientEndMission();
      
   // Disable mission lighting if it's going, this is here
   // in case we're disconnected while the mission is loading.
   
   $lightingMission = false;
   $sceneLighting::terminateLighting = true;
   
   // Clear misc script stuff
   HudMessageVector.clear();
   
   //
   LagIcon.setVisible(false);
   PlayerListGui.clear();
   
   // Clear all print messages
   clientCmdclearBottomPrint();
   clientCmdClearCenterPrint();

   // Back to the launch screen
   if (isObject( MainMenuGui ))
      Canvas.setContent( MainMenuGui );

   // Before we destroy the client physics world
   // make sure all ServerConnection objects are deleted.
   if(isObject(ServerConnection))
   {
      ServerConnection.deleteAllObjects();
   }
   
   // We can now delete the client physics simulation.
   physicsDestroyWorld( "client" );                 
}

//----------------------------------------------------------------------------
// Helper functions
//----------------------------------------------------------------------------

function cGetPlayerName()
{
   if($Pref::AIMS::Enabled)
      return $Pref::AIMS::PlayerName;
   else
      return $Pref::Player::Name;
}

function cGetAuthAlgs()
{
   if($Pref::AIMS::Enabled)
      return "aims/playerdb/auth.1";
   else
      return "";
}

function connect(%server)
{
   %conn = new GameConnection(ServerConnection);
   RootGroup.add(ServerConnection);
   %conn.setConnectArgs(cGetPlayerName(), cGetAuthAlgs());
   %conn.setJoinPassword($Client::Password);
   %conn.connect(%server);
}

