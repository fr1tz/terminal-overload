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

XaNotc1CatMoveMap.bind( keyboard, space, XaNotc1CatMoveMap_instantXJump );
XaNotc1CatMoveMap.bind( keyboard, lalt, XaNotc1CatMoveMap_chargedXJump );
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

XaNotc1CatMoveMap.bind(keyboard, lshift, XaNotc1CatMoveMap_doWalk);
XaNotc1CatMoveMap.bind(keyboard, lcontrol, XaNotc1CatMoveMap_doSlide);
XaNotc1CatMoveMap.bind(gamepad, btn_b, XaNotc1CatMoveMap_doSlide);

//------------------------------------------------------------------------------
// Discs
//------------------------------------------------------------------------------

XaNotc1CatMoveMap.bind(keyboard, "e", XaNotc1CatMoveMap_selectDiscSlot1);
XaNotc1CatMoveMap.bind(keyboard, "r", XaNotc1CatMoveMap_selectDiscSlot2);

//------------------------------------------------------------------------------
// B.O.U.N.C.E.
//------------------------------------------------------------------------------

XaNotc1CatMoveMap.bind(keyboard, "x", XaNotc1CatMoveMap_fireBounce);

//------------------------------------------------------------------------------
// Mouse Trigger
//------------------------------------------------------------------------------

XaNotc1CatMoveMap.bind( mouse, button0, XaNotc1CatMoveMap_trigger0 );
XaNotc1CatMoveMap.bind( mouse, button1, XaNotc1CatMoveMap_trigger1 );
XaNotc1CatMoveMap.bind( mouse, button2, XaNotc1CatMoveMap_trigger3 );

//------------------------------------------------------------------------------
// Gamepad Trigger
//------------------------------------------------------------------------------

XaNotc1CatMoveMap.bind(gamepad, triggerr, XaNotc1CatMoveMap_gamepadFire);
XaNotc1CatMoveMap.bind(gamepad, triggerl, XaNotc1CatMoveMap_gamepadAltTrigger);

//------------------------------------------------------------------------------
// Zoom and FOV functions
//------------------------------------------------------------------------------

if($Player::CurrentFOV $= "")
   $Player::CurrentFOV = $pref::Player::DefaultFOV / 2;

XaNotc1CatMoveMap.bind(mouse, "zaxis", XaNotc1CatMoveMap_mouseZoom);
XaNotc1CatMoveMap.bind(keyboard, "f", XaNotc1CatMoveMap_switchFeed);

//------------------------------------------------------------------------------
// Camera & View functions
//------------------------------------------------------------------------------

XaNotc1CatMoveMap.bind( keyboard, v, XaNotc1CatMoveMap_toggleFreeLook ); // v for vanity
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

XaNotc1CatMoveMap.bind(mouse0, "alt button1", XaNotc1CatMoveMap_suicide);

//------------------------------------------------------------------------------
// Item manipulation
//------------------------------------------------------------------------------

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

//XaNotc1CatMoveMap.bind(keyboard, "alt w", XaNotc1CatMoveMap_throwWeapon);
//XaNotc1CatMoveMap.bind(keyboard, "alt a", XaNotc1CatMoveMap_tossAmmo);

XaNotc1CatMoveMap.bind(keyboard, "q", XaNotc1CatMoveMap_cycleWeapons);

//XaNotc1CatMoveMap.bind(keyboard, q, XaNotc1CatMoveMap_nextWeapon);
//XaNotc1CatMoveMap.bind(keyboard, "ctrl q", XaNotc1CatMoveMap_prevWeapon);
//XaNotc1CatMoveMap.bind(mouse, "zaxis", XaNotc1CatMoveMap_mouseWheelWeaponCycle);


XaNotc1CatMoveMap.bind(keyboard, "v", XaNotc1CatMoveMap_adjustSniperSights);
XaNotc1CatMoveMap.bind(keyboard, "c", XaNotc1CatMoveMap_scanForSniperTarget);


