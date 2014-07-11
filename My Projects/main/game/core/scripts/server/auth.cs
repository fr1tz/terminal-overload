// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// called by script
function sAuthStart()
{
   if(!isObject(sAimsAuthConn))
   {
      new TCPObject(sAimsAuthConn);
      sAimsAuthConn.reset();
   }
}

// called by script
function sAuthStop()
{
   if(isObject(sAimsAuthConn))
      sAimsAuthConn.delete();
}

// called by script
function sAimsAuthConn::reset(%this)
{
   %this.ready = false;
   %this.connect($Pref::AIMS::Server[0] @ ":28003");
}

// called by script
function sAimsAuthConn::processAuth(%this)
{
   if(!%this.ready)
      return;

   %count = ClientGroup.getCount();
   for(%idx = 0; %idx < %count; %idx++)
   {
      %client = ClientGroup.getObject(%idx);
      if(%client.authStage == 2)
      {
         %this.send(
            %client SPC
            %client.authPlayerId SPC
            %client.authHash SPC
            $Pref::Server::Name SPC
            %client.authServerName SPC
            %client.authClientTime SPC
            %client.authServerTime SPC
            %client.authClientRand SPC
            %client.authServerRand @ "\n"
         );
         %client.authStage = 3;
      }
   }
}

// called by engine
function sAimsAuthConn::onLine(%this, %line)
{
   echo("sAimsAuthConn::onLine():" SPC %line);

   if(%line $= "ready")
   {
      %this.ready = true;
      %this.processAuth();
      return;
   }

   %client = getWord(%line, 0);
   if(!isObject(%client) || %client.authStage != 3)
   {
      error("sAimsAuthConn::onLine(): received invalid line:" SPC %line);
      return;
   }

   %msg = getWords(%line, 1);
   if(getWord(%msg, 0) $= "player:")
   {
      %client.playerName = getWords(%msg, 1);
      messageAll(
         'MsgClientAuth',
         '\c2The server has authenticated a new player as %1 via the AIMS player database (aims.wasted.ch).',
         %client.playerName
      );
      %client.onAuthComplete();
   }
   else
   {
      %client.schedule(0, "delete", "Auth failed:" SPC %msg);
   }
   %client.authStage = 0;
}

// called by engine
function sAimsAuthConn::onConnected(%this)
{
   //error("sAimsAuthConn::onConnected()");
   %this.send("playerdb/auth.1\n");
}

// called by engine
function sAimsAuthConn::onConnectFailed(%this)
{
   error("sAimsAuthConn: Connection to" SPC $Pref::AIMS::Server[0] @ ":28003 failed!");
   %this.onDisconnect();
}

// called by engine
function sAimsAuthConn::onDisconnect(%this)
{
   error("sAimsAuthConn::onDisconnect()");
   error("sAimsAuthConn: Trying to reconnect in 5 seconds");
   %this.schedule(5000, "reset");
}

