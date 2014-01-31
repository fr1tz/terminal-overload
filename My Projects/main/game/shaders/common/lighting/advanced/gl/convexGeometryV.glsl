// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

varying vec4 wsEyeDir;
varying vec4 ssPos;

uniform mat4 modelview;
uniform mat4 objTrans;
uniform vec3 eyePosWorld;

void main()
{
   gl_Position = modelview * gl_Vertex;
   wsEyeDir = objTrans * gl_Vertex - vec4( eyePosWorld, 0.0 );
   ssPos = gl_Position;
}
