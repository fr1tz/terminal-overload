// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

uniform sampler2D diffuseMap;

varying vec2 uv;

uniform vec2 oneOverTargetSize;

void main()
{
   vec2 sNonUniformTaps[8];
      
   sNonUniformTaps[0] = vec2(0.992833, 0.979309);
   sNonUniformTaps[1] = vec2(-0.998585, 0.985853);
   sNonUniformTaps[2] = vec2(0.949299, -0.882562);
   sNonUniformTaps[3] = vec2(-0.941358, -0.893924);
   sNonUniformTaps[4] = vec2(0.545055, -0.589072);
   sNonUniformTaps[5] = vec2(0.346526, 0.385821);
   sNonUniformTaps[6] = vec2(-0.260183, 0.334412);
   sNonUniformTaps[7] = vec2(0.248676, -0.679605);
   
   gl_FragColor = vec4(0.0);
   
   vec2 texScale = vec2(1.0);
   
   for ( int i=0; i < 4; i++ )
   {
      vec2 offset = (oneOverTargetSize * texScale) * sNonUniformTaps[i];
      gl_FragColor += texture2D( diffuseMap, uv + offset );
   }
   
   gl_FragColor /= vec4(4.0);
   gl_FragColor.rgb = vec3(0.0);
}
