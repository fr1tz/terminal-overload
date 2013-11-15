// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function FrontlineGame::loadDefaultUnit(%game, %client, %slot)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::loadDefaultUnit");
   switch(%slot)
   {
      case 1:
         %client.unitName[%slot] = "Brick";
         %client.unitCode[%slot] = "10";
      case 11:
         %client.unitName[%slot] = "Soldier w/ Raptor";
         %client.unitCode[%slot] = "1 1";
      case 12:
         %client.unitName[%slot] = "Soldier w/ Siberion";
         %client.unitCode[%slot] = "1 2";
      default:
         %client.unitName[%slot] = "";
         %client.unitCode[%slot] = "";
   }
}

function FrontlineGame::unitcode2SpawnMode(%game, %code)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::unitcode2SpawnMode");
   %arg1 = getWord(%code, 0);
   switch(%arg1)
   {
      case 1: return "transform"; // Soldier
      default: return "build";
   }
}

function FrontlineGame::unitcode2SpawnFunc(%game, %code)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::unitcode2SpawnFunc");
   %arg1 = getWord(%code, 0);
   switch(%arg1)
   {
      case  1: return "Spawn_Soldierpod"; // Soldier
      case 10: return "Spawn_Brick";      // Brick
      default: return "";
   }
}

function FrontlineGame::unitcode2Pieces(%game, %code)
{
   //echo(%game @"\c4 -> "@ %game.class @" -> FrontlineGame::unitcode2Pieces");
   %pieces = "";
   %arg1 = getWord(%code, 0);
   if(%arg1 == 1) // Soldier
   {
      %pieces = "0 1";
      %arg2 = getWord(%code, 4);
      if(%arg2 == 1)
         %pieces = %pieces; // TAB "4 1";
      else if(%arg2 == 2)
         %pieces = %pieces TAB "5 1";
      else if(%arg2 == 3)
         %pieces = %pieces TAB "6 1";
      else if(%arg2 == 4)
         %pieces = %pieces TAB "7 1";
      else if(%arg2 == 5)
         %pieces = %pieces TAB "8 1";
      else if(%arg2 == 6)
         %pieces = %pieces TAB "6 1";
   }
   else if(%arg1 == 3)
   {
      %pieces = "3 1"; // Box
   }
   else if(%arg1 == 2)
   {
      %pieces = "2 1"; // Bumblebee
   }
   else if(%arg1 == 1) // Parrot
   {
      %pieces = "1 1";
   }
   else if(%arg1 == 5) // Pillar
   {
      %pieces = "3 2";
   }
   else if(%arg1 == 6) // Hoverpod
   {
      %pieces = "9 1";
   }
   else if(%arg1 == 7) // Hovercycle
   {
      %pieces = "9 1";
   }
   else if(%arg1 == 10) // Brick
   {
      %pieces = "2 1";
   }
   return %pieces;
}
