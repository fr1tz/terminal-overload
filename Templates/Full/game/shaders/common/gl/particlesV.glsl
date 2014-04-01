// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hlslCompat.glsl"

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexCoord0;

#define In_pos    vPosition
#define In_color  vColor
#define In_uv0    vTexCoord0

out vec4 color;
out vec2 uv0;
out vec4 pos;

#define OUT_hpos gl_Position
#define OUT_color color
#define OUT_uv0 uv0
#define OUT_pos pos

uniform mat4 modelViewProj;
uniform mat4 fsModelViewProj;

void main()
{
   OUT_hpos = tMul( modelViewProj, In_pos );
	OUT_pos = tMul( fsModelViewProj, In_pos );
	OUT_color = In_color;
	OUT_uv0 = In_uv0;
	
   correctSSP(gl_Position);
}

