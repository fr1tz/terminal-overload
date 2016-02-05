// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function DM::onDeath(%client)
{
   echo("DM::onDeath()");

   %client.timeOfDeath = getSimTime();

   // Clear out the name on the corpse
   %client.player.setShapeName("");

   // Schedule corpse removal
   cancelAll(%client.player);
   %client.player.schedule(10000, "startFade", 1000, 0, true);
   %client.player.schedule(11000, "delete");

   // Switch the client over to the death cam and unhook the player object.
   if (isObject(%client.deathCamera) && isObject(%client.player))
   {
      %client.deathCamera.controlMode = "Stationary";
      %client.deathCamera.setDamageFlash(1);
      %client.deathCamera.fovDelta = 0.25;
      %client.deathCamera.viewIrisSizeX = 8;
      %client.deathCamera.viewIrisSizeY = 8;
      %client.deathCamera.viewIrisDtX = -0.025;
      %client.deathCamera.viewIrisDtY = -0.03;
      %client.deathCamera.viewMotionBlurActive = true;
      %client.deathCamera.viewMotionBlurVelMul = 5;
      %client.deathCamera.hearingDeafness = 0.7;
      %client.deathCamera.hearingDeafnessDt = 0.0010;
      %client.deathCamera.hearingTinnitusEnabled = false;
      %client.deathCamera.hearingTinnitusVolume = 1.0;
      %client.deathCamera.hearingTinnitusVolumeDt = -0.005;
      %client.player.mountObject(%client.deathCamera, 4);
      %client.control(%client.deathCamera);
   }
   %client.player = 0;

   // Display damage appropriate kill message
   %sendMsgFunction = "sendMsgClientKilled_" @ %damageType;
   if ( !isFunction( %sendMsgFunction ) )
      %sendMsgFunction = "sendMsgClientKilled_Default";
   call( %sendMsgFunction, 'MsgClientKilled', %client, %sourceClient, %damLoc );

   // Dole out points and check for win
   if (( %damageType $= "Suicide" || %sourceClient == %client ) && isObject(%sourceClient))
   {
      Game.incDeaths( %client, 1, true );
      Game.incScore( %client, -1, false );
   }
   else
   {
      Game.incDeaths( %client, 1, false );
      Game.incScore( %sourceClient, 1, true );
      Game.incKills( %sourceClient, 1, false );

      // If the game may be ended by a client getting a particular score, check that now.
      if ( $Game::EndGameScore > 0 && %sourceClient.kills >= $Game::EndGameScore )
         Game.cycleGame();
   }
}
