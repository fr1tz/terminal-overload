// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hlslCompat.glsl"

in vec2  vTexCoord0;
#define uvCoord vTexCoord0

out vec4 offscreenPos;
out vec4 backbufferPos;

#define OUT_hpos gl_Position
#define OUT_offscreenPos offscreenPos
#define OUT_backbufferPos backbufferPos

uniform vec4 screenRect; // point, extent

void main()
{
   OUT_hpos = vec4(uvCoord.xy, 1.0, 1.0);
   OUT_hpos.xy *= screenRect.zw;
   OUT_hpos.xy += screenRect.xy;
   
   OUT_backbufferPos = OUT_hpos;
   OUT_offscreenPos = OUT_hpos;
   
   correctSSP(gl_Position);
}

