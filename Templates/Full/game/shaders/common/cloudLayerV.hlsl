// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Structures                                                                  
//-----------------------------------------------------------------------------

struct CloudVert
{
   float4 pos        : POSITION;
   float3 normal     : NORMAL;
   float3 binormal   : BINORMAL;
   float3 tangent    : TANGENT;
   float2 uv0        : TEXCOORD0;
};

struct ConnectData
{
   float4 hpos                : POSITION;   
   float4 texCoord12          : TEXCOORD0;
   float4 texCoord34          : TEXCOORD1;   
   float3 vLightTS            : TEXCOORD2;   // light vector in tangent space, denormalized
   float3 vViewTS             : TEXCOORD3;   // view vector in tangent space, denormalized
   float  worldDist           : TEXCOORD4;
};

//-----------------------------------------------------------------------------
// Uniforms                                                                        
//-----------------------------------------------------------------------------
uniform float4x4  modelview;
uniform float3    eyePosWorld;
uniform float3    sunVec;
uniform float2    texOffset0;
uniform float2    texOffset1;
uniform float2    texOffset2;
uniform float3    texScale;

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
ConnectData main( CloudVert IN )
{   
   ConnectData OUT;

   OUT.hpos = mul(modelview, IN.pos);
   
   // Offset the uv so we don't have a seam directly over our head.
   float2 uv = IN.uv0 + float2( 0.5, 0.5 );
   
   OUT.texCoord12.xy = uv * texScale.x;
   OUT.texCoord12.xy += texOffset0;
   
   OUT.texCoord12.zw = uv * texScale.y;
   OUT.texCoord12.zw += texOffset1;
   
   OUT.texCoord34.xy = uv * texScale.z;
   OUT.texCoord34.xy += texOffset2;
   
   OUT.texCoord34.z = IN.pos.z;
   OUT.texCoord34.w = 0.0;

   // Transform the normal, tangent and binormal vectors from object space to 
   // homogeneous projection space:
   float3 vNormalWS   = -IN.normal; 
   float3 vTangentWS  = -IN.tangent;
   float3 vBinormalWS = -IN.binormal;

   // Compute position in world space:
   float4 vPositionWS = IN.pos + float4( eyePosWorld, 1 ); //mul( IN.pos, objTrans );

   // Compute and output the world view vector (unnormalized):
   float3 vViewWS = eyePosWorld - vPositionWS.xyz;

   // Compute denormalized light vector in world space:
   float3 vLightWS = -sunVec;

   // Normalize the light and view vectors and transform it to the tangent space:
   float3x3 mWorldToTangent = float3x3( vTangentWS, vBinormalWS, vNormalWS );

   // Propagate the view and the light vectors (in tangent space):
   OUT.vLightTS = mul( vLightWS, mWorldToTangent );
   OUT.vViewTS  = mul( mWorldToTangent, vViewWS  );
   
   OUT.worldDist = saturate( pow( max( IN.pos.z, 0 ), 2 ) );

   return OUT;
}
