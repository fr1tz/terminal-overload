// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Server Admin Commands
//-----------------------------------------------------------------------------

function SAD(%password)
{
   if (%password !$= "")
      commandToServer('SAD', %password);
}

function SADSetPassword(%password)
{
   commandToServer('SADSetPassword', %password);
}

//----------------------------------------------------------------------------
// Misc server commands
//----------------------------------------------------------------------------

function clientCmdSyncClock(%time)
{
   // Time update from the server, this is only sent at the start of a mission
   // or when a client joins a game in progress.
}
function clientCmdGameTimer(%timeLeft)
{
   HudGameTimer.setTimeLeft(%timeLeft);
}

function clientCmdGridCreateExplosions(%grid, %datablock, %griddata)
{
   if(!isObject(%datablock))
      return;

   %grid = ServerConnection.resolveGhostID(%grid);
   if(%grid == 0)
      return;
      
   %numExplosions = getWordCount(%griddata) / 4;
   for(%i = 0; %i < %numExplosions; %i++)
   {
      %gridPosX = getWord(%griddata, 4*%i+0);
      %gridPosY = getWord(%griddata, 4*%i+1);
      %gridPosZ = getWord(%griddata, 4*%i+2);
      %amount = getWord(%griddata, 4*%i+3);
      for(%j = 0; %j < %amount; %j++)
      {
         %gridPos = %gridPosX SPC %gridPosY SPC %gridPosZ + %j;
         %worldPos = %grid.gridToWorld(%gridPos);
         new Explosion()
         {
            position = %worldPos;
            dataBlock = %datablock;
         };
      }
   }
}

function clientCmdLeftPrint(%text)
{
   if(%text $= "")
      leftPrintText.setText("");
   else
      leftPrintText.setText(leftPrintText.getText() @ %text);
}

//------------------------------------------------------------------------------
// Server -> Client commands to manipulate player's view
//------------------------------------------------------------------------------

function clientCmdSetFovDelta(%dt)
{
   setFovDelta(%dt);
}

function clientCmdViewSetHud(%hud, %teamId)
{
   %valid = false;
   if(%hud $= "LightHud")
      %valid = true;
   if(%hud $= "SoldierHud")
      %valid = true;
      
   if(!%valid)
      return;
      
   %hud.zTeamId = %teamId;
   $PlayGui = %hud;
   Canvas.setContent($PlayGui);
}

function clientCmdViewSetIris(%sizeX, %dtX, %sizeY, %dtY)
{
   if(%sizeX !$= "")
      Iris.sizeX = %sizeX;
   if(%dtX !$= "")
      Iris.setDeltaX(%dtX);
   if(%sizeY !$= "")
      Iris.sizeY = %sizeY;
   if(%dtY !$= "")
      Iris.setDeltaY(%dtY);
}

function clientCmdViewSetMotionBlur(%enabled, %velmul)
{
   if(%enabled !$= "")
   {
      if(%enabled)
         MotionBlurFX.enable();
      else
         MotionBlurFX.disable();
   }
   
   if(%velmul !$= "")
      $PostFX::MotionBlur::VelMul = %velmul;
}

//------------------------------------------------------------------------------
// Server -> Client commands to manipulate player's hearing
//------------------------------------------------------------------------------

function clientCmdHearingSetDeafness(%deafness, %dt)
{
   if(%deafness !$= "")
      hearingSetDeafness(%deafness);
   if(%dt !$= "")
      hearingSetDeafnessDt(%dt);
}

function clientCmdHearingSetTinnitus(%enabled, %volume, %volumeDt)
{
   if(%enabled !$= "")
      hearingSetTinnitusEnabled(%enabled);
   if(%volume !$= "")
      hearingSetTinnitusVolume(%volume);
   if(%volumeDt !$= "")
      hearingSetTinnitusVolumeDt(%volumeDt);
}

//------------------------------------------------------------------------------
