// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Authentication challenge
function clientCmdAuthChallenge(%alg, %arg1, %arg2, %arg3, %arg4, %arg5, %arg6)
{
   echo("clientCmdAuthChallenge():");

   if(%alg !$= "aims/playerdb/auth.1")
   {
      error("Received auth challenge with unknown algorithm");
      disconnect();
      return;
   }

   if(!$Pref::AIMS::Enabled)
   {
      error("Received unexpected auth challenge, disconnecting...");
      disconnect();
      return;
   }

   %servername = %arg1;
   %servertime = %arg2;
   %serverrand = %arg3;
   
   echo(" servername:" SPC %servername);
   echo(" servertime:" SPC %servertime);
   echo(" serverrand:" SPC %serverrand);

   %clienttime = getSimTime(); //getTime();
   %clientrand = getRandom(999999);

   %hash = sha256(
      %servername SPC
      ServerConnection.getAddress() SPC
      %clienttime SPC
      %servertime SPC
      %clientrand SPC
      %serverrand SPC
      $Pref::AIMS::Password
   );

   commandToServer('AuthResponse',
      %hash,
      $Pref::AIMS::PlayerName,
      ServerConnection.getAddress(),
      %clienttime,
      %clientrand
   );
}

// Sync the Camera and the EditorGui
function clientCmdSyncEditorGui()
{
   if (isObject(EditorGui))
      EditorGui.syncCameraGui();
}

function clientCmdInitPreload()
{
   if(isObject($Client::Preload))
      $Client::Preload.delete();
   $Client::Preload = new SimGroup();
   $Client::Preload.serverAddress = ServerConnection.getAddress();
   $Client::Preload.state = "working";
   $Client::Preload.missingFiles = new ArrayObject();
   $Client::Preload.add($Client::Preload.missingFiles);
   PreloadGui.addText("CONNECTED\nCHECKING REQUIRED FILES\n");
   Canvas.setContent(PreloadGui);
}

function clientCmdFinishPreload()
{
   PreloadGui.addText("\n");
   %c = $Client::Preload.missingFiles.count();
   if(%c == 0)
   {
      PreloadGui.addText("HAVE REQUIRED FILES, ASKING TO PROCEED...\n");
      $Client::Preload.delete();
      commandToServer('PreloadFinished', "success");
   }
   else
   {
      PreloadGui.addText("MISSING REQUIRED FILES, UNABLE TO PROCEED!\n");
      $Client::Preload.state = "failed";
      commandToServer('PreloadFinished', $Client::Preload.state);
      //schedule(ServerConnection, 3000, "disconnect();");
   }
}

function clientCmdCheckFile(%file, %size, %crc)
{
   %local = 0;
   if(isFile(%file))
      %local = getFileCRC(%file);
   
   if(%local $= %crc)
   {
      PreloadGui.addText(".");
   }
   else
   {
      PreloadGui.addText("X");
      $Client::Preload.missingFiles.push_back(%file, %size);
      $Client::Preload.state = "failed";
   }
}

function clientCmdExecContentScript(%path)
{
   if(strstr(%path, ".." ) != -1)
   {
      echo("clientCmdExecContentScript(): skipping" SPC %path);
      return;
   }
   %stor = $instantGroup;
   $instantGroup = ClientMissionCleanup;
   exec("content/" @ %path @ ".cs");
   $instantGroup = %stor;
}

