// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Pieces:
// 0  Infantry
// 1  Anti-Soil
// 2  Brick

function FrontlineGame::piece2String(%game, %piece)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::piece2String");
   switch(%piece)
   {
      case 0:  return "Infantry";
      case 1:  return "Anti-Soil";
      case 2:  return "Brick";
   }
}

function FrontlineGame::resetResources1(%game, %client, %piece, %current, %max, %limit, %cost)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::resetResources1");
   %client.resources.pieceExists[%piece] = true;
   %client.resources.pieceUsed[%piece]   = 0;
   %client.resources.pieceCount[%piece]  = %current;
   %client.resources.pieceMax[%piece]    = %max;
   %client.resources.pieceLimit[%piece]  = %limit;
   %client.resources.pieceCost[%piece]   = %cost;
}

function FrontlineGame::resetResources(%game, %client)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::resetResources");
   %game.resetResources1(%client, 0, 1, 1, true, 20); // Infantry
   %game.resetResources1(%client, 1, 0, 1, true, 10); // Anti-Soil
   %game.resetResources1(%client, 2, 0, 25, false, 2); // Brick
   %game.displayResources(%client);
}

function FrontlineGame::updateResourcesThread(%game, %client)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::updateResourcesThread");

	cancel(%client.updateResourcesThread);
	%client.updateResourcesThread = %game.schedule(1000, "updateResourcesThread", %client);

   if(!isObject(%client.resources))
      return;
      
   %piece = 0;
   while(%client.resources.pieceExists[%piece])
   {
      %oldCount = %client.resources.pieceCount[%piece];
      %newCount = %oldCount + 1 / %client.resources.pieceCost[%piece];
      if(%newCount > %client.resources.pieceMax[%piece])
         %newCount = %client.resources.pieceMax[%piece];

      %client.resources.pieceCount[%piece] = %newCount;
      
      if(%piece == 0)
      {
         if(%client.player.getClassName() $= "Etherform")
            %client.player.updateVisuals();
      }

      //if(mFloor(%newCount) > mFloor(%oldCount))
         %game.displayResources(%client);

      %piece++;
   }
}

function FrontlineGame::displayResources(%game, %client)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::displayResources");

   %text = "";
   %pieceOrder = "0 1 2";
   %j = 0;
   while(%j < 100)
   {
      %piece = getWord(%pieceOrder, %j);

      if(%client.resources.pieceExists[%piece] $= "")
         break;

      %pieceString = %game.piece2String(%piece);
      %used = %client.resources.pieceUsed[%piece];
      %free = %client.resources.pieceCount[%piece] - %used;
      
      if(%client.resources.pieceLimit[%piece])
         %text = %text @ %pieceString @ ": " @ %free SPC "[" SPC %used SPC "]\n";
      else
         %text = %text @ %pieceString @ ": " @ %free @ "\n";

      %j++;
   }
   
   commandToClient(%client, 'LeftPrint', "");
	%l = strlen(%text); %n = 0;
	while(%n < %l)
	{
		%chunk = getSubStr(%text, %n, 255);
		commandToClient(%client, 'LeftPrint', %chunk);
		%n += 255;
	}
}
