// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


new ShaderData(BlurDepthShader)
{
   DXVertexShaderFile = "shaders/common/lighting/shadowMap/boxFilterV.hlsl";
   DXPixelShaderFile  = "shaders/common/lighting/shadowMap/boxFilterP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/lighting/shadowMap/gl/boxFilterV.glsl";
   OGLPixelShaderFile = "shaders/common/lighting/shadowMap/gl/boxFilterP.glsl";
   pixVersion = 2.0;
};
