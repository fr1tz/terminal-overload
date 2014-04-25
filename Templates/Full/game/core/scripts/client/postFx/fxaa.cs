// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// An implementation of "NVIDIA FXAA 3.11" by TIMOTHY LOTTES
//
// http://timothylottes.blogspot.com/
//
// The shader is tuned for the defaul quality and good performance.
// See shaders\common\postFx\fxaa\fxaaP.hlsl to tweak the internal
// quality and performance settings.

singleton GFXStateBlockData( FXAA_StateBlock : PFX_DefaultStateBlock )
{   
   samplersDefined = true;   
   samplerStates[0] = SamplerClampLinear;
};

singleton ShaderData( FXAA_ShaderData )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/fxaa/fxaaV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/fxaa/fxaaP.hlsl";
   
   OGLVertexShaderFile  = "shaders/common/postFx/fxaa/gl/fxaaV.glsl";
   OGLPixelShaderFile   = "shaders/common/postFx/fxaa/gl/fxaaP.glsl";
   
   samplerNames[0] = "$colorTex";

   pixVersion = 3.0;
};

singleton PostEffect( FXAA_PostEffect )
{
   isEnabled = false;
   
   allowReflectPass = false;
   renderTime = "PFXAfterDiffuse";

   texture[0] = "$backBuffer";      

   target = "$backBuffer";

   stateBlock = FXAA_StateBlock;
   shader = FXAA_ShaderData;
};

