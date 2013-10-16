// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function ShapeBaseData::clientAction(%this, %obj, %nr)
{
   if(%nr == 19)
      Game.clientLeaveForm(%obj.client, %obj);
}

