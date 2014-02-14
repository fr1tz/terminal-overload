// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

$PostFX::MotionBlur::VelMul = 10;

singleton ShaderData( PFX_MotionBlurShader )  
{     
   DXVertexShaderFile   = "shaders/common/postFx/postFxV.hlsl";  //we use the bare-bones postFxV.hlsl
   DXPixelShaderFile    = "shaders/common/postFx/motionBlurP.hlsl";  //new pixel shader
   
   OGLVertexShaderFile   = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile    = "shaders/common/postFx/gl/motionBlurP.glsl";
   
   samplerNames[0] = "$backBuffer";
   samplerNames[1] = "$prepassTex";
   
   pixVersion = 3.0;  
};  

singleton PostEffect(MotionBlurFX)  
{
   isEnabled = false;

   renderTime = "PFXAfterDiffuse";  

   shader = PFX_MotionBlurShader;  
   stateBlock = PFX_DefaultStateBlock;  
   texture[0] = "$backbuffer";
   texture[1] = "#prepass";
   target = "$backBuffer";
};

function MotionBlurFX::setShaderConsts(%this)
{
   %this.setShaderConst("$velocityMultiplier", $PostFX::MotionBlur::VelMul);
}
