//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

// These are some simple wrappers for simple 
// HLSL compatibility.

#define float4 vec4
#define float3 vec3
#define float2 vec2

#define half float
#define half2 vec2
#define half3 vec3
#define half4 vec4

#define float4x4 mat4
#define float3x3 mat3
#define float2x2 mat2

#define texCUBE textureCube
#define tex2D texture2D
#define tex1D texture1D

#define samplerCUBE samplerCube

#define frac fract

vec4 tex2Dlod(sampler2D sampler, vec4 texCoord) { return texture2DLod(sampler, texCoord.xy, texCoord.w); }

#define lerp mix

void tSetMatrixRow(out float3x3 m, int row, float3 value)
{
   m[0][row] = value.x;
   m[1][row] = value.y;
   m[2][row] = value.z;
}

void tSetMatrixRow(out float4x4 m, int row, float4 value)
{
   m[0][row] = value.x;
   m[1][row] = value.y;
   m[2][row] = value.z;
   m[3][row] = value.w;
}

#define tGetMatrix3Row(matrix, row) float3(m[0][row], m[1][row], m[2][row])
#define tGetMatrix4Row(matrix, row) float4(m[0][row], m[1][row], m[2][row], m[3][row])

float3x3 float4x4to3x3(float4x4 m)
{   
   return float3x3( vec3(m[0]).xyz, m[1].xyz, m[2].xyz);
}

float3x3 float4x4to3x3_(float4x4 m)
{   
   return float3x3( vec3(m[0]), m[1].xyz, m[2].xyz);
}

mat4 mat4FromRow( float r0c0, float r0c1, float r0c2, float r0c3,
                  float r1c0, float r1c1, float r1c2, float r1c3,
                  float r2c0, float r2c1, float r2c2, float r2c3,
                  float r3c0, float r3c1, float r3c2, float r3c3 )
{
   return mat4( r0c0, r1c0, r2c0, r3c0,
                r0c1, r1c1, r2c1, r3c1,
                r0c2, r1c2, r2c2, r3c2,
                r0c3, r1c3, r2c3, r3c3 );
}

float saturate( float val ) { return clamp( val, 0.0, 1.0 ); }
vec2 saturate( vec2 val ) { return clamp( val, 0.0, 1.0 ); }
vec3 saturate( vec3 val ) { return clamp( val, 0.0, 1.0 ); }
vec4 saturate( vec4 val ) { return clamp( val, 0.0, 1.0 ); }

float round( float n ) { return sign( n ) * floor( abs( n ) + 0.5 ); }
vec2 round( vec2 n ) { return sign( n ) * floor( abs( n ) + 0.5 ); }
vec3 round( vec3 n ) { return sign( n ) * floor( abs( n ) + 0.5 ); }
vec4 round( vec4 n ) { return sign( n ) * floor( abs( n ) + 0.5 ); }

vec4 mul( mat4 m1, vec4 v1) { return m1*v1; }
vec4 mul( vec4 v1, mat4 m1) { return v1*m1; }
vec3 mul( vec3 v1, mat3 m1) { return v1*m1; }
vec3 mul( mat3 m1, vec3 v1) { return m1*v1; }
vec2 mul( mat2 m1, vec2 v1) { return m1*v1; }
mat3 mul( mat3 m1, mat3 m2) { return m1*m2; }

vec4 rsqrt( vec4 n ){ return inversesqrt( n ); }

#define invertY vec2

void correctSSP(inout vec4 vec) 
{ 
	vec.y *= -1;
}

#ifdef TORQUE_PIXEL_SHADER
	void clip(float a) { if(a < 0) discard;}
#endif
