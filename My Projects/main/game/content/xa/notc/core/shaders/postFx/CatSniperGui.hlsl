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

// Based on 'Cubic Lens Distortion HLSL Shader' by François Tarlier
// www.francois-tarlier.com/blog/index.php/2009/11/cubic-lens-distortion-shader

#include "shaders/common/postFx/postFx.hlsl"
#include "shaders/common/torque.hlsl"


uniform sampler2D backBuffer : register( s0 );
uniform float distCoeff;
uniform float cubeDistort;
uniform float3 colorDistort;
uniform float4 keepColor;


float4 main( PFXVertToPix IN ) : COLOR0
{
    float2 tex = IN.uv0;

    float f = 0;
    float r2 = (tex.x - 0.5) * (tex.x - 0.5) + (tex.y - 0.5) * (tex.y - 0.5);       

    // Only compute the cubic distortion if necessary.
    if ( cubeDistort == 0.0 )
        f = 1 + r2 * distCoeff;
    else
        f = 1 + r2 * (distCoeff + cubeDistort * sqrt(r2));

    float3 outColor;
    float3 distort = f.xxx + colorDistort;
    
    float x = distort[0] * ( tex.x - 0.5 ) + 0.5;
    float y = distort[0] * ( tex.y - 0.5 ) + 0.5;
    
    outColor = tex2Dlod( backBuffer, float4(x,y,0,0) );
    float v = (outColor[0] + outColor[1] + outColor[2]) / 3;
    for(int i = 0; i < 3; i++)
      outColor[i] = v;
      //outColor[i] = outColor[i]*keepColor[i] + clamp(v-keepColor[i],0,1);

    return float4( outColor.rgb, 1 );
}
