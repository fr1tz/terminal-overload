// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// These are some simple wrappers for simple 
// HLSL compatibility.

#define float4 vec4
#define float3 vec3
#define float2 vec2

#define texCUBE textureCube
#define tex2D texture2D

#define lerp mix

float saturate( float val ) { return clamp( val, 0.0, 1.0 ); }
vec2 saturate( vec2 val ) { return clamp( val, 0.0, 1.0 ); }
vec3 saturate( vec3 val ) { return clamp( val, 0.0, 1.0 ); }
vec4 saturate( vec4 val ) { return clamp( val, 0.0, 1.0 ); }

float round( float n ) { return sign( n ) * floor( abs( n ) + 0.5 ); }
vec2 round( vec2 n ) { return sign( n ) * floor( abs( n ) + 0.5 ); }
vec3 round( vec3 n ) { return sign( n ) * floor( abs( n ) + 0.5 ); }
vec4 round( vec4 n ) { return sign( n ) * floor( abs( n ) + 0.5 ); }
