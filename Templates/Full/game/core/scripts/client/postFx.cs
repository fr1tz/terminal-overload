// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.


singleton GFXStateBlockData( PFX_DefaultStateBlock )
{
   zDefined = true;
   zEnable = false;
   zWriteEnable = false;
      
   samplersDefined = true;
   samplerStates[0] = SamplerClampLinear;
};

singleton ShaderData( PFX_PassthruShader )
{   
   DXVertexShaderFile 	= "shaders/common/postFx/postFxV.hlsl";
   DXPixelShaderFile 	= "shaders/common/postFx/passthruP.hlsl";
         
   OGLVertexShaderFile  = "shaders/common/postFx/gl/postFxV.glsl";
   OGLPixelShaderFile   = "shaders/common/postFx/gl/passthruP.glsl";
      
   samplerNames[0] = "$inputTex";
   
   pixVersion = 2.0;
};

function initPostEffects()
{
   // First exec the scripts for the different light managers
   // in the lighting folder.
   
   %pattern = "./postFx/*.cs";   
   %file = findFirstFile( %pattern );
   if ( %file $= "" )
   {
      // Try for DSOs next.
      %pattern = "./postFx/*.cs.dso";
      %file = findFirstFile( %pattern );
   }
   
   while( %file !$= "" )
   {      
      exec( %file );
      %file = findNextFile( %pattern );
   }
}

function PostEffect::inspectVars( %this )
{
   %name = %this.getName(); 
   %globals = "$" @ %name @ "::*";
   inspectVars( %globals );   
}

function PostEffect::viewDisassembly( %this )
{
   %file = %this.dumpShaderDisassembly();  
   
   if ( %file $= "" )
   {
      echo( "PostEffect::viewDisassembly - no shader disassembly found." );  
   }
   else
   {
      echo( "PostEffect::viewDisassembly - shader disassembly file dumped ( " @ %file @ " )." );
      openFile( %file );
   }
}

// Return true if we really want the effect enabled.
// By default this is the case.
function PostEffect::onEnabled( %this )
{   
   return true;
}