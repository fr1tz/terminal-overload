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

#include "../../../gl/torque.glsl"
#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"

varying vec2 uv0;
varying vec2 uv1;
varying vec2 uv2;
varying vec2 uv3;
varying vec3 wsEyeRay;

#define IN_uv0 uv0
#define IN_uv1 uv1
#define IN_uv2 uv2
#define IN_uv3 uv3
#define IN_wsEyeRay wsEyeRay

uniform sampler2D inputTex ;
uniform sampler2D luminanceTex  ;
uniform float2 oneOverTargetSize;
uniform float brightPassThreshold;
uniform float g_fMiddleGray;

const float3 LUMINANCE_VECTOR = float3(0.3125f, 0.6154f, 0.0721f);


const float2 gTapOffsets[4] = float2[]
(
   float2( -0.5, 0.5 ),  float2( 0.5, -0.5 ),
   float2( -0.5, -0.5 ), float2( 0.5, 0.5 )
);

void main()
{
   float4 average = float4( 0.0f, 0.0f, 0.0f, 0.0f );      

   // Combine and average 4 samples from the source HDR texture.
   for( int i = 0; i < 4; i++ )
      average += hdrDecode( tex2D( inputTex, IN_uv0 + ( gTapOffsets[i] * oneOverTargetSize ) ) );
   average *= 0.25f;

   // Determine the brightness of this particular pixel.   
   float adaptedLum = tex2D( luminanceTex, float2( 0.5f, 0.5f ) ).r;
   float lum = (g_fMiddleGray / (adaptedLum + 0.0001)) * hdrLuminance( average.rgb );
   //float lum = hdrLuminance( average.rgb );
   
   // Determine whether this pixel passes the test...
   if ( lum < brightPassThreshold )
      average = float4( 0.0f, 0.0f, 0.0f, 1.0f );

   // Write the colour to the bright-pass render target
   gl_FragColor = hdrEncode( average );
}
