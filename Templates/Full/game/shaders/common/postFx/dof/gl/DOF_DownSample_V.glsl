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

#include "../../../gl/hlslCompat.glsl"
#include "../../../gl/torque.glsl"

#define IN_pos  gl_Vertex
#define IN_tc gl_MultiTexCoord0.st
#define IN_wsEyeRay gl_MultiTexCoord1.xyz

#define OUT_position gl_Position

varying float2 tcColor0;
#define OUT_tcColor0 tcColor0
varying float2 tcColor1;
#define OUT_tcColor1 tcColor1
varying float2 tcDepth0;
#define OUT_tcDepth0 tcDepth0
varying float2 tcDepth1;
#define OUT_tcDepth1 tcDepth1
varying float2 tcDepth2;
#define OUT_tcDepth2 tcDepth2
varying float2 tcDepth3;
#define OUT_tcDepth3 tcDepth3


uniform float4    rtParams0;
uniform float2    oneOverTargetSize;  

void main()  
{  
   OUT_position = IN_pos;
   
   float2 uv = viewportCoordToRenderTarget( IN_tc, rtParams0 ); 
   //OUT_position = mul( IN_pos, modelView );  
   OUT_tcColor1 = uv + float2( +1.0, -0.0 ) * oneOverTargetSize;  
   OUT_tcColor0 = uv + float2( -1.0, -0.0 ) * oneOverTargetSize;  
   OUT_tcDepth0 = uv + float2( -0.5, -0.0 ) * oneOverTargetSize;    
   OUT_tcDepth1 = uv + float2( -1.5, -0.0 ) * oneOverTargetSize;    
   OUT_tcDepth2 = uv + float2( +1.5, -0.0 ) * oneOverTargetSize;    
   OUT_tcDepth3 = uv + float2( +2.5, -0.0 ) * oneOverTargetSize;    
   
   correctSSP(gl_Position);
}  