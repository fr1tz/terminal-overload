// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

uniform sampler2D diffMap;
uniform sampler2D bumpMap;
uniform samplerCube cubeMap;
uniform vec4 specularColor;
uniform float specularPower;
uniform vec4 ambient;
uniform float accumTime;

varying vec2 TEX0;
varying vec4 outLightVec;
varying vec3 outPos;
varying vec3 outEyePos;

void main()
{
   vec2 texOffset;
   float sinOffset1 = sin( accumTime * 1.5 + TEX0.y * 6.28319 * 3.0 ) * 0.03;
   float sinOffset2 = sin( accumTime * 3.0 + TEX0.y * 6.28319 ) * 0.04;
   
   texOffset.x = TEX0.x + sinOffset1 + sinOffset2;
   texOffset.y = TEX0.y + cos( accumTime * 3.0 + TEX0.x * 6.28319 * 2.0 ) * 0.05;
   
   vec4 bumpNorm = texture2D(bumpMap, texOffset) * 2.0 - 1.0;
   vec4 diffuse = texture2D(diffMap, texOffset);
   
   gl_FragColor = diffuse * (clamp(dot(outLightVec.xyz, bumpNorm.xyz), 0.0, 1.0) + ambient);
   
   vec3 eyeVec = normalize(outEyePos - outPos);
   vec3 halfAng = normalize(eyeVec + outLightVec.xyz);
   float specular = clamp(dot(bumpNorm.xyz, halfAng), 0.0, 1.0) * outLightVec.w;
   specular = pow(specular, specularPower);
   gl_FragColor += specularColor * specular;
}
