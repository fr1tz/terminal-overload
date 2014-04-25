// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton ShaderData( GammaShader )
{
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/gammaP.hlsl";

   OGLVertexShaderFile  = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile   = "shaders/common/postFx/gl/gammaP.glsl";
   
   samplerNames[0] = "$backBuffer";
   samplerNames[1] = "$colorCorrectionTex";

   pixVersion = 2.0;   
};

singleton GFXStateBlockData( GammaStateBlock : PFX_DefaultStateBlock )
{
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;
   samplerStates[1] = SamplerClampLinear; 
};

singleton PostEffect( GammaPostFX )
{
   isEnabled = true;
   allowReflectPass = false;
   
   renderTime = "PFXBeforeBin";
   renderBin = "EditorBin";
   renderPriority = 9999;
      
   shader = GammaShader;
   stateBlock = GammaStateBlock;
   
   texture[0] = "$backBuffer";  
   texture[1] = $HDRPostFX::colorCorrectionRamp;  
};

function GammaPostFX::preProcess( %this )
{
   if ( %this.texture[1] !$= $HDRPostFX::colorCorrectionRamp )
      %this.setTexture( 1, $HDRPostFX::colorCorrectionRamp );         
}

function GammaPostFX::setShaderConsts( %this )
{
   %clampedGamma  = mClamp( $pref::Video::Gamma, 0.001, 2.2);
   %this.setShaderConst( "$OneOverGamma", 1 / %clampedGamma );
}