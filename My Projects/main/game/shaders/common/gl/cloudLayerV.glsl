// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "hlslCompat.glsl"

attribute vec4 vPosition;
attribute vec3 vNormal;
attribute vec3 vBinormal;
attribute vec3 vTangent;
attribute vec2 vTexCoord0;

varying vec4 texCoord12;
#define OUT_texCoord12 texCoord12
varying vec4 texCoord34;
#define OUT_texCoord34 texCoord34
varying vec3 vLightTS; // light vector in tangent space, denormalized
#define OUT_vLightTS vLightTS
varying vec3 vViewTS;  // view vector in tangent space, denormalized
#define OUT_vViewTS vViewTS
varying float worldDist;
#define OUT_worldDist worldDist

//-----------------------------------------------------------------------------
// Uniforms                                                                        
//-----------------------------------------------------------------------------
uniform mat4  modelview;
uniform vec3  eyePosWorld;
uniform vec3  sunVec;
uniform vec2  texOffset0;
uniform vec2  texOffset1;
uniform vec2  texOffset2;
uniform vec3  texScale;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
void main()
{   
   vec4 IN_pos = vPosition;
   vec3 IN_normal = vNormal;
   vec3 IN_binormal = vBinormal;
   vec3 IN_tangent = vTangent;
   vec2 IN_uv0 = vTexCoord0.st;

   gl_Position = modelview * IN_pos;
   
   // Offset the uv so we don't have a seam directly over our head.
   vec2 uv = IN_uv0 + vec2( 0.5, 0.5 );
   
   OUT_texCoord12.xy = uv * texScale.x;
   OUT_texCoord12.xy += texOffset0;
   
   OUT_texCoord12.zw = uv * texScale.y;
   OUT_texCoord12.zw += texOffset1;
   
   OUT_texCoord34.xy = uv * texScale.z;
   OUT_texCoord34.xy += texOffset2;
   
   OUT_texCoord34.z = IN_pos.z;
   OUT_texCoord34.w = 0.0;

   // Transform the normal, tangent and binormal vectors from object space to 
   // homogeneous projection space:
   vec3 vNormalWS   = -IN_normal; 
   vec3 vTangentWS  = -IN_tangent;
   vec3 vBinormalWS = -IN_binormal;
   
   // Compute position in world space:
   vec4 vPositionWS = IN_pos + vec4( eyePosWorld, 1 ); //mul( IN_pos, objTrans );

   // Compute and output the world view vector (unnormalized):
   vec3 vViewWS = eyePosWorld - vPositionWS.xyz;

   // Compute denormalized light vector in world space:
   vec3 vLightWS = -sunVec;

   // Normalize the light and view vectors and transform it to the IN_tangent space:
   mat3 mWorldToTangent = mat3( vTangentWS, vBinormalWS, vNormalWS );

   // Propagate the view and the light vectors (in tangent space):
   OUT_vLightTS = vLightWS * mWorldToTangent;
   OUT_vViewTS  = mWorldToTangent * vViewWS;

   OUT_worldDist = clamp( pow( max( IN_pos.z, 0 ), 2 ), 0.0, 1.0 );

   correctSSP(gl_Position);
}
