//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  This file contains shader data necessary for various engine utility functions
//-----------------------------------------------------------------------------


singleton ShaderData( _DebugInterior_ )
{
   CGVertexShaderFile   = "shaders/common/debugInteriorsV.cg";
   CGPixelShaderFile    = "shaders/common/debugInteriorsP.cg";
   
   
   samplerNames[0] = "$diffuseMap";
   
   pixVersion = 1.1;
};

singleton ShaderData( ParticlesShaderData )
{
   CGVertexShaderFile     = "shaders/common/particlesV.cg";
   CGPixelShaderFile      = "shaders/common/particlesP.cg";   
      
   pixVersion = 2.0;
};

singleton ShaderData( OffscreenParticleCompositeShaderData )
{
   CGVertexShaderFile     = "shaders/common/particleCompositeV.cg";
   CGPixelShaderFile      = "shaders/common/particleCompositeP.cg";
      
   pixVersion = 2.0;
};

//-----------------------------------------------------------------------------
// Planar Reflection
//-----------------------------------------------------------------------------
new ShaderData( ReflectBump )
{
   CGVertexShaderFile 	= "shaders/common/planarReflectBumpV.cg";
   CGPixelShaderFile 	= "shaders/common/planarReflectBumpP.cg";
              
   samplerNames[0] = "$diffuseMap";
   samplerNames[1] = "$refractMap";
   samplerNames[2] = "$bumpMap";
   
   pixVersion = 2.0;
};

new ShaderData( Reflect )
{
   CGVertexShaderFile 	= "shaders/common/planarReflectV.cg";
   CGPixelShaderFile 	= "shaders/common/planarReflectP.cg";
      
   samplerNames[0] = "$diffuseMap";
   samplerNames[1] = "$refractMap";
   
   pixVersion = 1.4;
};

//-----------------------------------------------------------------------------
// fxFoliageReplicator
//-----------------------------------------------------------------------------
new ShaderData( fxFoliageReplicatorShader )
{
   CGVertexShaderFile 	= "shaders/common/fxFoliageReplicatorV.cg";
   CGPixelShaderFile 	= "shaders/common/fxFoliageReplicatorP.cg";
   
   samplerNames[0] = "$diffuseMap";
   samplerNames[1] = "$alphaMap";
   
   pixVersion = 1.4;
};