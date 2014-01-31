// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Anim flag settings - must match material.h
// These cannot be enumed through script becuase it cannot
// handle the "|" operation for combining them together
// ie. Scroll | Wave does not work.
//-----------------------------------------------------------------------------
$scroll = 1;
$rotate = 2;
$wave   = 4;
$scale  = 8;
$sequence = 16;


// Common stateblock definitions
new GFXSamplerStateData(SamplerClampLinear)
{
   textureColorOp = GFXTOPModulate;
   addressModeU = GFXAddressClamp;
   addressModeV = GFXAddressClamp;
   addressModeW = GFXAddressClamp;
   magFilter = GFXTextureFilterLinear;
   minFilter = GFXTextureFilterLinear;
   mipFilter = GFXTextureFilterLinear;
};

new GFXSamplerStateData(SamplerClampPoint)
{
   textureColorOp = GFXTOPModulate;
   addressModeU = GFXAddressClamp;
   addressModeV = GFXAddressClamp;
   addressModeW = GFXAddressClamp;
   magFilter = GFXTextureFilterPoint;
   minFilter = GFXTextureFilterPoint;
   mipFilter = GFXTextureFilterPoint;
};

new GFXSamplerStateData(SamplerWrapLinear)
{
   textureColorOp = GFXTOPModulate;
   addressModeU = GFXTextureAddressWrap;
   addressModeV = GFXTextureAddressWrap;
   addressModeW = GFXTextureAddressWrap;
   magFilter = GFXTextureFilterLinear;
   minFilter = GFXTextureFilterLinear;
   mipFilter = GFXTextureFilterLinear;
};

new GFXSamplerStateData(SamplerWrapPoint)
{
   textureColorOp = GFXTOPModulate;
   addressModeU = GFXTextureAddressWrap;
   addressModeV = GFXTextureAddressWrap;
   addressModeW = GFXTextureAddressWrap;
   magFilter = GFXTextureFilterPoint;
   minFilter = GFXTextureFilterPoint;
   mipFilter = GFXTextureFilterPoint;
};
