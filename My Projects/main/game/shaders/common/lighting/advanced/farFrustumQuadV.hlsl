// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../hlslStructs.h"
#include "farFrustumQuad.hlsl"


FarFrustumQuadConnectV main( VertexIn_PNTT IN,
                             uniform float4 rtParams0 )
{
   FarFrustumQuadConnectV OUT;

   OUT.hpos = float4( IN.uv0, 0, 1 );

   // Get a RT-corrected UV from the SS coord
   OUT.uv0 = getUVFromSSPos( OUT.hpos.xyz, rtParams0 );
   
   // Interpolators will generate eye rays the 
   // from far-frustum corners.
   OUT.wsEyeRay = IN.tangent.xyz;
   OUT.vsEyeRay = IN.normal.xyz;

   return OUT;
}
