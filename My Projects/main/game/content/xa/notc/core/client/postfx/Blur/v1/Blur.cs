// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton PostEffect(NotcBlurPostFx)
{
   renderTime = "PFXAfterDiffuse";
   renderPriority = 0.2;
   isEnabled = false;
   allowReflectPass = false;
   
   shader = PFX_PassthruShader;
   stateBlock = PFX_DefaultStateBlock;
   texture[0] = "$backBuffer";
   target = "$outTex";
   targetScale = "1.0 1.0";
   
   singleton PostEffect(NotcBlurPostFx2)
   {
      shader = PFX_PassthruShader;
      stateBlock = PFX_DefaultStateBlock;
      texture[0] = "$inTex";
      target = "$backBuffer";
   };
};

function NotcBlurPostFx::setShaderConsts( %this )
{

}
