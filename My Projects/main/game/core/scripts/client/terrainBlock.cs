// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/// Used when generating the blended base texture.
singleton ShaderData( TerrainBlendShader )
{
   DXVertexShaderFile   = "shaders/common/terrain/blendV.hlsl";
   DXPixelShaderFile    = "shaders/common/terrain/blendP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/terrain/gl/blendV.glsl";
   OGLPixelShaderFile = "shaders/common/terrain/gl/blendP.glsl";
   
   pixVersion = 2.0;
};
