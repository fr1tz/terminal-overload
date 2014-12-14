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
   $Client::PreloadPhase = true;
   $Client::PreloadResult = "success";
   Canvas.setContent(PreloadGui);
}

function clientCmdFinishPreload()
{
   $Client::PreloadPhase = false;

   commandToServer('PreloadFinished', $Client::PreloadResult);
}

function clientCmdCheckFile(%file, %crc)
{
   %local = "MISSING";
   if(isFile(%file))
      %local = getFileCRC(%file);

   PreloadGui.addLine(%file @ ":");
   PreloadGui.addLine("   REMOTE:" SPC %crc SPC "LOCAL:" SPC %local);
   
   if(%local !$= %crc)
      $Client::PreloadResult = "failed";
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

