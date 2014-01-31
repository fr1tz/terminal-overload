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

singleton SFXDescription( AudioDefault3D : AudioEffect )
{
   is3D              = true;
   ReferenceDistance = 20.0;
   MaxDistance       = 100.0;
};

singleton SFXDescription( AudioSoft3D : AudioEffect )
{
   is3D              = true;
   ReferenceDistance = 20.0;
   MaxDistance       = 100.0;
   volume = 0.4;
};

singleton SFXDescription( AudioClose3D : AudioEffect )
{
   is3D              = true;
   ReferenceDistance = 10.0;
   MaxDistance       = 60.0;
};

singleton SFXDescription( AudioClosest3D : AudioEffect )
{
   is3D              = true;
   ReferenceDistance = 5.0;
   MaxDistance       = 10.0;
};

//-----------------------------------------------------------------------------
// Looping sounds
//-----------------------------------------------------------------------------

singleton SFXDescription( AudioDefaultLoop3D : AudioEffect )
{
   isLooping         = true;
   is3D              = true;
   ReferenceDistance = 20.0;
   MaxDistance       = 100.0;
};

singleton SFXDescription( AudioCloseLoop3D : AudioEffect )
{
   isLooping         = true;
   is3D              = true;
   ReferenceDistance = 18.0;
   MaxDistance       = 25.0;
};

singleton SFXDescription( AudioClosestLoop3D : AudioEffect )
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
singleton SFXDescription( Audio2D : AudioEffect )
{
   isLooping         = false;
};

// Used for Looping Environmental Sounds
singleton SFXDescription( AudioLoop2D : AudioEffect )
{
   isLooping         = true;
};

singleton SFXDescription( AudioStream2D : AudioEffect )
{
   isStreaming       = true;
};
singleton SFXDescription( AudioStreamLoop2D : AudioEffect )
{
   isLooping         = true;
   isStreaming       = true;
};

//-----------------------------------------------------------------------------
// GUI
//-----------------------------------------------------------------------------

// Used for Looping GUI Sounds
singleton SFXDescription( AudioGuiLoop2D : AudioGui )
{
   isLooping         = true;
};

//-----------------------------------------------------------------------------
// Music
//-----------------------------------------------------------------------------

singleton SFXDescription( AudioMusic2D : AudioMusic )
{
   isStreaming       = true;
};

singleton SFXDescription( AudioMusicLoop2D : AudioMusic )
{
   isLooping         = true;
   isStreaming       = true;
};

singleton SFXDescription( AudioMusic3D : AudioMusic )
{
   isStreaming       = true;
   is3D              = true;
};

singleton SFXDescription( AudioMusicLoop3D : AudioMusic )
{
   isStreaming       = true;
   is3D              = true;
   isLooping         = true;
};
