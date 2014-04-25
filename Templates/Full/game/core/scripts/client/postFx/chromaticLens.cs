// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/// 
$CAPostFx::enabled = false;

/// The lens distortion coefficient.
$CAPostFx::distCoeffecient =  -0.05;

/// The cubic distortion value.
$CAPostFx::cubeDistortionFactor =  -0.1;

/// The amount and direction of the maxium shift for
/// the red, green, and blue channels.
$CAPostFx::colorDistortionFactor = "0.005 -0.005 0.01";


singleton GFXStateBlockData( PFX_DefaultChromaticLensStateBlock )
{
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;   
   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;
};

singleton ShaderData( PFX_ChromaticLensShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/chromaticLens.hlsl"; 
   
   OGLVertexShaderFile  = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile   = "shaders/common/postFx/gl/chromaticLens.glsl";
   
   samplerNames[0] = "$backBuffer";
   
   pixVersion = 3.0;
};

singleton PostEffect( ChromaticLensPostFX )
{
   renderTime = "PFXAfterDiffuse";
   renderPriority = 0.2;
   isEnabled = false;
   allowReflectPass = false;

   shader = PFX_ChromaticLensShader;
   stateBlock = PFX_DefaultChromaticLensStateBlock;
   texture[0] = "$backBuffer";
   target = "$backBuffer";
};

function ChromaticLensPostFX::setShaderConsts( %this )
{
   %this.setShaderConst( "$distCoeff", $CAPostFx::distCoeffecient );   
   %this.setShaderConst( "$cubeDistort", $CAPostFx::cubeDistortionFactor );    
   %this.setShaderConst( "$colorDistort", $CAPostFx::colorDistortionFactor );   
}
