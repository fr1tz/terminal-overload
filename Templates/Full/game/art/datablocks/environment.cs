// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// ENVIROMENTAL EFFECTS GO HERE (PRECIPITATION - LIGHTNING)

// ----------------------------------------------------------------------------
// Rain
// ----------------------------------------------------------------------------

datablock SFXProfile(HeavyRainSound)
{
   filename = "art/sound/environment/amb";
   description = AudioLoop2d;
};

datablock PrecipitationData(HeavyRain)
{
   soundProfile = "HeavyRainSound";

   dropTexture = "art/environment/precipitation/rain";
   splashTexture = "art/environment/precipitation/water_splash";
   dropSize = 0.35;
   splashSize = 0.1;
   useTrueBillboards = false;
   splashMS = 500;
};

// ----------------------------------------------------------------------------
// Lightning
// ----------------------------------------------------------------------------

// When setting up thunder sounds for lightning it should be known that:
// - strikeSound is a 3d sound
// - thunderSounds[n] are 2d sounds

datablock SFXProfile(ThunderCrash1Sound)
{
   filename = "art/sound/environment/thunder1";
   description = Audio2d;
};

datablock SFXProfile(ThunderCrash2Sound)
{
   filename = "art/sound/environment/thunder2";
   description = Audio2d;
};

datablock SFXProfile(ThunderCrash3Sound)
{
   filename = "art/sound/environment/thunder3";
   description = Audio2d;
};

datablock SFXProfile(ThunderCrash4Sound)
{
   filename = "art/sound/environment/thunder4";
   description = Audio2d;
};


datablock LightningData(DefaultStorm)
{
   thunderSounds[0] = ThunderCrash1Sound;
   thunderSounds[1] = ThunderCrash2Sound;
   thunderSounds[2] = ThunderCrash3Sound;
   thunderSounds[3] = ThunderCrash4Sound;
};
