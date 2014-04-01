// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
uniform sampler2D diffuseMap, alphaMap;
uniform vec4 groundAlpha;

in vec4 color, groundAlphaCoeff;
in vec2 outTexCoord, alphaLookup;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{
   vec4 alpha = texture(alphaMap, alphaLookup);
   OUT_FragColor0 = color * texture(diffuseMap, outTexCoord);
   OUT_FragColor0.a = OUT_FragColor0.a * min(alpha, groundAlpha + groundAlphaCoeff.x).x;
}
