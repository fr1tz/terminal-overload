// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

function createExplosion(%data, %pos, %norm)
{
	%visibleDistance = 1000; // getVisibleDistance(); FIXME
	%count = ClientGroup.getCount();
	for(%i = 0; %i < %count; %i++)
	{
		%client = ClientGroup.getObject(%i);
		if(%client.ingame $= "")
			continue;

		%control = %client.getControlObject();
		%dist = VectorLen(VectorSub(%pos, %control.getPosition()));

		// can the player potentially see it?
		if(%dist <= %visibleDistance)
		{
			createExplosionOnClient(%client, %data, %pos, %norm);
		}
		else
		{
			// Perhaps the player can hear it?
			// (The 'play3D' engine method does the distance check.)
			%soundProfile = %data.soundProfile;
			if(isObject(%soundProfile))
				%client.play3D(%soundProfile, %pos);
		}
	}
}
