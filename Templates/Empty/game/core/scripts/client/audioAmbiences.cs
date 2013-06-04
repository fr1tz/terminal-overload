// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


singleton SFXAmbience( AudioAmbienceDefault )
{
   environment = AudioEnvOff;
};

singleton SFXAmbience( AudioAmbienceOutside )
{
   environment = AudioEnvPlain;
   states[ 0 ] = AudioLocationOutside;
};

singleton SFXAmbience( AudioAmbienceInside )
{
   environment = AudioEnvRoom;
   states[ 0 ] = AudioLocationInside;
};

singleton SFXAmbience( AudioAmbienceUnderwater )
{
   environment = AudioEnvUnderwater;
   states[ 0 ] = AudioLocationUnderwater;
};
