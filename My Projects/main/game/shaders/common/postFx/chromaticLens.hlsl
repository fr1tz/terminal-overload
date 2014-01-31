// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// Based on 'Cubic Lens Distortion HLSL Shader' by François Tarlier
// www.francois-tarlier.com/blog/index.php/2009/11/cubic-lens-distortion-shader

#include "./postFx.hlsl"
#include "./../torque.hlsl"


uniform sampler2D backBuffer : register( s0 );
uniform float distCoeff;
uniform float cubeDistort;
uniform float3 colorDistort;


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

    // Distort each color channel seperately to get a chromatic distortion effect.
    float3 outColor;
    float3 distort = f.xxx + colorDistort;

    for ( int i=0; i < 3; i++ )
    {
        float x = distort[i] * ( tex.x - 0.5 ) + 0.5;
        float y = distort[i] * ( tex.y - 0.5 ) + 0.5;
        outColor[i] = tex2Dlod( backBuffer, float4(x,y,0,0) )[i];
    }

    return float4( outColor.rgb, 1 );
}