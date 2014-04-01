// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//*****************************************************************************
// Glow Shader
//*****************************************************************************
uniform vec4 kernel;
uniform sampler2D diffuseMap;

in vec2 texc0, texc1, texc2, texc3;

void main()
{
   OUT_FragColor0 = texture(diffuseMap, texc0) * kernel.x;
   OUT_FragColor0 += texture(diffuseMap, texc1) * kernel.y;
   OUT_FragColor0 += texture(diffuseMap, texc2) * kernel.z;
   OUT_FragColor0 += texture(diffuseMap, texc3) * kernel.w;
}
