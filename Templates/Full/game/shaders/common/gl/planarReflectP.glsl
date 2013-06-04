// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
uniform sampler2D diffuseMap, refractMap;
uniform vec4 shadeColor;

varying vec2 TEX0;
varying vec4 TEX1;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{
   vec4 diffuseColor = texture2D( diffuseMap, TEX0 );
   vec4 reflectColor = texture2DProj( refractMap, TEX1 );

   gl_FragColor = diffuseColor + reflectColor * diffuseColor.a;
}
