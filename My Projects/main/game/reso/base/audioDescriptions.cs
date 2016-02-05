// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Always declare SFXDescription's (the type of sound) before SFXProfile's (the
// sound itself) when creating new ones

//-----------------------------------------------------------------------------
// 3D Sounds
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Single shot sounds
//-----------------------------------------------------------------------------

datablock SFXDescription( AudioDefault3D : AudioEffect )
{
   is3D              = true;
   ReferenceDistance = 20.0;
   MaxDistance       = 100.0;
};

datablock SFXDescription( AudioSoft3D : AudioEffect )
{
   is3D              = true;
   ReferenceDistance = 20.0;
   MaxDistance       = 100.0;
   volume = 0.4;
};

datablock SFXDescription( AudioClose3D : AudioEffect )
{
   is3D              = true;
   ReferenceDistance = 10.0;
   MaxDistance       = 60.0;
};

datablock SFXDescription( AudioClosest3D : AudioEffect )
{
   is3D              = true;
   ReferenceDistance = 5.0;
   MaxDistance       = 10.0;
};

//-----------------------------------------------------------------------------
// Looping sounds
//-----------------------------------------------------------------------------

datablock SFXDescription( AudioDefaultLoop3D : AudioEffect )
{
   isLooping         = true;
   is3D              = true;
   ReferenceDistance = 20.0;
   MaxDistance       = 100.0;
};

datablock SFXDescription( AudioCloseLoop3D : AudioEffect )
{
   isLooping         = true;
   is3D              = true;
   ReferenceDistance = 18.0;
   MaxDistance       = 25.0;
};

datablock SFXDescription( AudioClosestLoop3D : AudioEffect )
{
   isLooping         = true;
   is3D              = true;
   ReferenceDistance = 5.0;
   MaxDistance       = 10.0;
};

//-----------------------------------------------------------------------------
// 2d sounds
//-----------------------------------------------------------------------------

// Used for non-looping environmental sounds (like power on, power off)
datablock SFXDescription( Audio2D : AudioEffect )
{
   isLooping         = false;
};

// Used for Looping Environmental Sounds
datablock SFXDescription( AudioLoop2D : AudioEffect )
{
   isLooping         = true;
};

datablock SFXDescription( AudioStream2D : AudioEffect )
{
   isStreaming       = true;
};
datablock SFXDescription( AudioStreamLoop2D : AudioEffect )
{
   isLooping         = true;
   isStreaming       = true;
};

//-----------------------------------------------------------------------------
// GUI
//-----------------------------------------------------------------------------

// Used for Looping GUI Sounds
datablock SFXDescription( AudioGuiLoop2D : AudioGui )
{
   isLooping         = true;
};

//-----------------------------------------------------------------------------
// Music
//-----------------------------------------------------------------------------

datablock SFXDescription( AudioMusic2D : AudioMusic )
{
   isStreaming       = true;
};

datablock SFXDescription( AudioMusicLoop2D : AudioMusic )
{
   isLooping         = true;
   isStreaming       = true;
};

datablock SFXDescription( AudioMusic3D : AudioMusic )
{
   isStreaming       = true;
   is3D              = true;
};

datablock SFXDescription( AudioMusicLoop3D : AudioMusic )
{
   isStreaming       = true;
   is3D              = true;
   isLooping         = true;
};
