// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function GameConnection::MinimapHud_SetHudInfoDatasetType_Color(%client, %type)
{
   commandToClient(%client, '_XaNotcMinimapHud_SetHudInfoDatasetType_Color', %type);
}

function GameConnection::MinimapHud_SetHudInfoDatasetType_Icon(%client, %type)
{
   commandToClient(%client, '_XaNotcMinimapHud_SetHudInfoDatasetType_Icon', %type);
}

function GameConnection::MinimapHud_ClearColors(%client)
{
   commandToClient(%client, '_XaNotcMinimapHud_ClearColors');
}

function GameConnection::MinimapHud_ClearIcons(%client)
{
   commandToClient(%client, '_XaNotcMinimapHud_ClearIcons');
}

function GameConnection::MinimapHud_AddColor(%client, %id, %colorF)
{
   %colorI = getWord(%colorF, 0)*255 SPC
             getWord(%colorF, 1)*255 SPC
             getWord(%colorF, 2)*255 SPC
             255;
   commandToClient(%client, '_XaNotcMinimapHud_AddColor', %id, %colorI);
}

function GameConnection::MinimapHud_AddIcon(%client, %id, %bitmap, %size)
{
   commandToClient(%client, '_XaNotcMinimapHud_AddIcon', %id, %bitmap, %size);
}

