// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock SFXProfile(BeepMessageSound)
{
   filename = "content/xa/rotc/p.5.4/sounds/rotc/denied1";
   description = AudioGui;
   preload = true;
};

function GameConnection::BeepMsg(%client, %msg)
{
   if(%client.zClearBeepMsgThread !$= "")
      cancel(%client.zClearBeepMsgThread);
   %client.zClearBeepMsgThread = schedule(3000, MissionGroup, "clearBottomPrint", %client);
   commandToClient(%client, 'BottomPrint', %msg, 3000, 1);
	%client.play2D(BeepMessageSound);
}


