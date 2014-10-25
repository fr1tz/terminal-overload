// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function GameConnection::HudIcons_SetHudInfoDatasetType_Color(%client, %type)
{
   commandToClient(%client, '_XaNotcHudIcons_SetHudInfoDatasetType_Color', %type);
}

function GameConnection::HudIcons_SetHudInfoDatasetType_Icon(%client, %type)
{
   commandToClient(%client, '_XaNotcHudIcons_SetHudInfoDatasetType_Icon', %type);
}

function GameConnection::HudIcons_ClearColors(%client)
{
   commandToClient(%client, '_XaNotcHudIcons_ClearColors');
}

function GameConnection::HudIcons_ClearIcons(%client)
{
   commandToClient(%client, '_XaNotcHudIcons_ClearIcons');
}

function GameConnection::HudIcons_AddColor(%client, %id, %colorF)
{
   %colorI = mFloatLength(getWord(%colorF, 0)*255, 0) SPC
             mFloatLength(getWord(%colorF, 1)*255, 0) SPC
             mFloatLength(getWord(%colorF, 2)*255, 0) SPC
             255;
   commandToClient(%client, '_XaNotcHudIcons_AddColor', %id, %colorI);
}

function GameConnection::HudIcons_AddIcon(%client, %id, %bitmap, %size)
{
   commandToClient(%client, '_XaNotcHudIcons_AddIcon', %id, %bitmap, %size);
}

