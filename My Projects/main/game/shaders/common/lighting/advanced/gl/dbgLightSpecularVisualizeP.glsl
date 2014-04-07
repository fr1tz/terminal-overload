// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"

in vec2 uv0;
uniform sampler2D lightInfoBuffer;

void main()
{   
   vec3 lightcolor;   
   float nl_Att, specular;   
   lightinfoUncondition( texture( lightInfoBuffer, uv0 ), lightcolor, nl_Att, specular );   
   OUT_FragColor0 = vec4( specular, specular, specular, 1.0 );
}