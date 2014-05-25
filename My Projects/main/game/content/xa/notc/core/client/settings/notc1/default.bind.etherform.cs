// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if ( isObject( XaNotc1EtherformMoveMap ) )
   XaNotc1EtherformMoveMap.delete();
new ActionMap(XaNotc1EtherformMoveMap);

function XaNotc1EtherformMoveMap_activate()
{
   XaNotc1EtherformMoveMap.push();
}

XaNotc1EtherformMoveMap.bind( keyboard, a, moveleft );
XaNotc1EtherformMoveMap.bind( keyboard, d, moveright );
XaNotc1EtherformMoveMap.bind( keyboard, left, moveleft );
XaNotc1EtherformMoveMap.bind( keyboard, right, moveright );

XaNotc1EtherformMoveMap.bind( keyboard, w, moveforward );
XaNotc1EtherformMoveMap.bind( keyboard, s, movebackward );
XaNotc1EtherformMoveMap.bind( keyboard, up, moveforward );
XaNotc1EtherformMoveMap.bind( keyboard, down, movebackward );

XaNotc1EtherformMoveMap.bind(keyboard, space, jump);
XaNotc1EtherformMoveMap.bind(keyboard, lcontrol, doSlide);

XaNotc1EtherformMoveMap.bind( mouse, xaxis, yaw );
XaNotc1EtherformMoveMap.bind( mouse, yaxis, pitch );

XaNotc1EtherformMoveMap.bind( mouse, button0, mouseFire );
XaNotc1EtherformMoveMap.bind( mouse, button1, altTrigger );

