// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
uniform sampler2D diffuseMap;

in vec4 color;
in vec2 texCoord;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{
   OUT_FragColor0 = texture(diffuseMap, texCoord) * color;
}
