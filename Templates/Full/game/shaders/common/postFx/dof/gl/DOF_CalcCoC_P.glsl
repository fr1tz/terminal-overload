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

varying float3 wsEyeRay;
#define IN_wsEyeRay wsEyeRay
varying float2 uv0;
#define IN_uv0 uv0
varying float2 uv1;
#define IN_uv1 uv1
varying float2 uv2;
#define IN_uv2 uv2
varying float2 uv3;
#define IN_uv3 uv3

// These are set by the game engine.  
uniform sampler2D shrunkSampler;  // Output of DofDownsample()  
uniform sampler2D blurredSampler; // Blurred version of the shrunk sampler  

// This is the pixel shader function that calculates the actual  
// value used for the near circle of confusion.  
// "texCoords" are 0 at the bottom left pixel and 1 at the top right.  
void main()
{
   float3 color;  
   float coc;  
   half4 blurred;  
   half4 shrunk;  
   
   shrunk = tex2D( shrunkSampler, IN_uv0 );  
   blurred = tex2D( blurredSampler, IN_uv1 );  
   color = shrunk.rgb;  
   //coc = shrunk.a;
   //coc = blurred.a;
   //coc = max( blurred.a, shrunk.a );  
   coc = 2 * max( blurred.a, shrunk.a ) - shrunk.a;  
   
   
   //gl_FragColor = float4( coc.rrr, 1.0 );
   //gl_FragColor = float4( color, 1.0 );
   gl_FragColor = float4( color, coc );  
   //gl_FragColor = float4( 1.0, 0.0, 1.0, 1.0 );
}