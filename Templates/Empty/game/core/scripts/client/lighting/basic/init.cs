// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

exec( "./shadowFilter.cs" );

singleton GFXStateBlockData( BL_ProjectedShadowSBData )
{
   blendDefined = true;
   blendEnable = true;
   blendSrc = GFXBlendDestColor;
   blendDest = GFXBlendZero;
         
   zDefined = true;
   zEnable = true;
   zWriteEnable = false;
               
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;   
   vertexColorEnable = true;
};

singleton ShaderData( BL_ProjectedShadowShaderData )
{
   DXVertexShaderFile     = "shaders/common/projectedShadowV.hlsl";
   DXPixelShaderFile      = "shaders/common/projectedShadowP.hlsl";   
   
   OGLVertexShaderFile     = "shaders/common/gl/projectedShadowV.glsl";
   OGLPixelShaderFile      = "shaders/common/gl/projectedShadowP.glsl";   
      
   samplerNames[0] = "inputTex";
   
   pixVersion = 2.0;
};

singleton CustomMaterial( BL_ProjectedShadowMaterial )
{
   sampler["inputTex"] = "$miscbuff";
 
   shader = BL_ProjectedShadowShaderData;
   stateBlock = BL_ProjectedShadowSBData;
   version = 2.0;
   forwardLit = true;
};

function onActivateBasicLM()
{
   // If HDR is enabled... enable the special format token.
   if ( $platform !$= "macos" && HDRPostFx.isEnabled )
      AL_FormatToken.enable();
      
   // Create render pass for projected shadow.
   new RenderPassManager( BL_ProjectedShadowRPM );

   // Create the mesh bin and add it to the manager.
   %meshBin = new RenderMeshMgr();
   BL_ProjectedShadowRPM.addManager( %meshBin );
   
   // Add both to the root group so that it doesn't
   // end up in the MissionCleanup instant group.
   RootGroup.add( BL_ProjectedShadowRPM );
   RootGroup.add( %meshBin );
}

function onDeactivateBasicLM()
{
   // Delete the pass manager which also deletes the bin.
   BL_ProjectedShadowRPM.delete();
}

function setBasicLighting()
{
   setLightManager( "Basic Lighting" );   
}
