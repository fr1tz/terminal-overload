// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function GameCoreDM::onUnitDestroyed(%game, %obj)
{
   echo(%game @"\c4 -> "@ %game.class @" -> GameCoreDM::onUnitDestroyed");

   RESO::spawnDisc(%obj.client);
}

