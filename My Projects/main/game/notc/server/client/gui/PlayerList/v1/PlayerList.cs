// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function GameConnection::PlayerList_start(%client, %update)
{
   commandToClient(%client, '_XaNotcPlayerList_start', %update);
}

function GameConnection::PlayerList_add(%client, %text, %layerMask)
{
	%l = strlen(%text); %n = 0;
	while(%n < %l)
	{
		%chunk = getSubStr(%text, %n, 255);
		commandToClient(%client, '_XaNotcPlayerList_add', %chunk, %layerMask);
		%n += 255;
	}
}

function GameConnection::PlayerList_finish(%client)
{
   commandToClient(%client, '_XaNotcPlayerList_finish');
}


