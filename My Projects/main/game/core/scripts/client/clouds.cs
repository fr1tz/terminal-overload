// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//------------------------------------------------------------------------------
// CloudLayer
//------------------------------------------------------------------------------

singleton ShaderData( CloudLayerShader )
{
   DXVertexShaderFile   = "shaders/common/cloudLayerV.hlsl";
   DXPixelShaderFile    = "shaders/common/cloudLayerP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/gl/cloudLayerV.glsl";
   OGLPixelShaderFile = "shaders/common/gl/cloudLayerP.glsl";
      
   pixVersion = 2.0;   
};

//------------------------------------------------------------------------------
// BasicClouds
//------------------------------------------------------------------------------

singleton ShaderData( BasicCloudsShader )
{
   DXVertexShaderFile   = "shaders/common/basicCloudsV.hlsl";
   DXPixelShaderFile    = "shaders/common/basicCloudsP.hlsl";
   
   //OGLVertexShaderFile = "shaders/common/gl/basicCloudsV.glsl";
   //OGLPixelShaderFile = "shaders/common/gl/basicCloudsP.glsl";
      
   pixVersion = 2.0;   
};
