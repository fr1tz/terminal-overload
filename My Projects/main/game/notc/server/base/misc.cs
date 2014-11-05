// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

datablock PrecipitationData(Precipitation_Snow)
{
   //soundProfile = "HeavyRainSound";

   dropTexture = "content/xa/rotc/p.5.4/textures/nat/snowflakes";
   splashTexture = "content/xa/torque3d/3.0/environment/precipitation/water_splash";
   dropSize = 0.35;
   splashSize = 0.1;
   useTrueBillboards = false;
   splashMS = 500;
};

function isValidPlayerColor(%colori)
{
   %numWords = getWordCount(%colori);
   
   if(%numWords != 3)
      return false;
      
   %total = 0;
   for(%i = 0; %i < %numWords; %i++)
   {
      %c = getWord(%colori, %i);
      if(%c < 0 || %c > 255)
         return false;
         
      %total += %c;
   }
   
   if(%total < 255)
      return false;
   
   return true;
}

function byteToHex(%byte)
{
   %chars = "0123456789ABCDEF";
   %digit[0] = "0";
   %digit[1] = "0";
   if(%byte > 15)
      %digit[0] = getSubStr(%chars, %byte / 16, 1);
   %digit[1] = getSubStr(%chars, %byte % 16, 1);
   return %digit[0] @ %digit[1];
}

function createExplosion(%data, %pos, %norm, %colorI)
{
	%visibleDistance = theLevelInfo.visibleDistance;
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
         commandToClient(%client,
            'CreateExplosion',
            %data.getId(),
            %pos,
            %norm,
            %colorI
         );
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
