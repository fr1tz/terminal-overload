// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton GFXStateBlockData( PFX_CausticsStateBlock : PFX_DefaultStateBlock )
{
   blendDefined = true;
   blendEnable = true; 
   blendSrc = GFXBlendOne;
   blendDest = GFXBlendOne;
   
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;
   samplerStates[1] = SamplerWrapLinear;
   samplerStates[2] = SamplerWrapLinear;
};

singleton ShaderData( PFX_CausticsShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/caustics/causticsP.hlsl";
         
   OGLVertexShaderFile  = "shaders/common/postFx/gl//postFxV.glsl";
   OGLPixelShaderFile   = "shaders/common/postFx/caustics/gl/causticsP.glsl";
      
   samplerNames[0] = "$prepassTex";
   samplerNames[1] = "$causticsTex0";
   samplerNames[2] = "$causticsTex1";
   
   pixVersion = 3.0;
};

singleton PostEffect( CausticsPFX )
{
   isEnabled = false;
   renderTime = "PFXBeforeBin";
   renderBin = "ObjTranslucentBin";      
   //renderPriority = 0.1;
      
   shader = PFX_CausticsShader;
   stateBlock = PFX_CausticsStateBlock;
   texture[0] = "#prepass";
   texture[1] = "textures/caustics_1";
   texture[2] = "textures/caustics_2";
   target = "$backBuffer";
};
