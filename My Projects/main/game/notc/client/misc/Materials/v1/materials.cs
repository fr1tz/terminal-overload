// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function GameConnection::Materials_Clear(%client)
{
   commandToClient(%client, '_XaNotcMaterials_Clear');
}

function GameConnection::Materials_Load(%client, %pathMask)
{
   commandToClient(%client, '_XaNotcMaterials_Load', %pathMask);
}

