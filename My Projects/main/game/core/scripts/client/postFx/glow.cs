// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


singleton ShaderData( PFX_GlowBlurVertShader )
{
   DXVertexShaderFile 	= "shaders/common/postFx/glowBlurV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/glowBlurP.hlsl";
   
   OGLVertexShaderFile  = "shaders/common/postFx/gl/glowBlurV.glsl";
   OGLPixelShaderFile   = "shaders/common/postFx/gl/glowBlurP.glsl";
      
   defines = "BLUR_DIR=float2(0.0,1.0)";

   samplerNames[0] = "$diffuseMap";
         
   pixVersion = 2.0;
};


singleton ShaderData( PFX_GlowBlurHorzShader : PFX_GlowBlurVertShader )
{
   defines = "BLUR_DIR=float2(4.0,0.0)";
};


singleton GFXStateBlockData( PFX_GlowCombineStateBlock : PFX_DefaultStateBlock )
{
   // Use alpha test to save some fillrate 
   // on the non-glowing areas of the scene.
   alphaDefined = true;
   alphaTestEnable = true;
   alphaTestRef = 1;
   alphaTestFunc = GFXCmpGreaterEqual;
         
   // Do a one to one blend.
   blendDefined = true;
   blendEnable = true;
   blendSrc = GFXBlendOne;
   blendDest = GFXBlendOne;   
};


singleton PostEffect( GlowPostFx )
{  
   // Do not allow the glow effect to work in reflection 
   // passes by default so we don't do the extra drawing.
   allowReflectPass = false;
                  
   renderTime = "PFXAfterBin";
   renderBin = "GlowBin";
   renderPriority = 1;
                    
   // First we down sample the glow buffer.   
   shader = PFX_PassthruShader;
   stateBlock = PFX_DefaultStateBlock;
   texture[0] = "#glowbuffer";
   target = "$outTex";
   targetScale = "1.0 1.0";
   
   isEnabled = true;
               
   // Blur vertically
   new PostEffect()
   {
      shader = PFX_GlowBlurVertShader;
      stateBlock = PFX_DefaultStateBlock;
      texture[0] = "$inTex";
      target = "$outTex";
   };
   
   // Blur horizontally
   new PostEffect()
   {
      shader = PFX_GlowBlurHorzShader;
      stateBlock = PFX_DefaultStateBlock;
      texture[0] = "$inTex";
      target = "$outTex";
   };
            
   // Upsample and combine with the back buffer.
   new PostEffect()
   {      
      shader = PFX_PassthruShader;
      stateBlock = PFX_GlowCombineStateBlock;
      texture[0] = "$inTex";
      target = "$backBuffer";
   };
};
