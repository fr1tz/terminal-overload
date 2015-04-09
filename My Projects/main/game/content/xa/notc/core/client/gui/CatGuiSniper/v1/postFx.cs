// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton GFXStateBlockData( PFX_DefaultnotcCatSniperGuiStateBlock )
{
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;   
   samplersDefined = true;
   samplerStates[0] = SamplerClampPoint;
};

singleton ShaderData( PFX_notcCatSniperGuiShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "content/xa/notc/core/shaders/postFx/CatSniperGui.hlsl";
   
   OGLVertexShaderFile  = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile   = "content/xa/notc/core/shaders/postFx/CatSniperGui.glsl";

   samplerNames[0] = "$backBuffer";
   
   //defines = "WHITE_COLOR=float4(1.0,1.0,1.0,0.0);MUL_COLOR=float4(1.0,0.25,0.25,0.0)";
   
   pixVersion = 3.0;
};

singleton PostEffect( notcCatSniperGuiPostFX )
{
   renderTime = "PFXAfterDiffuse";
   renderPriority = 0.2;
   isEnabled = false;
   allowReflectPass = false;

   shader = PFX_notcCatSniperGuiShader;
   stateBlock = PFX_DefaultnotcCatSniperGuiStateBlock;
   texture[0] = "$backBuffer";
   target = "$backBuffer";
   targetScale = "1.0 1.0";
};

function notcCatSniperGuiPostFX::setShaderConsts( %this )
{
   %colorI = ServerConnection.getControlObject().paletteColors[0];
   %colorF = "";
   for(%i = 0; %i < 4; %i++)
      %colorF = %colorF SPC getWord(%colorI, %i)/255;
   %colorF = trim(%colorF);

   %this.setShaderConst( "$keepColor", %colorF);
}
