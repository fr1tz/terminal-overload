// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.



//-----------------------------------------------------------------------------
// Water
//-----------------------------------------------------------------------------

singleton ShaderData( WaterShader )
{
   DXVertexShaderFile 	= "shaders/common/water/waterV.hlsl";
   DXPixelShaderFile 	= "shaders/common/water/waterP.hlsl";
   
   OGLVertexShaderFile = "shaders/common/water/gl/waterV.glsl";
   OGLPixelShaderFile = "shaders/common/water/gl/waterP.glsl";
   
   samplerNames[0] = "$bumpMap";  // noise
   samplerNames[1] = "$prepassTex";  // #prepass
   samplerNames[2] = "$reflectMap"; // $reflectbuff
   samplerNames[3] = "$refractBuff";  // $backbuff
   samplerNames[4] = "$skyMap";  // $cubemap   
   samplerNames[5] = "$foamMap";  // foam     
   samplerNames[6] = "$depthGradMap"; // depthMap ( color gradient ) 
   
   pixVersion = 3.0;
};

new GFXSamplerStateData(WaterSampler)
{
   textureColorOp = GFXTOPModulate;
   addressModeU = GFXAddressWrap;
   addressModeV = GFXAddressWrap;
   addressModeW = GFXAddressWrap;
   magFilter = GFXTextureFilterLinear;
   minFilter = GFXTextureFilterAnisotropic;
   mipFilter = GFXTextureFilterLinear;
   maxAnisotropy = 4;
};

singleton GFXStateBlockData( WaterStateBlock )
{
   samplersDefined = true;
   samplerStates[0] = WaterSampler;  // noise
   samplerStates[1] = SamplerClampPoint;  // #prepass
   samplerStates[2] = SamplerClampLinear; // $reflectbuff
   samplerStates[3] = SamplerClampPoint;  // $backbuff
   samplerStates[4] = SamplerWrapLinear;  // $cubemap   
   samplerStates[5] = SamplerWrapLinear;  // foam     
   samplerStates[6] = SamplerClampLinear; // depthMap ( color gradient ) 
   cullDefined = true;
   cullMode = "GFXCullCCW";
};

singleton GFXStateBlockData( UnderWaterStateBlock : WaterStateBlock )
{
   cullMode = "GFXCullCW";
};

singleton CustomMaterial( WaterMat )
{   
   sampler["prepassTex"] = "#prepass";
   sampler["reflectMap"] = "$reflectbuff";
   sampler["refractBuff"] = "$backbuff";
   // These samplers are set in code not here.
   // This is to allow different WaterObject instances
   // to use this same material but override these textures
   // per instance.
   //sampler["bumpMap"] = "";    
   //sampler["skyMap"] = "";
   //sampler["foamMap"] = "";  
   //sampler["depthGradMap"] = "";
   
   shader = WaterShader;
   stateBlock = WaterStateBlock;
   version = 3.0;
   
   useAnisotropic[0] = true;
};

//-----------------------------------------------------------------------------
// Underwater
//-----------------------------------------------------------------------------

singleton ShaderData( UnderWaterShader : WaterShader )
{
   defines = "UNDERWATER";   
};

singleton CustomMaterial( UnderwaterMat )
{  
   // These samplers are set in code not here.
   // This is to allow different WaterObject instances
   // to use this same material but override these textures
   // per instance.   
   //sampler["bumpMap"] = "core/art/water/noise02";
   //sampler["foamMap"] = "core/art/water/foam";

   sampler["prepassTex"] = "#prepass";
   sampler["refractBuff"] = "$backbuff";   
   
   shader = UnderWaterShader;
   stateBlock = UnderWaterStateBlock;
   specular = "0.75 0.75 0.75 1.0";
   specularPower = 48.0;
   version = 3.0;
};

//-----------------------------------------------------------------------------
// Basic Water
//-----------------------------------------------------------------------------

singleton ShaderData( WaterBasicShader )
{
   DXVertexShaderFile 	= "shaders/common/water/waterBasicV.hlsl";
   DXPixelShaderFile 	= "shaders/common/water/waterBasicP.hlsl";
   
   OGLVertexShaderFile  = "shaders/common/water/gl/waterBasicV.glsl";
   OGLPixelShaderFile   = "shaders/common/water/gl/waterBasicP.glsl"; 
   
   samplerNames[0] = "$bumpMap";
   samplerNames[2] = "$reflectMap";
   samplerNames[3] = "$refractBuff";
   samplerNames[4] = "$skyMap";
   samplerNames[5] = "$depthGradMap";
   
   pixVersion = 2.0;
};

singleton GFXStateBlockData( WaterBasicStateBlock )
{
   samplersDefined = true;
   samplerStates[0] = WaterSampler;  // noise
   samplerStates[2] = SamplerClampLinear;  // $reflectbuff
   samplerStates[3] = SamplerClampPoint;  // $backbuff
   samplerStates[4] = SamplerWrapLinear;  // $cubemap
   cullDefined = true;
   cullMode = "GFXCullCCW";
};

singleton GFXStateBlockData( UnderWaterBasicStateBlock : WaterBasicStateBlock )
{
   cullMode = "GFXCullCW";
};

singleton CustomMaterial( WaterBasicMat )
{
   // These samplers are set in code not here.
   // This is to allow different WaterObject instances
   // to use this same material but override these textures
   // per instance.     
   //sampler["bumpMap"] = "core/art/water/noise02";
   //sampler["skyMap"] = "$cubemap";   
   
   //sampler["prepassTex"] = "#prepass";
   sampler["reflectMap"] = "$reflectbuff";
   sampler["refractBuff"] = "$backbuff";
    
   cubemap = NewLevelSkyCubemap;
   shader = WaterBasicShader;
   stateBlock = WaterBasicStateBlock;
   version = 2.0;
};

//-----------------------------------------------------------------------------
// Basic UnderWater
//-----------------------------------------------------------------------------

singleton ShaderData( UnderWaterBasicShader : WaterBasicShader)
{
   defines = "UNDERWATER";   
};

singleton CustomMaterial( UnderwaterBasicMat )
{
   // These samplers are set in code not here.
   // This is to allow different WaterObject instances
   // to use this same material but override these textures
   // per instance.  
   //sampler["bumpMap"] = "core/art/water/noise02";
   //samplers["skyMap"] = "$cubemap";  

   //sampler["prepassTex"] = "#prepass";
   sampler["refractBuff"] = "$backbuff";
   
   shader = UnderWaterBasicShader;
   stateBlock = UnderWaterBasicStateBlock;
   version = 2.0;
};