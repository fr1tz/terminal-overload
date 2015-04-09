
#include "shaders/common/postFx/gl/postFx.glsl"
#include "shaders/common/gl/torque.glsl"
#include "shaders/common/gl/hlslCompat.glsl"

uniform float damageFlash;
uniform float whiteOut;
uniform sampler2D backBuffer;

out vec4 OUT_col;

void main()
{
   vec4 c = texture(backBuffer, IN_uv0);
   float v = (c[0] + c[1] + c[2])/3;
   c[0] = v;
   c[1] = 0;
   c[2] = 0;
   OUT_col = vec4(c.rgb, 1);
}
