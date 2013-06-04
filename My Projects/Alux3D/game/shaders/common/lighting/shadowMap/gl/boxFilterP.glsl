// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#define blurSamples 4.0

uniform sampler2D diffuseMap0;
uniform float texSize;
uniform vec2 blurDimension;

varying vec2 tex0;

void main()
{
   // Preshader
   float TexelSize = 1.0 / texSize;
   vec2 SampleOffset = TexelSize * blurDimension;
   vec2 Offset = 0.5 * float(blurSamples - 1.0) * SampleOffset;
   
   vec2 BaseTexCoord = tex0 - Offset;
   
   vec4 accum = vec4(0.0, 0.0, 0.0, 0.0);
   for(int i = 0; i < int(blurSamples); i++)
   {
      accum += texture2D(diffuseMap0, BaseTexCoord + float(i) * SampleOffset);
   }
   accum /= blurSamples;
   gl_FragColor = accum;
}