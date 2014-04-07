// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../gl/hlslCompat.glsl"

in vec4 vPosition;

#define IN_pos vPosition

out vec4 wsEyeDir;
out vec4 ssPos;
out vec4 vsEyeDir;

#define OUT_hpos gl_Position
#define OUT_wsEyeDir wsEyeDir
#define OUT_ssPos ssPos
#define OUT_vsEyeDir vsEyeDir

uniform mat4 modelview;
uniform mat4 objTrans;
uniform mat4 worldViewOnly;
uniform vec3 eyePosWorld;

void main()
{
   OUT_hpos = tMul( modelview, IN_pos );
   OUT_wsEyeDir = tMul( objTrans, IN_pos ) - vec4( eyePosWorld, 0.0 );
   OUT_vsEyeDir = tMul( worldViewOnly, IN_pos );
   OUT_ssPos = OUT_hpos;

   correctSSP(gl_Position);
}

