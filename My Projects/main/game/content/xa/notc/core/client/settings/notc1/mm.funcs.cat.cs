// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function XaNotc1CatMoveMap_setSpeed(%speed)
{
   if(%speed)
      $movementSpeed = %speed;
}

function XaNotc1CatMoveMap_moveleft(%val)
{
   $mvLeftAction = %val * $movementSpeed;
}

function XaNotc1CatMoveMap_moveright(%val)
{
   $mvRightAction = %val * $movementSpeed;
}

function XaNotc1CatMoveMap_moveforward(%val)
{
   $mvForwardAction = %val * $movementSpeed;
}

function XaNotc1CatMoveMap_movebackward(%val)
{
   $mvBackwardAction = %val * $movementSpeed;
}

function XaNotc1CatMoveMap_moveup(%val)
{
   %object = ServerConnection.getControlObject();

   if(%object.isInNamespaceHierarchy("Camera"))
      $mvUpAction = %val * $movementSpeed;
}

function XaNotc1CatMoveMap_movedown(%val)
{
   %object = ServerConnection.getControlObject();

   if(%object.isInNamespaceHierarchy("Camera"))
      $mvDownAction = %val * $movementSpeed;
}

function XaNotc1CatMoveMap_turnLeft( %val )
{
   $mvYawRightSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function XaNotc1CatMoveMap_turnRight( %val )
{
   $mvYawLeftSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function XaNotc1CatMoveMap_panUp( %val )
{
   $mvPitchDownSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function XaNotc1CatMoveMap_panDown( %val )
{
   $mvPitchUpSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function XaNotc1CatMoveMap_getMouseAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * $pref::Input::LinkMouseSensitivity;
}

function XaNotc1CatMoveMap_getGamepadAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * 10.0;
}

function XaNotc1CatMoveMap_yaw(%val)
{
   MouseInputGraph_input(0, %val);

   %yawAdj = XaNotc1CatMoveMap_getMouseAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %yawAdj = mClamp(%yawAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %yawAdj *= 0.5;
   }

   MoveManager_addYaw(%yawAdj);
}

function XaNotc1CatMoveMap_pitch(%val)
{
   MouseInputGraph_input(1, %val);

   %pitchAdj = XaNotc1CatMoveMap_getMouseAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %pitchAdj = mClamp(%pitchAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %pitchAdj *= 0.5;
   }

   if($Pref::NOTC1::MouseInvertY)
      %pitchAdj = -%pitchAdj;

   if(Canvas.getContent() == notcCatSniperGui.getId()
   && XaNotc1CatMoveMap.zAdjustSniperSights)
   {
      %val = mClamp(%val*$pref::Input::LinkMouseSensitivity*0.01, -1, 1);
      notcCatSniperGui.setElevation(notcCatSniperGui.zElevation - %val);
   }
   else
      MoveManager_addPitch(%pitchAdj);
}

function XaNotc1CatMoveMap_trigger0(%val)
{
   $mvTriggerCount0++;
}

function XaNotc1CatMoveMap_trigger1(%val)
{
   $mvTriggerCount1++;
}

function XaNotc1CatMoveMap_trigger3(%val)
{
   $mvTriggerCount3++;
}

function XaNotc1CatMoveMap_jump(%val)
{
   $mvTriggerCount2++;
}

function XaNotc1CatMoveMap_instantXJump(%val)
{
   $mvTriggerCount2++;
}

function XaNotc1CatMoveMap_doSprint(%val)
{
   $mvTriggerCount5++;
}

function XaNotc1CatMoveMap_doWalk(%val)
{
   $mvTriggerCount5 = !%val;
}

function XaNotc1CatMoveMap_doSlide(%val)
{
   $mvTriggerCount6 = %val;
}

function XaNotc1CatMoveMap_chargedXJump(%val)
{
   $mvTriggerCount7 = %val;
}

function XaNotc1CatMoveMap_gamePadMoveX( %val )
{
   if(%val > 0)
   {
      $mvRightAction = %val * $movementSpeed;
      $mvLeftAction = 0;
   }
   else
   {
      $mvRightAction = 0;
      $mvLeftAction = -%val * $movementSpeed;
   }
}

function XaNotc1CatMoveMap_gamePadMoveY( %val )
{
   if(%val > 0)
   {
      $mvForwardAction = %val * $movementSpeed;
      $mvBackwardAction = 0;
   }
   else
   {
      $mvForwardAction = 0;
      $mvBackwardAction = -%val * $movementSpeed;
   }
}

function XaNotc1CatMoveMap_gamepadYaw(%val)
{
   %yawAdj = XaNotc1CatMoveMap_getGamepadAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %yawAdj = mClamp(%yawAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %yawAdj *= 0.5;
   }

   if(%yawAdj > 0)
   {
      $mvYawLeftSpeed = %yawAdj;
      $mvYawRightSpeed = 0;
   }
   else
   {
      $mvYawLeftSpeed = 0;
      $mvYawRightSpeed = -%yawAdj;
   }
}

function XaNotc1CatMoveMap_gamepadPitch(%val)
{
   %pitchAdj = getGamepadAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %pitchAdj = mClamp(%pitchAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %pitchAdj *= 0.5;
   }

   if(%pitchAdj > 0)
   {
      $mvPitchDownSpeed = %pitchAdj;
      $mvPitchUpSpeed = 0;
   }
   else
   {
      $mvPitchDownSpeed = 0;
      $mvPitchUpSpeed = -%pitchAdj;
   }
}

function XaNotc1CatMoveMap_switchFeed(%val)
{
   if(!%val)
      return;
      
   if(!ServerConnection.isFirstPerson())
      return;
      
   if(Canvas.getContent() == CatGui.getId())
      $PlayGui = notcCatSniperGui;
   else
      $PlayGui = CatGui;
      
   Canvas.setContent($PlayGui);
}

function XaNotc1CatMoveMap_mouseZoom(%val)
{
	if(Canvas.isCursorOn())
		return;

   if(!ServerConnection.isFirstPerson())
      return;

   if(Canvas.getContent() == CatGui.getId())
   {
      if($MouseZoomSteps $= "")
         $MouseZoomSteps = $Pref::NOTC1::MouseZoomSteps;

   	%minFov = ServerConnection.getControlObject().getDataBlock().cameraMinFov;
      %maxFov = $Pref::NOTC1::DefaultFov;

      %mouseZoomStepStor = $MouseZoomStep;
   	if(%val > 0)
         $MouseZoomStep++;
   	else
   		$MouseZoomStep--;
      $MouseZoomStep = mClamp($MouseZoomStep, 0, $MouseZoomSteps);
      if($MouseZoomStep == %mouseZoomStepStor)
         return;

      %pos = (1/($MouseZoomSteps)) * $MouseZoomStep;
      //echo(%pos);
      %f = mPow(1-%pos, 2);
      $MouseZoomValue = %minFov + (%maxFov-%minFov)*%f;
      setFov($MouseZoomValue);
      sfxPlayOnce(AudioGui, "content/o/rotc/p.5.4/sounds/rotc/weaponSwitch.wav");
   }
   else
   {
      %oldFov = $cameraFov;

   	%minFov = ServerConnection.getControlObject().getDataBlock().cameraMinFov;
      %maxFov = 45;

      %newFov = %oldFov * (%val > 0 ? 0.5 : 2);
      %newFov = mClamp(%newFov, %minFov, %maxFov);

      if(%newFov == %oldFov)
         return;

      $cameraFov = %newFov;
      setFov(%newFov);
      notcCatSniperGui.updateView();
      sfxPlayOnce(AudioGui, "content/o/rotc/p.5.4/sounds/rotc/weaponSwitch.wav");
   }
}

function XaNotc1CatMoveMap_toggleFirstPerson(%val)
{
   if(!%val)
      return;

   %control = ServerConnection.getControlObject();
   if(!isObject(%control))
      return;

   %datablock = %control.getDataBlock();
   if(%datablock.firstPersonOnly || %datablock.thirdPersonOnly)
      return;
      
   %fp = !ServerConnection.isFirstPerson();

   ServerConnection.setFirstPerson(%fp);

   if(%fp)
      $PlayGui = notcUserGui.zPlayGui;
   else
   {
      notcUserGui.zPlayGui = $PlayGui;
      $PlayGui = notcUserGui;
   }
      
   Canvas.setContent($PlayGui);
}

function XaNotc1CatMoveMap_selectDiscSlot1(%val)
{
   if(%val)
      commandToServer('selectDiscSlot', 1);
}

function XaNotc1CatMoveMap_selectDiscSlot2(%val)
{
   if(%val)
      commandToServer('selectDiscSlot', 2);
}

function XaNotc1CatMoveMap_selectDiscSlot3(%val)
{
   if(%val)
      commandToServer('selectDiscSlot', 3);
}

function XaNotc1CatMoveMap_fireBounce(%val)
{
   if(%val)
      commandToServer('fireBounce');
}

function XaNotc1CatMoveMap_gamepadFire(%val)
{
   if(%val > 0.1 && !$gamepadFireTriggered)
   {
      $gamepadFireTriggered = true;
      $mvTriggerCount0++;
   }
   else if(%val <= 0.1 && $gamepadFireTriggered)
   {
      $gamepadFireTriggered = false;
      $mvTriggerCount0++;
   }
}

function XaNotc1CatMoveMap_gamepadAltTrigger(%val)
{
   if(%val > 0.1 && !$gamepadAltTriggerTriggered)
   {
      $gamepadAltTriggerTriggered = true;
      $mvTriggerCount1++;
   }
   else if(%val <= 0.1 && $gamepadAltTriggerTriggered)
   {
      $gamepadAltTriggerTriggered = false;
      $mvTriggerCount1++;
   }
}

function XaNotc1CatMoveMap_toggleFreeLook( %val )
{
   if ( %val )
      $mvFreeLook = true;
   else
      $mvFreeLook = false;
}

function XaNotc1CatMoveMap_suicide(%val)
{
   if (%val)
      commandToServer('suicide');
}

function XaNotc1CatMoveMap_throwWeapon(%val)
{
   if (%val)
      commandToServer('Throw', "Weapon");
}
function XaNotc1CatMoveMap_tossAmmo(%val)
{
   if (%val)
      commandToServer('Throw', "Ammo");
}

function XaNotc1CatMoveMap_nextWeapon(%val)
{
   if (%val)
      commandToServer('cycleWeapon', "next");
}

function XaNotc1CatMoveMap_prevWeapon(%val)
{
   if (%val)
      commandToServer('cycleWeapon', "prev");
}

function XaNotc1CatMoveMap_mouseWheelWeaponCycle(%val)
{
   if (%val < 0)
      commandToServer('cycleWeapon', "next");
   else if (%val > 0)
      commandToServer('cycleWeapon', "prev");
}

function XaNotc1CatMoveMap_cycleWeapons(%val)
{
   if(%val) commandToServer('action', 19);
}

function XaNotc1CatMoveMap_adjustSniperSights(%val)
{
   XaNotc1CatMoveMap.zAdjustSniperSights = %val;
}

function XaNotc1CatMoveMap_scanForSniperTarget(%val)
{
   notcCatSniperGui.zScanForTargets = %val;
   if(%val)
      notcCatSniperGui.scanForTarget();
}

