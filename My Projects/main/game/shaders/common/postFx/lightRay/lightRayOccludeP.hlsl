// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shadergen:/autogenConditioners.h"
#include "../postFx.hlsl"

uniform sampler2D backBuffer : register( s0 );   // The original backbuffer.
uniform sampler2D prepassTex : register( s1 );   // The pre-pass depth and normals.

uniform float brightScalar;

static const float3 LUMINANCE_VECTOR = float3(0.3125f, 0.6154f, 0.0721f);


float4 main( PFXVertToPix IN ) : COLOR0
{
    float4 col = float4( 0, 0, 0, 1 );
    
    // Get the depth at this pixel.
    float depth = prepassUncondition( prepassTex, IN.uv0 ).w;
    
    // If the depth is equal to 1.0, read from the backbuffer
    // and perform the exposure calculation on the result.
    if ( depth >= 0.999 )
    {
        col = tex2D( backBuffer, IN.uv0 );

        //col = 1 - exp(-120000 * col);
        col += dot( col.rgb, LUMINANCE_VECTOR ) + 0.0001f;
        col *= brightScalar;
    }
    
    return col;
}
