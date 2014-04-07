// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../../../gl/hlslCompat.glsl"

uniform sampler2D diffuseMap;

in vec2 uv;

uniform vec2 oneOverTargetSize;

const float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
const float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

void main()
{
   vec4 OUT = texture( diffuseMap, uv ) * weight[0];
   
   for ( int i=1; i < 3; i++ )
   {
      vec2 _sample = (BLUR_DIR * offset[i]) * oneOverTargetSize;
      OUT += texture( diffuseMap, uv + _sample ) * weight[i];  
      OUT += texture( diffuseMap, uv - _sample ) * weight[i];  
   }

   OUT_FragColor0 = OUT;
}
