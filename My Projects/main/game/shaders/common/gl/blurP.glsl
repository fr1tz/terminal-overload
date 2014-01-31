// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//*****************************************************************************
// Glow Shader
//*****************************************************************************
uniform vec4 kernel;
uniform sampler2D diffuseMap;

varying vec2 texc0, texc1, texc2, texc3;

void main()
{
   gl_FragColor = texture2D(diffuseMap, texc0) * kernel.x;
   gl_FragColor += texture2D(diffuseMap, texc1) * kernel.y;
   gl_FragColor += texture2D(diffuseMap, texc2) * kernel.z;
   gl_FragColor += texture2D(diffuseMap, texc3) * kernel.w;
}
