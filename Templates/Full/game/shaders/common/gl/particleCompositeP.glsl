// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "torque.glsl"

uniform sampler2D colorSource;
uniform vec4 offscreenTargetParams;

#ifdef TORQUE_LINEAR_DEPTH
#define REJECT_EDGES
uniform sampler2D edgeSource;
uniform vec4 edgeTargetParams;
#endif

varying vec4 backbufferPos;
varying vec4 offscreenPos;

void main()
{  
   // Off-screen particle source screenspace position in XY
   // Back-buffer screenspace position in ZW
   vec4 ssPos = vec4(offscreenPos.xy / offscreenPos.w, backbufferPos.xy / backbufferPos.w);
   
	vec4 uvScene = ( ssPos + 1.0 ) / 2.0;
	uvScene.yw = 1.0 - uvScene.yw;
	uvScene.xy = viewportCoordToRenderTarget(uvScene.xy, offscreenTargetParams);
	
#ifdef REJECT_EDGES
   // Cut out particles along the edges, this will create the stencil mask
	uvScene.zw = viewportCoordToRenderTarget(uvScene.zw, edgeTargetParams);
	float edge = texture2D( edgeSource, uvScene.zw ).r;
   if (-edge < 0.0)
      discard;
#endif
	
	// Sample offscreen target and return
   gl_FragColor = texture2D( colorSource, uvScene.xy );
}
