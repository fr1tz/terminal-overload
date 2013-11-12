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

//-----------------------------------------------------------------------------
// Damage Direction Indicator
//-----------------------------------------------------------------------------

function clientCmdSetDamageDirection(%direction)
{
   eval("%ctrl = SoldierHudDamageHUD-->damage_" @ %direction @ ";");
   if (isObject(%ctrl))
   {
      // Show the indicator, and schedule an event to hide it again
      cancelAll(%ctrl);
      %ctrl.setVisible(true);
      %ctrl.schedule(500, setVisible, false);
   }
}

//-----------------------------------------------------------------------------
// Teleporter visual effect
//-----------------------------------------------------------------------------

function clientCmdPlayTeleportEffect(%position, %effectDataBlock)
{
   if (isObject(%effectDataBlock))
   {
      new Explosion()
      {
         position = %position;
         dataBlock = %effectDataBlock;
      };
   }
}

// ----------------------------------------------------------------------------
// WeaponHUD
// ----------------------------------------------------------------------------

// Update the Ammo Counter with current ammo, if not any then hide the counter.
function clientCmdSetAmmoAmountHud(%amount, %amountInClips)
{
   SoldierHudAmmoAmount.zMagazine = %amount;
   SoldierHudAmmoAmount.zSpare = %amountInClips;
   SoldierHudAmmoAmount.setVisible(true);
}

// Here we update the Weapon Preview image & reticle for each weapon.  We also
// update the Ammo Counter (just so we don't have to call it separately).
// Passing an empty parameter ("") hides the HUD component.

function clientCmdRefreshWeaponHUD(%amount, %preview, %ret, %zoomRet, %amountInClips)
{
   clientCmdSetAmmoAmountHud(%amount, %amountInClips);

   if (%preview $= "")
      WeaponHUD.setVisible(false);//PreviewImage.setVisible(false);
   else
   {
      WeaponHUD.setVisible(true);//PreviewImage.setVisible(true);
      PreviewImage.setbitmap("content/torque3d/3.0/gui/weaponHud/"@ detag(%preview));
   }

   if (%ret $= "")
      Reticle.setVisible(false);
   else
   {
      Reticle.setVisible(true);
      Reticle.setbitmap("content/torque3d/3.0/gui/weaponHud/"@ detag(%ret));
   }

   if (isObject(ZoomReticle))
   {
      if (%zoomRet $= "")
      {
         ZoomReticle.setBitmap("");
      }
      else
      {
         ZoomReticle.setBitmap("content/torque3d/3.0/gui/weaponHud/"@ detag(%zoomRet));
      }
   }
}

// ----------------------------------------------------------------------------
// Vehicle Support
// ----------------------------------------------------------------------------

function clientCmdtoggleVehicleMap(%toggle)
{
   if(%toggle)
   {
      moveMap.pop();
      vehicleMap.push();
   }
   else
   {
      vehicleMap.pop();
      moveMap.push();
   }
}

// ----------------------------------------------------------------------------
// Turret Support
// ----------------------------------------------------------------------------

// Call by the Turret class when a player mounts or unmounts it.
// %turret = The turret that was mounted
// %player = The player doing the mounting
// %mounted = True if the turret was mounted, false if it was unmounted
function turretMountCallback(%turret, %player, %mounted)
{
   //echo ( "\c4turretMountCallback -> " @ %mounted );

   if (%mounted)
   {
      // Push the action map
      turretMap.push();
   }
   else
   {
      // Pop the action map
      turretMap.pop();
   }
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
