// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


singleton GFXStateBlockData( PFX_DefaultEdgeAAStateBlock )
{
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;
      
   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;
   //samplerStates[1] = SamplerWrapPoint;
};

singleton ShaderData( PFX_EdgeAADetectShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/edgeaa/edgeDetectP.hlsl";
         
   //OGLVertexShaderFile  = "shaders/common/postFx/gl//postFxV.glsl";
   //OGLPixelShaderFile   = "shaders/common/postFx/gl/passthruP.glsl";
      
   samplerNames[0] = "$inputTex";
   
   pixVersion = 3.0;
};

singleton ShaderData( PFX_EdgeAAShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/edgeaa/edgeAAV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/edgeaa/edgeAAP.hlsl";
         
   //OGLVertexShaderFile  = "shaders/common/postFx/gl//postFxV.glsl";
   //OGLPixelShaderFile   = "shaders/common/postFx/gl/passthruP.glsl";
      
   samplerNames[0] = "$inputTex";
   
   pixVersion = 3.0;
};

singleton ShaderData( PFX_EdgeAADebugShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/edgeaa/dbgEdgeDisplayP.hlsl";
         
   //OGLVertexShaderFile  = "shaders/common/postFx/gl//postFxV.glsl";
   //OGLPixelShaderFile   = "shaders/common/postFx/gl/passthruP.glsl";
      
   samplerNames[0] = "$inputTex";
   
   pixVersion = 3.0;
};

singleton PostEffect( EdgeDetectPostEffect )
{
   renderTime = "PFXBeforeBin";
   renderBin = "ObjTranslucentBin";      
   //renderPriority = 0.1;
   targetScale = "0.5 0.5";
      
   shader = PFX_EdgeAADetectShader;
   stateBlock = PFX_DefaultEdgeAAStateBlock;
   texture[0] = "#prepass";
   target = "#edge";
   
   isEnabled = false;
};

singleton PostEffect( EdgeAAPostEffect )
{
   renderTime = "PFXAfterDiffuse";
   //renderBin = "ObjTranslucentBin";      
   //renderPriority = 0.1;
   
   shader = PFX_EdgeAAShader;
   stateBlock = PFX_DefaultEdgeAAStateBlock;
   texture[0] = "#edge"; 
   texture[1] = "$backBuffer";
   target = "$backBuffer";
};
   
singleton PostEffect( Debug_EdgeAAPostEffect )
{
   renderTime = "PFXAfterDiffuse";
   //renderBin = "ObjTranslucentBin";      
   //renderPriority = 0.1;
      
   shader = PFX_EdgeAADebugShader;
   stateBlock = PFX_DefaultEdgeAAStateBlock;
   texture[0] = "#edge"; 
   target = "$backBuffer";
};