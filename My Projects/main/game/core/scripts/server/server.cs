// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/// Attempt to find an open port to initialize the server with
function portInit(%port)
{
   %failCount = 0;
   while(%failCount < 10 && !setNetPort(%port))
   {
      echo("Port init failed on port " @ %port @ " trying next port.");
      %port++; %failCount++;
   }
}

function startServer(%gameType, %args)
{
   %serverScriptFileName = %gameType @ ".srv.cs";
   %serverScriptFilePath = findFirstFile("*/" @ %serverScriptFileName);

   if(%serverScriptFilePath $= "")
   {
      error("Unable to find server script file '" @ %serverScriptFileName @
         "' for game type '" @ %gameType @ "'!");
      return false;
   }
   
   // Shut down existing server.
   if(isFunction("destroyServer"))
      destroyServer();
   
   echo("Executing server script file:" SPC %serverScriptFilePath);
   exec(%serverScriptFilePath);
   
   echo("Checking if required basic server functions exist...");
   %createServer = true;
   %serverfuncs = "createServer destroyServer resetServerDefaults";
   for(%i = 0; %i < getWordCount(%serverfuncs); %i++)
   {
      %funcName = getWord(%serverfuncs, %i);
      if(!isFunction(%funcName))
      {
         error(" function" SPC %funcName SPC "is missing!");
         %createServer = false;
      }
      else
         echo(" function" SPC %funcName SPC "exists.");
   }
   
   if(!%createServer)
   {
      error("Unable to create server!");
      return false;
   }
   
   // Increase the server session number.  This is used to make sure we're
   // working with the server session we think we are.
   $Server::Session++;
   
   return createServer(%gameType, %args);
}

/// Run a server and create a local client connection to the server.
/// @return true if successful.
function startAndConnectToLocalServer(%gameType, %args)
{
   if(!startServer(%gameType, %args))
      return false;
   
   %conn = new GameConnection( ServerConnection );
   RootGroup.add( ServerConnection );

   %conn.setConnectArgs(cGetPlayerName(), cGetAuthAlgs());
   %conn.setJoinPassword( $Client::Password );
   
   %result = %conn.connectLocal();
   if( %result !$= "" )
   {
      %conn.delete();
      destroyServer();
      
      return false;
   }

   return true;
}



/// Guid list maintenance functions
function addToServerGuidList( %guid )
{
   %count = getFieldCount( $Server::GuidList );
   for ( %i = 0; %i < %count; %i++ )
   {
      if ( getField( $Server::GuidList, %i ) == %guid )
         return;
   }

   $Server::GuidList = $Server::GuidList $= "" ? %guid : $Server::GuidList TAB %guid;
}

function removeFromServerGuidList( %guid )
{
   %count = getFieldCount( $Server::GuidList );
   for ( %i = 0; %i < %count; %i++ )
   {
      if ( getField( $Server::GuidList, %i ) == %guid )
      {
         $Server::GuidList = removeField( $Server::GuidList, %i );
         return;
      }
   }
}

/// When the server is queried for information, the value of this function is
/// returned as the status field of the query packet.  This information is
/// accessible as the ServerInfo::State variable.
function onServerInfoQuery()
{
   return "Doing Ok";
}
