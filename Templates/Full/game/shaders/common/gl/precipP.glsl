// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
uniform sampler2D diffuseMap;

in vec4 color;
in vec2 texCoord;

out vec4 OUT_col;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{
   OUT_col = texture(diffuseMap, texCoord) * color;
}
