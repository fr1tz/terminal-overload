// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if ( isObject( XaNotc1CatMoveMap ) )
   XaNotc1CatMoveMap.delete();
new ActionMap(XaNotc1CatMoveMap);

$mvTriggerCount5 = true; // sprint by default

function XaNotc1CatMoveMap_activate()
{
   XaNotc1CatMoveMap.push();
}

//------------------------------------------------------------------------------
// Movement Keys
//------------------------------------------------------------------------------

$movementSpeed = 1; // m/s

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
   %yawAdj = XaNotc1CatMoveMap_getMouseAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %yawAdj = mClamp(%yawAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %yawAdj *= 0.5;
   }

   $mvYaw += %yawAdj;
}

function XaNotc1CatMoveMap_pitch(%val)
{
   %pitchAdj = XaNotc1CatMoveMap_getMouseAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %pitchAdj = mClamp(%pitchAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %pitchAdj *= 0.5;
   }

   $mvPitch += %pitchAdj;
}

function XaNotc1CatMoveMap_jump(%val)
{
   $mvTriggerCount2++;
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

XaNotc1CatMoveMap.bind( keyboard, a, XaNotc1CatMoveMap_moveleft );
XaNotc1CatMoveMap.bind( keyboard, d, XaNotc1CatMoveMap_moveright );
XaNotc1CatMoveMap.bind( keyboard, left, XaNotc1CatMoveMap_moveleft );
XaNotc1CatMoveMap.bind( keyboard, right, XaNotc1CatMoveMap_moveright );

XaNotc1CatMoveMap.bind( keyboard, w, XaNotc1CatMoveMap_moveforward );
XaNotc1CatMoveMap.bind( keyboard, s, XaNotc1CatMoveMap_movebackward );
XaNotc1CatMoveMap.bind( keyboard, up, XaNotc1CatMoveMap_moveforward );
XaNotc1CatMoveMap.bind( keyboard, down, XaNotc1CatMoveMap_movebackward );

//XaNotc1CatMoveMap.bind( keyboard, e, XaNotc1CatMoveMap_moveup );
//XaNotc1CatMoveMap.bind( keyboard, c, XaNotc1CatMoveMap_movedown );

XaNotc1CatMoveMap.bind( keyboard, space, XaNotc1CatMoveMap_jump );
XaNotc1CatMoveMap.bind( mouse, xaxis, XaNotc1CatMoveMap_yaw );
XaNotc1CatMoveMap.bind( mouse, yaxis, XaNotc1CatMoveMap_pitch );

XaNotc1CatMoveMap.bind( gamepad, thumbrx, "D", "-0.23 0.23", XaNotc1CatMoveMap_gamepadYaw );
XaNotc1CatMoveMap.bind( gamepad, thumbry, "D", "-0.23 0.23", XaNotc1CatMoveMap_gamepadPitch );
XaNotc1CatMoveMap.bind( gamepad, thumblx, "D", "-0.23 0.23", XaNotc1CatMoveMap_gamePadMoveX );
XaNotc1CatMoveMap.bind( gamepad, thumbly, "D", "-0.23 0.23", XaNotc1CatMoveMap_gamePadMoveY );

XaNotc1CatMoveMap.bind( gamepad, btn_a, XaNotc1CatMoveMap_jump );
XaNotc1CatMoveMap.bindCmd( gamepad, btn_back, "disconnect();", "" );

XaNotc1CatMoveMap.bindCmd(gamepad, dpadl, "toggleLightColorViz();", "");
XaNotc1CatMoveMap.bindCmd(gamepad, dpadu, "toggleDepthViz();", "");
XaNotc1CatMoveMap.bindCmd(gamepad, dpadd, "toggleNormalsViz();", "");
XaNotc1CatMoveMap.bindCmd(gamepad, dpadr, "toggleLightSpecularViz();", "");

// ----------------------------------------------------------------------------
// Stance/pose
// ----------------------------------------------------------------------------

function XaNotc1CatMoveMap_doCrouch(%val)
{
   $mvTriggerCount3++;
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

XaNotc1CatMoveMap.bind(keyboard, lshift, XaNotc1CatMoveMap_doWalk);
XaNotc1CatMoveMap.bind(keyboard, lcontrol, XaNotc1CatMoveMap_doSlide);
XaNotc1CatMoveMap.bind(gamepad, btn_b, XaNotc1CatMoveMap_doSlide);

//------------------------------------------------------------------------------
// Discs
//------------------------------------------------------------------------------

function XaNotc1CatMoveMap_launchExplosiveDisc(%val)
{
   if(%val)
      commandToServer('launchExplosiveDisc');
}

function XaNotc1CatMoveMap_launchRepelDisc(%val)
{
   if(%val)
      commandToServer('launchRepelDisc');
}

function XaNotc1CatMoveMap_launchRazorDisc(%val)
{
   if(%val)
      commandToServer('launchRazorDisc');
}

XaNotc1CatMoveMap.bind(keyboard, "e", XaNotc1CatMoveMap_launchExplosiveDisc);
XaNotc1CatMoveMap.bind(keyboard, "r", XaNotc1CatMoveMap_launchRepelDisc);
XaNotc1CatMoveMap.bind(keyboard, "f", XaNotc1CatMoveMap_launchRazorDisc);

//------------------------------------------------------------------------------
// B.O.U.N.C.E.
//------------------------------------------------------------------------------

function XaNotc1CatMoveMap_fireBounce(%val)
{
   if(%val)
      commandToServer('fireBounce');
}

XaNotc1CatMoveMap.bind(keyboard, "x", XaNotc1CatMoveMap_fireBounce);

//------------------------------------------------------------------------------
// Mouse Trigger
//------------------------------------------------------------------------------

function XaNotc1CatMoveMap_mouseFire(%val)
{
   $mvTriggerCount0++;
}

function XaNotc1CatMoveMap_altTrigger(%val)
{
   $mvTriggerCount1++;
}

XaNotc1CatMoveMap.bind( mouse, button0, XaNotc1CatMoveMap_mouseFire );
XaNotc1CatMoveMap.bind( mouse, button1, XaNotc1CatMoveMap_altTrigger );

//------------------------------------------------------------------------------
// Gamepad Trigger
//------------------------------------------------------------------------------

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

XaNotc1CatMoveMap.bind(gamepad, triggerr, XaNotc1CatMoveMap_gamepadFire);
XaNotc1CatMoveMap.bind(gamepad, triggerl, XaNotc1CatMoveMap_gamepadAltTrigger);

//------------------------------------------------------------------------------
// Zoom and FOV functions
//------------------------------------------------------------------------------

if($Player::CurrentFOV $= "")
   $Player::CurrentFOV = $pref::Player::DefaultFOV / 2;

// toggleZoomFOV() works by dividing the CurrentFOV by 2.  Each time that this
// toggle is hit it simply divides the CurrentFOV by 2 once again.  If the
// FOV is reduced below a certain threshold then it resets to equal half of the
// DefaultFOV value.  This gives us 4 zoom levels to cycle through.

function XaNotc1CatMoveMap_toggleZoomFOV()
{
    $Player::CurrentFOV = $Player::CurrentFOV / 2;

    if($Player::CurrentFOV < 5)
        resetCurrentFOV();

    if(ServerConnection.zoomed)
      setFOV($Player::CurrentFOV);
    else
    {
      setFov(ServerConnection.getControlCameraDefaultFov());
    }
}

function XaNotc1CatMoveMap_resetCurrentFOV()
{
   $Player::CurrentFOV = ServerConnection.getControlCameraDefaultFov() / 2;
}

function XaNotc1CatMoveMap_turnOffZoom()
{
   ServerConnection.zoomed = false;
   setFov(ServerConnection.getControlCameraDefaultFov());
   Reticle.setVisible(true);
   zoomReticle.setVisible(false);

   // Rather than just disable the DOF effect, we want to set it to the level's
   // preset values.
   //DOFPostEffect.disable();
   ppOptionsUpdateDOFSettings();
}

function XaNotc1CatMoveMap_setZoomFOV(%val)
{
   if(%val)
      XaNotc1CatMoveMap_toggleZoomFOV();
}

function XaNotc1CatMoveMap_toggleZoom(%val)
{
   if (%val)
   {
      ServerConnection.zoomed = true;
      setFov($Player::CurrentFOV);
      Reticle.setVisible(false);
      zoomReticle.setVisible(true);

      DOFPostEffect.setAutoFocus( true );
      DOFPostEffect.setFocusParams( 0.5, 0.5, 50, 500, -5, 5 );
      DOFPostEffect.enable();
   }
   else
   {
      turnOffZoom();
   }
}

function XaNotc1CatMoveMap_mouseButtonZoom(%val)
{
   XaNotc1CatMoveMap_toggleZoom(%val);
}

function XaNotc1CatMoveMap_mouseZoom(%val)
{
	if(Canvas.isCursorOn())
		return;

	if($MouseZoomValue == 0)
		$MouseZoomValue = $Pref::NOTC1::DefaultFov;

	%minFov = ServerConnection.getControlObject().getDataBlock().cameraMinFov;
	%step = ($Pref::NOTC1::DefaultFov - %minFov)/$Pref::NOTC1::MouseZoomSteps;

	if(%val > 0)
		$MouseZoomValue -= %step;
	else
		$MouseZoomValue += %step;

	if($MouseZoomValue < %minFov)
		$MouseZoomValue = %minFov;
	else if($MouseZoomValue > $Pref::NOTC1::DefaultFov)
		$MouseZoomValue = $Pref::NOTC1::DefaultFov;

	setFov($MouseZoomValue);
}

//XaNotc1CatMoveMap.bind(keyboard, f, XaNotc1CatMoveMap_setZoomFOV); // f for field of view
XaNotc1CatMoveMap.bind(keyboard, z, XaNotc1CatMoveMap_toggleZoom); // z for zoom
//XaNotc1CatMoveMap.bind( mouse, button1, XaNotc1CatMoveMap_mouseButtonZoom );
XaNotc1CatMoveMap.bind(mouse, "zaxis", XaNotc1CatMoveMap_mouseZoom);

//------------------------------------------------------------------------------
// Camera & View functions
//------------------------------------------------------------------------------

function XaNotc1CatMoveMap_toggleFreeLook( %val )
{
   if ( %val )
      $mvFreeLook = true;
   else
      $mvFreeLook = false;
}

function XaNotc1CatMoveMap_toggleFirstPerson(%val)
{
   if (%val)
   {
      ServerConnection.setFirstPerson(!ServerConnection.isFirstPerson());
   }
}


XaNotc1CatMoveMap.bind( keyboard, v, XaNotc1CatMoveMap_toggleFreeLook ); // v for vanity
XaNotc1CatMoveMap.bind(keyboard, tab, XaNotc1CatMoveMap_toggleFirstPerson );

XaNotc1CatMoveMap.bind( gamepad, btn_x, XaNotc1CatMoveMap_toggleFirstPerson );

XaNotc1CatMoveMap.bind(keyboard, "p", XaNotc1CatMoveMap_toggleFirstPerson );

// ----------------------------------------------------------------------------
// Misc. Player stuff
// ----------------------------------------------------------------------------

// Gideon does not have these animations, so the player does not need access to
// them.  Commenting instead of removing so as to retain an example for those
// who will want to use a player model that has these animations and wishes to
// use them.

//XaNotc1CatMoveMap.bindCmd(keyboard, "ctrl w", "commandToServer('playCel',\"wave\");", "");
//XaNotc1CatMoveMap.bindCmd(keyboard, "ctrl s", "commandToServer('playCel',\"salute\");", "");

function XaNotc1CatMoveMap_suicide(%val)
{
   if (%val)
      commandToServer('suicide');
}

XaNotc1CatMoveMap.bind(keyboard, "lalt", "XaNotc1CatMoveMap_suicide");

//------------------------------------------------------------------------------
// Item manipulation
//------------------------------------------------------------------------------

XaNotc1CatMoveMap.bindCmd(keyboard, "tab", "commandToServer('action', 0);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "1", "commandToServer('action', 1);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "2", "commandToServer('action', 2);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "3", "commandToServer('action', 3);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "4", "commandToServer('action', 4);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "5", "commandToServer('action', 5);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "6", "commandToServer('action', 6);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "7", "commandToServer('action', 7);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "8", "commandToServer('action', 8);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "9", "commandToServer('action', 9);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "0", "commandToServer('action', 10);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "q", "commandToServer('action', 19);", "");

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

XaNotc1CatMoveMap.bind(keyboard, "alt w", XaNotc1CatMoveMap_throwWeapon);
XaNotc1CatMoveMap.bind(keyboard, "alt a", XaNotc1CatMoveMap_tossAmmo);

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

//XaNotc1CatMoveMap.bind(keyboard, q, XaNotc1CatMoveMap_nextWeapon);
//XaNotc1CatMoveMap.bind(keyboard, "ctrl q", XaNotc1CatMoveMap_prevWeapon);
//XaNotc1CatMoveMap.bind(mouse, "zaxis", XaNotc1CatMoveMap_mouseWheelWeaponCycle);


