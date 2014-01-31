// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

singleton ShaderData( PFX_TurbulenceShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/turbulenceP.hlsl";
           
   samplerNames[0] = "$inputTex";
   pixVersion = 3.0;
};

singleton PostEffect( TurbulenceFx )  
{  
   requirements = "None";
   isEnabled = false;    
   allowReflectPass = true;  
         
   renderTime = "PFXAfterDiffuse";  
   renderBin = "ObjTranslucentBin";     
     
   shader = PFX_TurbulenceShader;  
   stateBlock = PFX_myShaderStateBlock;  
   texture[0] = "$backBuffer";  
      
   renderPriority = 0.1;  
 };

function TurbulenceFx::setShaderConsts(%this)
{
   %this.setShaderConst(%this.timeConst, $Sim::time - %this.timeStart); 
}

function UnderwaterFogPostFx::onEnabled( %this )
{
   TurbulenceFx.enable();
   return true;
}

function UnderwaterFogPostFx::onDisabled( %this )
{
   TurbulenceFx.disable();
   return false;
}