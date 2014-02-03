// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hlslCompat.glsl"

attribute vec4 vPosition;
attribute vec4 vColor;
attribute vec2 vTexCoord0;

#define In_pos    vPosition
#define In_color  vColor
#define In_uv0    vTexCoord0

varying vec4 color;
varying vec2 uv0;
varying vec4 pos;

#define OUT_hpos gl_Position
#define OUT_color color
#define OUT_uv0 uv0
#define OUT_pos pos

uniform mat4 modelViewProj;
uniform mat4 fsModelViewProj;

void main()
{
   OUT_hpos = mul( modelViewProj, In_pos );
	OUT_pos = mul( fsModelViewProj, In_pos );
	OUT_color = In_color;
	OUT_uv0 = In_uv0;
	
   correctSSP(gl_Position);
}

