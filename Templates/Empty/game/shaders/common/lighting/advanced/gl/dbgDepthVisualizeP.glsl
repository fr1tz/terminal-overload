// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"

varying vec2 uv0;
uniform sampler2D prepassBuffer;
uniform sampler2D depthViz;

void main()
{
   float depth = prepassUncondition( prepassBuffer, uv0 ).w;
   gl_FragColor = vec4( texture2D( depthViz, vec2(0.0,depth) ).rgb, 1.0 );
}