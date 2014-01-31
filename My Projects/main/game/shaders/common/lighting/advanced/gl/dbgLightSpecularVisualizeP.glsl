// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "shadergen:/autogenConditioners.h"

varying vec2 uv0;
uniform sampler2D lightInfoBuffer;

void main()
{   
   vec3 lightcolor;
   float nl_Att, specular;   
   lightinfoUncondition( texture2DLod( lightInfoBuffer, uv0 ), lightcolor, nl_Att, specular );
   gl_FragColor = vec4( specular, specular, specular, 1.0 );
}