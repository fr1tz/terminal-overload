// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"

in vec2 uv0;
uniform sampler2D prepassBuffer;
uniform sampler1D depthViz;

out vec4 OUT_col;

void main()
{
   float depth = prepassUncondition( prepassBuffer, uv0 ).w;
   OUT_col = vec4( texture( depthViz, depth ).rgb, 1.0 );
}