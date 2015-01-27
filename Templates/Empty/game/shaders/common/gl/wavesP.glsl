// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

uniform sampler2D diffMap;
uniform sampler2D bumpMap;
uniform samplerCube cubeMap;
uniform vec4 specularColor;
uniform float specularPower;
uniform vec4 ambient;
uniform float accumTime;

in vec2 TEX0;
in vec4 outLightVec;
in vec3 outPos;
in vec3 outEyePos;

out vec4 OUT_col;

void main()
{
   vec2 texOffset;
   float sinOffset1 = sin( accumTime * 1.5 + TEX0.y * 6.28319 * 3.0 ) * 0.03;
   float sinOffset2 = sin( accumTime * 3.0 + TEX0.y * 6.28319 ) * 0.04;
   
   texOffset.x = TEX0.x + sinOffset1 + sinOffset2;
   texOffset.y = TEX0.y + cos( accumTime * 3.0 + TEX0.x * 6.28319 * 2.0 ) * 0.05;
   
   vec4 bumpNorm = texture(bumpMap, texOffset) * 2.0 - 1.0;
   vec4 diffuse = texture(diffMap, texOffset);
   
   OUT_col = diffuse * (clamp(dot(outLightVec.xyz, bumpNorm.xyz), 0.0, 1.0) + ambient);
   
   vec3 eyeVec = normalize(outEyePos - outPos);
   vec3 halfAng = normalize(eyeVec + outLightVec.xyz);
   float specular = clamp(dot(bumpNorm.xyz, halfAng), 0.0, 1.0) * outLightVec.w;
   specular = pow(specular, specularPower);
   OUT_col += specularColor * specular;
}
