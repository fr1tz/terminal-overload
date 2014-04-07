// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hlslCompat.glsl"

in vec4 vPosition;
in vec4 vColor;
in vec2 vTexCoord0;
in vec2 vTexCoord1;

out vec2 texCoord;
out vec4 color;
out float fade;

uniform mat4 modelview;
uniform float shadowLength;
uniform vec3 shadowCasterPosition;

void main()
{
   gl_Position = modelview * vec4(vPosition.xyz, 1.0);
   
   color = vColor;
   texCoord = vTexCoord1.st;
   
   float fromCasterDist = length(vPosition.xyz - shadowCasterPosition) - shadowLength;
   fade = 1.0 - clamp( fromCasterDist / shadowLength , 0.0, 1.0 );
   
   correctSSP(gl_Position);
}
