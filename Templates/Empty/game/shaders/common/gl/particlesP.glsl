// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "torque.glsl"
#include "hlslCompat.glsl"
   
// With advanced lighting we get soft particles.
#ifdef TORQUE_LINEAR_DEPTH
   #define SOFTPARTICLES  
#endif

#ifdef SOFTPARTICLES
   
   #include "shadergen:/autogenConditioners.h"
   
   uniform float oneOverSoftness;
   uniform float oneOverFar;
   uniform sampler2D prepassTex;   
   //uniform vec3 vEye;
   uniform vec4 prePassTargetParams;
#endif

#define CLIP_Z // TODO: Make this a proper macro

in vec4 color;
in vec2 uv0;
in vec4 pos;

#define IN_color color
#define IN_uv0 uv0
#define IN_pos pos

uniform sampler2D diffuseMap;

uniform sampler2D paraboloidLightMap;

vec4 lmSample( vec3 nrm )
{
   bool calcBack = (nrm.z < 0.0);
   if ( calcBack )
      nrm.z = nrm.z * -1.0;

   vec2 lmCoord;
   lmCoord.x = (nrm.x / (2*(1 + nrm.z))) + 0.5;
   lmCoord.y = 1-((nrm.y / (2*(1 + nrm.z))) + 0.5);


   // If this is the back, offset in the atlas
   if ( calcBack )
      lmCoord.x += 1.0;
      
   // Atlasing front and back maps, so scale
   lmCoord.x *= 0.5;

   return texture(paraboloidLightMap, lmCoord);
}


uniform float alphaFactor;
uniform float alphaScale;

void main()
{
   float softBlend = 1;
   
   #ifdef SOFTPARTICLES
      vec2 tc = IN_pos.xy * vec2(1.0, -1.0) / IN_pos.w;
      tc = viewportCoordToRenderTarget(saturate( ( tc + 1.0 ) * 0.5 ), prePassTargetParams); 
   
   	float sceneDepth = prepassUncondition( prepassTex, tc ).w;   	   	   			
   	float depth = IN_pos.w * oneOverFar;   	
	float diff = sceneDepth - depth;
	#ifdef CLIP_Z
	   // If drawing offscreen, this acts as the depth test, since we don't line up with the z-buffer
	   // When drawing high-res, though, we want to be able to take advantage of hi-z
	   // so this is #ifdef'd out
	   //clip(diff);
	#endif
      softBlend = saturate( diff * oneOverSoftness );
   #endif
	   
   vec4 diffuse = texture( diffuseMap, IN_uv0 );
   
   //OUT_FragColor0 = vec4( lmSample(vec3(0, 0, -1)).rgb, IN_color.a * diffuse.a * softBlend * alphaScale);
   
   // Scale output color by the alpha factor (turn LerpAlpha into pre-multiplied alpha)
   vec3 colorScale = ( alphaFactor < 0.0 ? IN_color.rgb * diffuse.rgb : vec3( alphaFactor > 0.0 ? IN_color.a * diffuse.a * alphaFactor * softBlend : softBlend ) );
   
   OUT_FragColor0 = hdrEncode( vec4( IN_color.rgb * diffuse.rgb * colorScale,
                  IN_color.a * diffuse.a * softBlend * alphaScale ) );
}

