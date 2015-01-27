// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../gl/hlslCompat.glsl"
#include "shadergen:/autogenConditioners.h"

in vec2 uv0;
uniform sampler2D lightInfoBuffer;

out vec4 OUT_col;

void main()
{   
   vec3 lightcolor;   
   float nl_Att, specular;   
   lightinfoUncondition( texture( lightInfoBuffer, uv0 ), lightcolor, nl_Att, specular );   
   OUT_col = vec4( lightcolor, 1.0 ); 
}