// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

$VignettePostEffect::RadiusX = 0.6;
$VignettePostEffect::RadiusY = 0.2;

singleton ShaderData( VignetteShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/vignette/VignetteP.hlsl";
   pixVersion = 2.0;
};

singleton PostEffect( VignettePostEffect )  
{  
   isEnabled         = false;
   allowReflectPass  = false;
   renderTime        = "PFXAfterBin";
   renderBin         = "GlowBin";
   shader            = VignetteShader;
   stateBlock        = PFX_DefaultStateBlock;
   texture[0]        = "$backBuffer";
   renderPriority    = 10;
};

function VignettePostEffect::setShaderConsts(%this)
{
   %this.setShaderConst("$radiusX", $VignettePostEffect::RadiusX);
   %this.setShaderConst("$radiusY", $VignettePostEffect::RadiusY);
}
