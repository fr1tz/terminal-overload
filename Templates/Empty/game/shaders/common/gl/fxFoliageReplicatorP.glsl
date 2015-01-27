// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
uniform sampler2D diffuseMap, alphaMap;
uniform vec4 groundAlpha;

in vec4 color, groundAlphaCoeff;
in vec2 outTexCoord, alphaLookup;

out vec4 OUT_col;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{
   vec4 alpha = texture(alphaMap, alphaLookup);
   OUT_col = color * texture(diffuseMap, outTexCoord);
   OUT_col.a = OUT_col.a * min(alpha, groundAlpha + groundAlphaCoeff.x).x;
}
