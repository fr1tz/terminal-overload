// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton GFXStateBlockData( PFX_TurbulenceStateBlock : PFX_DefaultStateBlock)  
{  
   zDefined = false;
   zEnable = false;  
   zWriteEnable = false;  
        
   samplersDefined = true;  
   samplerStates[0] = SamplerClampLinear;
};  
  
singleton ShaderData( PFX_TurbulenceShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/turbulenceP.hlsl";
           
   OGLVertexShaderFile  = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile   = "shaders/common/postFx/gl/turbulenceP.glsl";
           
   samplerNames[0] = "$inputTex";
   pixVersion = 3.0;
};

singleton PostEffect( TurbulenceFx )  
{  
   isEnabled = false;    
   allowReflectPass = true;  
         
   renderTime = "PFXAfterBin";
   renderBin = "GlowBin";
   renderPriority = 0.5; // Render after the glows themselves
     
   shader = PFX_TurbulenceShader;  
   stateBlock=PFX_TurbulenceStateBlock;
   texture[0] = "$backBuffer";      
 };
