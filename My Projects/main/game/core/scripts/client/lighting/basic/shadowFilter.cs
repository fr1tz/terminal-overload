// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


singleton ShaderData( BL_ShadowFilterShaderV )
{   
   DXVertexShaderFile 	= "shaders/common/lighting/basic/shadowFilterV.hlsl";
   DXPixelShaderFile 	= "shaders/common/lighting/basic/shadowFilterP.hlsl";
   
   OGLVertexShaderFile 	= "shaders/common/lighting/basic/gl/shadowFilterV.glsl";
   OGLPixelShaderFile 	= "shaders/common/lighting/basic/gl/shadowFilterP.glsl";

   samplerNames[0] = "$diffuseMap";

   defines = "BLUR_DIR=float2(1.0,0.0)";

   pixVersion = 2.0;     
};

singleton ShaderData( BL_ShadowFilterShaderH : BL_ShadowFilterShaderV )
{
    defines = "BLUR_DIR=float2(0.0,1.0)";
};


singleton GFXStateBlockData( BL_ShadowFilterSB : PFX_DefaultStateBlock )
{
   colorWriteDefined=true;
   colorWriteRed=false;
   colorWriteGreen=false;
   colorWriteBlue=false;
   blendDefined = true;
   blendEnable = true;
};

// NOTE: This is ONLY used in Basic Lighting, and 
// only directly by the ProjectedShadow.  It is not 
// meant to be manually enabled like other PostEffects.
singleton PostEffect( BL_ShadowFilterPostFx )
{
    // Blur vertically
   shader = BL_ShadowFilterShaderV;
   stateBlock = PFX_DefaultStateBlock;
   targetClear = "PFXTargetClear_OnDraw";
   targetClearColor = "0 0 0 0";
   texture[0] = "$inTex";
   
   target = "$outTex";   

   // Blur horizontal
   new PostEffect()
   {
      shader = BL_ShadowFilterShaderH;
      stateBlock = PFX_DefaultStateBlock;
      texture[0] = "$inTex";
      target = "$outTex";
   };
};
