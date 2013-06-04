// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Data
//-----------------------------------------------------------------------------
uniform sampler2D diffuseMap, refractMap, bumpMap;
uniform vec4 shadeColor;

varying vec2 TEX0;
varying vec4 TEX1;

//-----------------------------------------------------------------------------
// Fade edges of axis for texcoord passed in
//-----------------------------------------------------------------------------
float fadeAxis( float val )
{
   // Fades from 1.0 to 0.0 when less than 0.1
   float fadeLow = clamp( val * 10.0, 0.0, 1.0 );
   
   // Fades from 1.0 to 0.0 when greater than 0.9
   float fadeHigh = 1.0 - clamp( (val - 0.9) * 10.0, 0.0, 1.0 );

   return fadeLow * fadeHigh;
}


//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{
   vec3 bumpNorm = texture2D( bumpMap, TEX0 ).rgb * 2.0 - 1.0;
   vec2 offset = vec2( bumpNorm.x, bumpNorm.y );
   vec4 texIndex = TEX1;

   // The fadeVal is used to "fade" the distortion at the edges of the screen.
   // This is done so it won't sample the reflection texture out-of-bounds and create artifacts
   // Note - this can be done more efficiently with a texture lookup
   float fadeVal = fadeAxis( texIndex.x / texIndex.w ) * fadeAxis( texIndex.y / texIndex.w );

   const float distortion = 0.2;
   texIndex.xy += offset * distortion * fadeVal;

   vec4 diffuseColor = texture2D( diffuseMap, TEX0 );
   vec4 reflectColor = texture2DProj( refractMap, texIndex );

   gl_FragColor = diffuseColor + reflectColor * diffuseColor.a;
}
