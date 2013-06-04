// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// An implementation of "Practical Morphological Anti-Aliasing" from 
// GPU Pro 2 by Jorge Jimenez, Belen Masia, Jose I. Echevarria, 
// Fernando Navarro, and Diego Gutierrez.
//
// http://www.iryoku.com/mlaa/

// NOTE: This is currently disabled in favor of FXAA.  See 
// core\scripts\client\canvas.cs if you want to re-enable it.

singleton GFXStateBlockData( MLAA_EdgeDetectStateBlock : PFX_DefaultStateBlock )
{   
   // Mark the edge pixels in stencil.
   stencilDefined = true;
   stencilEnable = true;
   stencilPassOp = GFXStencilOpReplace;
   stencilFunc = GFXCmpAlways;
   stencilRef = 1;

   samplersDefined = true;   
   samplerStates[0] = SamplerClampLinear;
};

singleton ShaderData( MLAA_EdgeDetectionShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/mlaa/offsetV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/mlaa/edgeDetectionP.hlsl";

   samplerNames[0] = "$colorMapG";

   pixVersion = 3.0;
};

singleton GFXStateBlockData( MLAA_BlendWeightCalculationStateBlock : PFX_DefaultStateBlock )
{   
   // Here we want to process only marked pixels.
   stencilDefined = true;
   stencilEnable = true;
   stencilPassOp = GFXStencilOpKeep;
   stencilFunc = GFXCmpEqual;
   stencilRef = 1;

   samplersDefined = true;   
   samplerStates[0] = SamplerClampPoint;
   samplerStates[1] = SamplerClampLinear;
   samplerStates[2] = SamplerClampPoint;
};

singleton ShaderData( MLAA_BlendWeightCalculationShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/mlaa/passthruV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/mlaa/blendWeightCalculationP.hlsl";

   samplerNames[0] = "$edgesMap";
   samplerNames[1] = "$edgesMapL";
   samplerNames[2] = "$areaMap";

   pixVersion = 3.0;
};

singleton GFXStateBlockData( MLAA_NeighborhoodBlendingStateBlock : PFX_DefaultStateBlock )
{   
   // Here we want to process only marked pixels too.
   stencilDefined = true;
   stencilEnable = true;
   stencilPassOp = GFXStencilOpKeep;
   stencilFunc = GFXCmpEqual;
   stencilRef = 1;

   samplersDefined = true;   
   samplerStates[0] = SamplerClampPoint;
   samplerStates[1] = SamplerClampLinear;
   samplerStates[2] = SamplerClampPoint;
};

singleton ShaderData( MLAA_NeighborhoodBlendingShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/mlaa/offsetV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/mlaa/neighborhoodBlendingP.hlsl";

   samplerNames[0] = "$blendMap";
   samplerNames[1] = "$colorMapL";
   samplerNames[2] = "$colorMap";

   pixVersion = 3.0;
};


singleton PostEffect( MLAAFx )
{
   isEnabled = false;
   
   allowReflectPass = false;
   renderTime = "PFXAfterDiffuse";

   texture[0] = "$backBuffer"; //colorMapG      
   texture[1] = "#prepass"; // Used for depth detection

   target = "$outTex";
   targetClear = PFXTargetClear_OnDraw;
   targetClearColor = "0 0 0 0";

   stateBlock = MLAA_EdgeDetectStateBlock;
   shader = MLAA_EdgeDetectionShader;

   // The luma calculation weights which can be user adjustable
   // per-scene if nessasary.  The default value of...
   //
   //    0.2126 0.7152 0.0722 
   //
   // ... is the HDTV ITU-R Recommendation BT. 709.
   lumaCoefficients = "0.2126 0.7152 0.0722";

   // The tweakable color threshold used to select
   // the range of edge pixels to blend.
   threshold = 0.1;

   // The depth delta threshold used to select
   // the range of edge pixels to blend.
   depthThreshold = 0.01;

   new PostEffect()
   {
      internalName = "blendingWeightsCalculation";

      target = "$outTex";
      targetClear = PFXTargetClear_OnDraw;

      shader = MLAA_BlendWeightCalculationShader;
      stateBlock = MLAA_BlendWeightCalculationStateBlock;

      texture[0] = "$inTex"; // Edges mask    
      texture[1] = "$inTex"; // Edges mask 
      texture[2] = "AreaMap33.dds";
   };

   new PostEffect()
   {
      internalName = "neighborhoodBlending";

      shader = MLAA_NeighborhoodBlendingShader;
      stateBlock = MLAA_NeighborhoodBlendingStateBlock;

      texture[0] = "$inTex"; // Blend weights
      texture[1] = "$backBuffer";      
      texture[2] = "$backBuffer";      
   };
};

function MLAAFx::setShaderConsts(%this)
{
   %this.setShaderConst("$lumaCoefficients", %this.lumaCoefficients);
   %this.setShaderConst("$threshold", %this.threshold);
   %this.setShaderConst("$depthThreshold", %this.depthThreshold);
}