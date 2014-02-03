// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton ShaderData( PFX_FlashShader )
{
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/flashP.hlsl";
   
   OGLVertexShaderFile 	= "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile 	= "shaders/common/postFx/gl/flashP.glsl";
   
   samplerNames[0] = "$backBuffer";

   defines = "WHITE_COLOR=float4(1.0,1.0,1.0,0.0);MUL_COLOR=float4(1.0,0.25,0.25,0.0)";

   pixVersion = 2.0;
};
 
singleton PostEffect( FlashFx )
{
   isEnabled = false;    
   allowReflectPass = false;  

   renderTime = "PFXAfterDiffuse";  

   shader = PFX_FlashShader;   
   texture[0] = "$backBuffer";  
   renderPriority = 10;
   stateBlock = PFX_DefaultStateBlock;  
};

function FlashFx::setShaderConsts( %this )
{
   if ( isObject( ServerConnection ) )
   {
      %this.setShaderConst( "$damageFlash", ServerConnection.getDamageFlash() );
      %this.setShaderConst( "$whiteOut", ServerConnection.getWhiteOut() );
   }
   else
   {
      %this.setShaderConst( "$damageFlash", 0 );
      %this.setShaderConst( "$whiteOut", 0 );
   }
}
