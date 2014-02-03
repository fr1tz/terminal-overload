// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

new GFXStateBlockData( ScatterSkySBData )
{
   cullDefined = true;
   cullMode = "GFXCullNone";
   
   zDefined = true;
   zEnable = true;
   zWriteEnable = false;
   zFunc = "GFXCmpLessEqual";
   
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;   
   samplerStates[1] = SamplerClampLinear;
   vertexColorEnable = true;
};

singleton ShaderData( ScatterSkyShaderData )
{
   DXVertexShaderFile     = "shaders/common/scatterSkyV.hlsl";
   DXPixelShaderFile      = "shaders/common/scatterSkyP.hlsl";   
   
   OGLVertexShaderFile     = "shaders/common/gl/scatterSkyV.glsl";
   OGLPixelShaderFile      = "shaders/common/gl/scatterSkyP.glsl";   
   
   samplerNames[0] = "$nightSky";
   
   pixVersion = 2.0;
};
