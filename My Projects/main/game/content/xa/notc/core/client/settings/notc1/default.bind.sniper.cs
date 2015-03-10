// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if ( isObject( XaNotc1CatSniperMoveMap ) )
   XaNotc1CatSniperMoveMap.delete();
new ActionMap(XaNotc1CatSniperMoveMap);

function XaNotc1CatSniperMoveMap_activate()
{
   XaNotc1CatSniperMoveMap.push();
}

XaNotc1CatSniperMoveMap.bind( keyboard, a, XaNotc1CatMoveMap_moveleft );
XaNotc1CatSniperMoveMap.bind( keyboard, d, XaNotc1CatMoveMap_moveright );
XaNotc1CatSniperMoveMap.bind( keyboard, left, XaNotc1CatMoveMap_moveleft );
XaNotc1CatSniperMoveMap.bind( keyboard, right, XaNotc1CatMoveMap_moveright );

XaNotc1CatSniperMoveMap.bind( keyboard, w, XaNotc1CatMoveMap_moveforward );
XaNotc1CatSniperMoveMap.bind( keyboard, s, XaNotc1CatMoveMap_movebackward );
XaNotc1CatSniperMoveMap.bind( keyboard, up, XaNotc1CatMoveMap_moveforward );
XaNotc1CatSniperMoveMap.bind( keyboard, down, XaNotc1CatMoveMap_movebackward );

//XaNotc1CatSniperMoveMap.bind( keyboard, e, XaNotc1CatMoveMap_moveup );
//XaNotc1CatSniperMoveMap.bind( keyboard, c, XaNotc1CatMoveMap_movedown );

XaNotc1CatSniperMoveMap.bind( keyboard, space, XaNotc1CatMoveMap_instantXJump );
XaNotc1CatSniperMoveMap.bind( keyboard, lalt, XaNotc1CatMoveMap_chargedXJump );
XaNotc1CatSniperMoveMap.bind( mouse, xaxis, XaNotc1CatSniperMoveMap_yaw );
XaNotc1CatSniperMoveMap.bind( mouse, yaxis, XaNotc1CatSniperMoveMap_pitch );

XaNotc1CatSniperMoveMap.bind( gamepad, thumbrx, "D", "-0.23 0.23", XaNotc1CatMoveMap_gamepadYaw );
XaNotc1CatSniperMoveMap.bind( gamepad, thumbry, "D", "-0.23 0.23", XaNotc1CatMoveMap_gamepadPitch );
XaNotc1CatSniperMoveMap.bind( gamepad, thumblx, "D", "-0.23 0.23", XaNotc1CatMoveMap_gamePadMoveX );
XaNotc1CatSniperMoveMap.bind( gamepad, thumbly, "D", "-0.23 0.23", XaNotc1CatMoveMap_gamePadMoveY );

XaNotc1CatSniperMoveMap.bind( gamepad, btn_a, XaNotc1CatMoveMap_jump );
XaNotc1CatSniperMoveMap.bindCmd( gamepad, btn_back, "disconnect();", "" );

XaNotc1CatSniperMoveMap.bindCmd(gamepad, dpadl, "toggleLightColorViz();", "");
XaNotc1CatSniperMoveMap.bindCmd(gamepad, dpadu, "toggleDepthViz();", "");
XaNotc1CatSniperMoveMap.bindCmd(gamepad, dpadd, "toggleNormalsViz();", "");
XaNotc1CatSniperMoveMap.bindCmd(gamepad, dpadr, "toggleLightSpecularViz();", "");



XaNotc1CatSniperMoveMap.bind(keyboard, lshift, XaNotc1CatMoveMap_doWalk);
XaNotc1CatSniperMoveMap.bind(keyboard, lcontrol, XaNotc1CatMoveMap_doSlide);
XaNotc1CatSniperMoveMap.bind(gamepad, btn_b, XaNotc1CatMoveMap_doSlide);


XaNotc1CatSniperMoveMap.bind(keyboard, "x", XaNotc1CatMoveMap_fireBounce);

//------------------------------------------------------------------------------
// Mouse Trigger
//------------------------------------------------------------------------------

XaNotc1CatSniperMoveMap.bind( mouse, button0, XaNotc1CatMoveMap_trigger0 );
XaNotc1CatSniperMoveMap.bind( mouse, button1, XaNotc1CatSniperMoveMap_trigger1 );
XaNotc1CatSniperMoveMap.bind( mouse, button2, XaNotc1CatSniperMoveMap_trigger3 );

XaNotc1CatSniperMoveMap.bind(gamepad, triggerr, XaNotc1CatMoveMap_gamepadFire);
XaNotc1CatSniperMoveMap.bind(gamepad, triggerl, XaNotc1CatMoveMap_gamepadAltTrigger);

XaNotc1CatSniperMoveMap.bind(mouse, "zaxis", XaNotc1CatSniperMoveMap_mouseZoom);
XaNotc1CatSniperMoveMap.bind(keyboard, "f", XaNotc1CatMoveMap_switchFeed);

XaNotc1CatSniperMoveMap.bind( keyboard, v, XaNotc1CatMoveMap_toggleFreeLook ); // v for vanity

XaNotc1CatSniperMoveMap.bind( gamepad, btn_x, XaNotc1CatMoveMap_toggleFirstPerson );

XaNotc1CatSniperMoveMap.bind(keyboard, "p", XaNotc1CatMoveMap_toggleFirstPerson );

XaNotc1CatSniperMoveMap.bind(mouse0, "alt button1", XaNotc1CatMoveMap_suicide);

XaNotc1CatSniperMoveMap.bindCmd(keyboard, "1", "commandToServer('action', 1);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "2", "commandToServer('action', 2);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "3", "commandToServer('action', 3);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "4", "commandToServer('action', 4);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "5", "commandToServer('action', 5);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "6", "commandToServer('action', 6);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "7", "commandToServer('action', 7);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "8", "commandToServer('action', 8);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "9", "commandToServer('action', 9);", "");
XaNotc1CatSniperMoveMap.bindCmd(keyboard, "0", "commandToServer('action', 10);", "");

XaNotc1CatSniperMoveMap.bind(keyboard, "q", XaNotc1CatMoveMap_cycleWeapons);


