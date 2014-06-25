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
// Non-remapable binds
//------------------------------------------------------------------------------

function escapeFromGame()
{
   if ( $Server::ServerType $= "SinglePlayer" )
      MessageBoxYesNo( "Exit", "Exit from this Mission?", "disconnect();", "");
   else
      MessageBoxYesNo( "Disconnect", "Disconnect from the server?", "disconnect();", "");
}

XaNotc1CatMoveMap.bindCmd(keyboard, "escape", "", "handleEscape();");

function showPlayerList(%val)
{
   if (%val)
      PlayerListGui.toggle();
}

XaNotc1CatMoveMap.bind( keyboard, Tab, showPlayerList );

function hideHUDs(%val)
{
   if (%val)
      HudlessPlayGui.toggle();
}

XaNotc1CatMoveMap.bind(keyboard, "ctrl h", hideHUDs);

function doScreenShotHudless(%val)
{
   if(%val)
   {
      canvas.setContent(HudlessPlayGui);
      //doScreenshot(%val);
      schedule(10, 0, "doScreenShot", %val);
   }
   else
      canvas.setContent($PlayGui);
}

XaNotc1CatMoveMap.bind(keyboard, "alt p", doScreenShotHudless);

//------------------------------------------------------------------------------
// Movement Keys
//------------------------------------------------------------------------------

$movementSpeed = 1; // m/s

function setSpeed(%speed)
{
   if(%speed)
      $movementSpeed = %speed;
}

function moveleft(%val)
{
   $mvLeftAction = %val * $movementSpeed;
}

function moveright(%val)
{
   $mvRightAction = %val * $movementSpeed;
}

function moveforward(%val)
{
   $mvForwardAction = %val * $movementSpeed;
}

function movebackward(%val)
{
   $mvBackwardAction = %val * $movementSpeed;
}

function moveup(%val)
{
   %object = ServerConnection.getControlObject();
   
   if(%object.isInNamespaceHierarchy("Camera"))
      $mvUpAction = %val * $movementSpeed;
}

function movedown(%val)
{
   %object = ServerConnection.getControlObject();
   
   if(%object.isInNamespaceHierarchy("Camera"))
      $mvDownAction = %val * $movementSpeed;
}

function turnLeft( %val )
{
   $mvYawRightSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function turnRight( %val )
{
   $mvYawLeftSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function panUp( %val )
{
   $mvPitchDownSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function panDown( %val )
{
   $mvPitchUpSpeed = %val ? $Pref::Input::KeyboardTurnSpeed : 0;
}

function getMouseAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * $pref::Input::LinkMouseSensitivity;
}

function getGamepadAdjustAmount(%val)
{
   // based on a default camera FOV of 90'
   return(%val * ($cameraFov / 90) * 0.01) * 10.0;
}

function yaw(%val)
{
   %yawAdj = getMouseAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %yawAdj = mClamp(%yawAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %yawAdj *= 0.5;
   }

   $mvYaw += %yawAdj;
}

function pitch(%val)
{
   %pitchAdj = getMouseAdjustAmount(%val);
   if(ServerConnection.isControlObjectRotDampedCamera())
   {
      // Clamp and scale
      %pitchAdj = mClamp(%pitchAdj, -m2Pi()+0.01, m2Pi()-0.01);
      %pitchAdj *= 0.5;
   }

   $mvPitch += %pitchAdj;
}

function jump(%val)
{
   $mvTriggerCount2++;
}

function gamePadMoveX( %val )
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

function gamePadMoveY( %val )
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

function gamepadYaw(%val)
{
   %yawAdj = getGamepadAdjustAmount(%val);
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

function gamepadPitch(%val)
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

XaNotc1CatMoveMap.bind( keyboard, a, moveleft );
XaNotc1CatMoveMap.bind( keyboard, d, moveright );
XaNotc1CatMoveMap.bind( keyboard, left, moveleft );
XaNotc1CatMoveMap.bind( keyboard, right, moveright );

XaNotc1CatMoveMap.bind( keyboard, w, moveforward );
XaNotc1CatMoveMap.bind( keyboard, s, movebackward );
XaNotc1CatMoveMap.bind( keyboard, up, moveforward );
XaNotc1CatMoveMap.bind( keyboard, down, movebackward );

//XaNotc1CatMoveMap.bind( keyboard, e, moveup );
//XaNotc1CatMoveMap.bind( keyboard, c, movedown );

XaNotc1CatMoveMap.bind( keyboard, space, jump );
XaNotc1CatMoveMap.bind( mouse, xaxis, yaw );
XaNotc1CatMoveMap.bind( mouse, yaxis, pitch );

XaNotc1CatMoveMap.bind( gamepad, thumbrx, "D", "-0.23 0.23", gamepadYaw );
XaNotc1CatMoveMap.bind( gamepad, thumbry, "D", "-0.23 0.23", gamepadPitch );
XaNotc1CatMoveMap.bind( gamepad, thumblx, "D", "-0.23 0.23", gamePadMoveX );
XaNotc1CatMoveMap.bind( gamepad, thumbly, "D", "-0.23 0.23", gamePadMoveY );

XaNotc1CatMoveMap.bind( gamepad, btn_a, jump );
XaNotc1CatMoveMap.bindCmd( gamepad, btn_back, "disconnect();", "" );

XaNotc1CatMoveMap.bindCmd(gamepad, dpadl, "toggleLightColorViz();", "");
XaNotc1CatMoveMap.bindCmd(gamepad, dpadu, "toggleDepthViz();", "");
XaNotc1CatMoveMap.bindCmd(gamepad, dpadd, "toggleNormalsViz();", "");
XaNotc1CatMoveMap.bindCmd(gamepad, dpadr, "toggleLightSpecularViz();", "");

// ----------------------------------------------------------------------------
// Stance/pose
// ----------------------------------------------------------------------------

function doCrouch(%val)
{
   $mvTriggerCount3++;
}

function doSprint(%val)
{
   $mvTriggerCount5++;
}

function doWalk(%val)
{
   $mvTriggerCount5 = !%val;
}

function doSlide(%val)
{
   $mvTriggerCount6 = %val;
}

XaNotc1CatMoveMap.bind(keyboard, lshift, doWalk);
XaNotc1CatMoveMap.bind(keyboard, lcontrol, doSlide);
XaNotc1CatMoveMap.bind(gamepad, btn_b, doSlide);

//------------------------------------------------------------------------------
// Discs
//------------------------------------------------------------------------------

function launchExplosiveDisc(%val)
{
   if(%val)
      commandToServer('launchExplosiveDisc');
}

function launchRepelDisc(%val)
{
   if(%val)
      commandToServer('launchRepelDisc');
}

function launchRazorDisc(%val)
{
   if(%val)
      commandToServer('launchRazorDisc');
}

XaNotc1CatMoveMap.bind(keyboard, "e", launchExplosiveDisc);
XaNotc1CatMoveMap.bind(keyboard, "r", launchRepelDisc);
XaNotc1CatMoveMap.bind(keyboard, "f", launchRazorDisc);

//------------------------------------------------------------------------------
// B.O.U.N.C.E.
//------------------------------------------------------------------------------

function fireBounce(%val)
{
   if(%val)
      commandToServer('fireBounce');
}

XaNotc1CatMoveMap.bind(keyboard, "x", fireBounce);

//------------------------------------------------------------------------------
// Mouse Trigger
//------------------------------------------------------------------------------

function mouseFire(%val)
{
   $mvTriggerCount0++;
}

function altTrigger(%val)
{
   $mvTriggerCount1++;
}

XaNotc1CatMoveMap.bind( mouse, button0, mouseFire );
XaNotc1CatMoveMap.bind( mouse, button1, altTrigger );

//------------------------------------------------------------------------------
// Gamepad Trigger
//------------------------------------------------------------------------------

function gamepadFire(%val)
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

function gamepadAltTrigger(%val)
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

XaNotc1CatMoveMap.bind(gamepad, triggerr, gamepadFire);
XaNotc1CatMoveMap.bind(gamepad, triggerl, gamepadAltTrigger);

//------------------------------------------------------------------------------
// Zoom and FOV functions
//------------------------------------------------------------------------------

if($Player::CurrentFOV $= "")
   $Player::CurrentFOV = $pref::Player::DefaultFOV / 2;

// toggleZoomFOV() works by dividing the CurrentFOV by 2.  Each time that this
// toggle is hit it simply divides the CurrentFOV by 2 once again.  If the
// FOV is reduced below a certain threshold then it resets to equal half of the
// DefaultFOV value.  This gives us 4 zoom levels to cycle through.

function toggleZoomFOV()
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

function resetCurrentFOV()
{
   $Player::CurrentFOV = ServerConnection.getControlCameraDefaultFov() / 2;
}

function turnOffZoom()
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

function setZoomFOV(%val)
{
   if(%val)
      toggleZoomFOV();
}

function toggleZoom(%val)
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

function mouseButtonZoom(%val)
{
   toggleZoom(%val);
}

function mouseZoom(%val)
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

//XaNotc1CatMoveMap.bind(keyboard, f, setZoomFOV); // f for field of view
XaNotc1CatMoveMap.bind(keyboard, z, toggleZoom); // z for zoom
//XaNotc1CatMoveMap.bind( mouse, button1, mouseButtonZoom );
XaNotc1CatMoveMap.bind(mouse, "zaxis", mouseZoom);

//------------------------------------------------------------------------------
// Camera & View functions
//------------------------------------------------------------------------------

function toggleFreeLook( %val )
{
   if ( %val )
      $mvFreeLook = true;
   else
      $mvFreeLook = false;
}

function toggleFirstPerson(%val)
{
   if (%val)
   {
      ServerConnection.setFirstPerson(!ServerConnection.isFirstPerson());
   }
}

function toggleCamera(%val)
{
   if (%val)
      commandToServer('ToggleCamera');
}

XaNotc1CatMoveMap.bind( keyboard, v, toggleFreeLook ); // v for vanity
XaNotc1CatMoveMap.bind(keyboard, tab, toggleFirstPerson );
XaNotc1CatMoveMap.bind(keyboard, "alt c", toggleCamera);

XaNotc1CatMoveMap.bind( gamepad, btn_start, toggleCamera );
XaNotc1CatMoveMap.bind( gamepad, btn_x, toggleFirstPerson );

XaNotc1CatMoveMap.bind(keyboard, "p", toggleFirstPerson );

// ----------------------------------------------------------------------------
// Misc. Player stuff
// ----------------------------------------------------------------------------

// Gideon does not have these animations, so the player does not need access to
// them.  Commenting instead of removing so as to retain an example for those
// who will want to use a player model that has these animations and wishes to
// use them.

//XaNotc1CatMoveMap.bindCmd(keyboard, "ctrl w", "commandToServer('playCel',\"wave\");", "");
//XaNotc1CatMoveMap.bindCmd(keyboard, "ctrl s", "commandToServer('playCel',\"salute\");", "");

function suicide(%val)
{
   if (%val)
      commandToServer('suicide');
}

XaNotc1CatMoveMap.bind(keyboard, "lalt", "suicide");

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
XaNotc1CatMoveMap.bindCmd(keyboard, "F1", "commandToServer('action', 11);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "F2", "commandToServer('action', 12);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "F3", "commandToServer('action', 13);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "F4", "commandToServer('action', 14);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "F5", "commandToServer('action', 15);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "F6", "commandToServer('action', 16);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "F7", "commandToServer('action', 17);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "F8", "commandToServer('action', 18);", "");
XaNotc1CatMoveMap.bindCmd(keyboard, "q", "commandToServer('action', 19);", "");

function unmountWeapon(%val)
{
   if (%val)
      commandToServer('unmountWeapon');
}

XaNotc1CatMoveMap.bind(keyboard, 0, unmountWeapon);

function throwWeapon(%val)
{
   if (%val)
      commandToServer('Throw', "Weapon");
}
function tossAmmo(%val)
{
   if (%val)
      commandToServer('Throw', "Ammo");
}

XaNotc1CatMoveMap.bind(keyboard, "alt w", throwWeapon);
XaNotc1CatMoveMap.bind(keyboard, "alt a", tossAmmo);

function nextWeapon(%val)
{
   if (%val)
      commandToServer('cycleWeapon', "next");
}

function prevWeapon(%val)
{
   if (%val)
      commandToServer('cycleWeapon', "prev");
}

function mouseWheelWeaponCycle(%val)
{
   if (%val < 0)
      commandToServer('cycleWeapon', "next");
   else if (%val > 0)
      commandToServer('cycleWeapon', "prev");
}

//XaNotc1CatMoveMap.bind(keyboard, q, nextWeapon);
//XaNotc1CatMoveMap.bind(keyboard, "ctrl q", prevWeapon);
//XaNotc1CatMoveMap.bind(mouse, "zaxis", mouseWheelWeaponCycle);

//------------------------------------------------------------------------------
// Message HUD functions
//------------------------------------------------------------------------------

function pageMessageHudUp( %val )
{
   if ( %val )
      pageUpMessageHud();
}

function pageMessageHudDown( %val )
{
   if ( %val )
      pageDownMessageHud();
}

function resizeMessageHud( %val )
{
   if ( %val )
      cycleMessageHudSize();
}

XaNotc1CatMoveMap.bind(keyboard, u, toggleMessageHud );
//XaNotc1CatMoveMap.bind(keyboard, y, teamMessageHud );
XaNotc1CatMoveMap.bind(keyboard, "pageUp", pageMessageHudUp );
XaNotc1CatMoveMap.bind(keyboard, "pageDown", pageMessageHudDown );
//XaNotc1CatMoveMap.bind(keyboard, "p", resizeMessageHud );

//------------------------------------------------------------------------------
// Demo recording functions
//------------------------------------------------------------------------------

function startRecordingDemo( %val )
{
   if ( %val )
      startDemoRecord();
}

function stopRecordingDemo( %val )
{
   if ( %val )
      stopDemoRecord();
}

//XaNotc1CatMoveMap.bind( keyboard, F3, startRecordingDemo );
//XaNotc1CatMoveMap.bind( keyboard, F4, stopRecordingDemo );


//------------------------------------------------------------------------------
// Helper Functions
//------------------------------------------------------------------------------

function bringUpOptions(%val)
{
   if (%val)
      Canvas.pushDialog(OptionsDlg);
}

GlobalActionMap.bind(keyboard, "ctrl o", bringUpOptions);


//------------------------------------------------------------------------------
// Debugging Functions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//
// Start profiler by pressing ctrl f3
// ctrl f3 - starts profile that will dump to console and file
//
function doProfile(%val)
{
   if (%val)
   {
      // key down -- start profile
      echo("Starting profile session...");
      profilerReset();
      profilerEnable(true);
   }
   else
   {
      // key up -- finish off profile
      echo("Ending profile session...");

      profilerDumpToFile("profilerDumpToFile" @ getSimTime() @ ".txt");
      profilerEnable(false);
   }
}

GlobalActionMap.bind(keyboard, "ctrl F3", doProfile);

//------------------------------------------------------------------------------
// Misc.
//------------------------------------------------------------------------------

GlobalActionMap.bind(keyboard, "tilde", toggleConsole);
GlobalActionMap.bindCmd(keyboard, "alt k", "cls();","");
GlobalActionMap.bindCmd(keyboard, "alt enter", "", "Canvas.attemptFullscreenToggle();");
XaNotc1CatMoveMap.bindCmd(keyboard, "n", "toggleNetGraph();", "");

// ----------------------------------------------------------------------------
// Useful vehicle stuff
// ----------------------------------------------------------------------------

// Trace a line along the direction the crosshair is pointing
// If you find a car with a player in it...eject them
function carjack()
{
   %player = LocalClientConnection.getControlObject();

   if (%player.getClassName() $= "Player")
   {
      %eyeVec = %player.getEyeVector();

      %startPos = %player.getEyePoint();
      %endPos = VectorAdd(%startPos, VectorScale(%eyeVec, 1000));

      %target = ContainerRayCast(%startPos, %endPos, $TypeMasks::VehicleObjectType);

      if (%target)
      {
         // See if anyone is mounted in the car's driver seat
         %mount = %target.getMountNodeObject(0);

         // Can only carjack bots
         // remove '&& %mount.getClassName() $= "AIPlayer"' to allow you
         // to carjack anyone/anything
         if (%mount && %mount.getClassName() $= "AIPlayer")
         {
            commandToServer('carUnmountObj', %mount);
         }
      }
   }
}

// Bind the keys to the carjack command
XaNotc1CatMoveMap.bindCmd(keyboard, "ctrl z", "carjack();", "");


// Starting vehicle action map code
if ( isObject( XaNotc1VehicleMoveMap ) )
   XaNotc1VehicleMoveMap.delete();
new ActionMap(XaNotc1VehicleMoveMap);

// The key command for flipping the car
XaNotc1VehicleMoveMap.bindCmd(keyboard, "ctrl x", "commandToServer(\'flipCar\');", "");

function getOut()
{
   XaNotc1VehicleMoveMap.pop();
   XaNotc1CatMoveMap.push();
   commandToServer('dismountVehicle');
}

function brakeLights()
{
   // Turn on/off the Cheetah's head lights.
   commandToServer('toggleBrakeLights');
}

function brake(%val)
{
   commandToServer('toggleBrakeLights');
   $mvTriggerCount2++;
}

XaNotc1VehicleMoveMap.bind( keyboard, w, moveforward );
XaNotc1VehicleMoveMap.bind( keyboard, s, movebackward );
XaNotc1VehicleMoveMap.bind( keyboard, up, moveforward );
XaNotc1VehicleMoveMap.bind( keyboard, down, movebackward );
XaNotc1VehicleMoveMap.bind( mouse, xaxis, yaw );
XaNotc1VehicleMoveMap.bind( mouse, yaxis, pitch );
XaNotc1VehicleMoveMap.bind( mouse, button0, mouseFire );
//XaNotc1VehicleMoveMap.bind( mouse, button1, altTrigger );
XaNotc1VehicleMoveMap.bindCmd(keyboard, "ctrl f","getout();","");
XaNotc1VehicleMoveMap.bind(keyboard, space, brake);
XaNotc1VehicleMoveMap.bindCmd(keyboard, "l", "brakeLights();", "");
XaNotc1VehicleMoveMap.bindCmd(keyboard, "escape", "", "handleEscape();");
XaNotc1VehicleMoveMap.bind( keyboard, v, toggleFreeLook ); // v for vanity
//XaNotc1VehicleMoveMap.bind(keyboard, tab, toggleFirstPerson );
XaNotc1VehicleMoveMap.bind(keyboard, "alt c", toggleCamera);

