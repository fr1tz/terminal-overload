// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function ETH::updatePlayerList(%client)
{
   %team[0] = "";
   %team[1] = "";
   %team[2] = "";
   
   %count = ClientGroup.getCount();
   for(%i = 0; %i < %count; %i++)
   {
      %c = ClientGroup.getObject(%i);
      %teamId = %c.team.teamId;
      %name = %client.playerName;
      %ping = %client.getPing();
      %team[%teamId] = %team[%teamId] TAB %name TAB %ping @ "\n";
   }
   
   %t = "<color:ffffff>";
   %t = %t @ "<tab:10, 150, 200, 250, 350>";
   %t = %t @ "\tName\tPing<br><br>";
   %t = %t @ "Team1: <br>";
   %t = %t @ %team1;
   %t = %t @ "<br> Team2: <br>";
   %t = %t @ %team2;
   %t = %t @ "<br> Unassigned: <br>";
   %t = %t @ %team0;

   %client.PlayerList_start(true);
   %client.PlayerList_add(%t);
   %client.PlayerList_finish();
}

