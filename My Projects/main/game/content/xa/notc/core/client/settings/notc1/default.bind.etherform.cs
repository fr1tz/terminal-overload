// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

if ( isObject( XaNotc1EtherformMoveMap ) )
   XaNotc1EtherformMoveMap.delete();
new ActionMap(XaNotc1EtherformMoveMap);

function XaNotc1EtherformMoveMap_activate()
{
   XaNotc1EtherformMoveMap.push();
}

//------------------------------------------------------------------------------

function XaNotc1EtherformMoveMap_manifest(%val)
{
   if(%val) commandToServer('Manifest');
}

function XaNotc1EtherformMoveMap_selectLoadout0(%val)
{
   if(%val) commandToServer('SelectLoadout', 0);
}

function XaNotc1EtherformMoveMap_selectLoadout1(%val)
{
   if(%val) commandToServer('SelectLoadout', 1);
}

function XaNotc1EtherformMoveMap_selectLoadout2(%val)
{
   if(%val) commandToServer('SelectLoadout', 2);
}

function XaNotc1EtherformMoveMap_selectLoadout3(%val)
{
   if(%val) commandToServer('SelectLoadout', 3);
}

function XaNotc1EtherformMoveMap_selectLoadout4(%val)
{
   if(%val) commandToServer('SelectLoadout', 4);
}

function XaNotc1EtherformMoveMap_selectLoadout5(%val)
{
   if(%val) commandToServer('SelectLoadout', 5);
}

function XaNotc1EtherformMoveMap_selectLoadout6(%val)
{
   if(%val) commandToServer('SelectLoadout', 6);
}

function XaNotc1EtherformMoveMap_selectLoadout7(%val)
{
   if(%val) commandToServer('SelectLoadout', 7);
}

function XaNotc1EtherformMoveMap_selectLoadout8(%val)
{
   if(%val) commandToServer('SelectLoadout', 8);
}

function XaNotc1EtherformMoveMap_selectLoadout9(%val)
{
   if(%val) commandToServer('SelectLoadout', 9);
}

XaNotc1EtherformMoveMap.bind(mouse0, "alt button0", XaNotc1EtherformMoveMap_manifest);

XaNotc1EtherformMoveMap.bind( keyboard, 1, XaNotc1EtherformMoveMap_selectLoadout0 );
XaNotc1EtherformMoveMap.bind( keyboard, 2, XaNotc1EtherformMoveMap_selectLoadout1 );
XaNotc1EtherformMoveMap.bind( keyboard, 3, XaNotc1EtherformMoveMap_selectLoadout2 );
XaNotc1EtherformMoveMap.bind( keyboard, 4, XaNotc1EtherformMoveMap_selectLoadout3 );
XaNotc1EtherformMoveMap.bind( keyboard, 5, XaNotc1EtherformMoveMap_selectLoadout4 );
XaNotc1EtherformMoveMap.bind( keyboard, 6, XaNotc1EtherformMoveMap_selectLoadout5 );
XaNotc1EtherformMoveMap.bind( keyboard, 7, XaNotc1EtherformMoveMap_selectLoadout6 );
XaNotc1EtherformMoveMap.bind( keyboard, 8, XaNotc1EtherformMoveMap_selectLoadout7 );
XaNotc1EtherformMoveMap.bind( keyboard, 9, XaNotc1EtherformMoveMap_selectLoadout8 );
XaNotc1EtherformMoveMap.bind( keyboard, 0, XaNotc1EtherformMoveMap_selectLoadout9 );

XaNotc1EtherformMoveMap.bind( keyboard, a, XaNotc1CatMoveMap_moveleft );
XaNotc1EtherformMoveMap.bind( keyboard, d, XaNotc1CatMoveMap_moveright );

XaNotc1EtherformMoveMap.bind( keyboard, w, XaNotc1CatMoveMap_moveforward );
XaNotc1EtherformMoveMap.bind( keyboard, s, XaNotc1CatMoveMap_movebackward );

XaNotc1EtherformMoveMap.bind(keyboard, space, XaNotc1CatMoveMap_jump);
XaNotc1EtherformMoveMap.bind(keyboard, lcontrol, XaNotc1CatMoveMap_doSlide);

XaNotc1EtherformMoveMap.bind( mouse, xaxis, XaNotc1CatMoveMap_yaw );
XaNotc1EtherformMoveMap.bind( mouse, yaxis, XaNotc1CatMoveMap_pitch );

XaNotc1EtherformMoveMap.bind( mouse, button0, XaNotc1CatMoveMap_trigger0 );
XaNotc1EtherformMoveMap.bind( mouse, button1, XaNotc1CatMoveMap_trigger1 );
XaNotc1EtherformMoveMap.bind( mouse, button2, XaNotc1CatMoveMap_trigger3 );

