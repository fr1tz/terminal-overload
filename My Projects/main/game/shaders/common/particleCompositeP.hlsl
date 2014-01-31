// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#include "torque.hlsl"

uniform sampler2D colorSource : register(S0);
uniform float4 offscreenTargetParams;

#ifdef TORQUE_LINEAR_DEPTH
#define REJECT_EDGES
uniform sampler2D edgeSource : register(S1);
uniform float4 edgeTargetParams;
#endif


float4 main( float4 offscreenPos : TEXCOORD0, float4 backbufferPos : TEXCOORD1 ) : COLOR
{  
   // Off-screen particle source screenspace position in XY
   // Back-buffer screenspace position in ZW
   float4 ssPos = float4(offscreenPos.xy / offscreenPos.w, backbufferPos.xy / backbufferPos.w);
   
	float4 uvScene = ( ssPos + 1.0 ) / 2.0;
	uvScene.yw = 1.0 - uvScene.yw;
	uvScene.xy = viewportCoordToRenderTarget(uvScene.xy, offscreenTargetParams);
	
#ifdef REJECT_EDGES
   // Cut out particles along the edges, this will create the stencil mask
	uvScene.zw = viewportCoordToRenderTarget(uvScene.zw, edgeTargetParams);
	float edge = tex2D( edgeSource, uvScene.zw ).r;
	clip( -edge );
#endif
	
	// Sample offscreen target and return
   return tex2D( colorSource, uvScene.xy );
}