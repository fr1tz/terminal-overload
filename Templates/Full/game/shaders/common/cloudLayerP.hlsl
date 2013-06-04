// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "torque.hlsl"

//-----------------------------------------------------------------------------
// Structures                                                                  
//-----------------------------------------------------------------------------
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
uniform sampler2D normalHeightMap : register(S0);
uniform float3    ambientColor;
uniform float3    sunColor;
uniform float     cloudCoverage;
uniform float3    cloudBaseColor;
uniform float	  cloudExposure;

//-----------------------------------------------------------------------------
// Globals                                                                        
//-----------------------------------------------------------------------------
// The per-color weighting to be used for luminance calculations in RGB order.
static const float3 LUMINANCE_VECTOR  = float3(0.2125f, 0.7154f, 0.0721f);


//-----------------------------------------------------------------------------
// Functions                                                                        
//-----------------------------------------------------------------------------

// Calculates the Rayleigh phase function
float getRayleighPhase( float angle )
{
   return 0.75 * ( 1.0 + pow( angle, 2 ) );	
}

// Returns the output rgb color given a texCoord and parameters it uses
// for lighting calculation.
float3 ComputeIllumination( float2 texCoord, 
                            float3 vLightTS, 
                            float3 vViewTS, 
                            float3 vNormalTS )
{   
   //return noiseNormal;
   //return vNormalTS;
   
   float3 vLightTSAdj = float3( -vLightTS.x, -vLightTS.y, vLightTS.z );
   
   float dp = dot( vNormalTS, vLightTSAdj );
   
   // Calculate the amount of illumination (lightTerm)...      
   
   // We do both a rim lighting effect and a halfLambertian lighting effect
   // and combine the result.
   float halfLambertTerm = saturate( pow( dp * 0.5 + 0.5, 1 ) );
   float rimLightTerm = pow( ( 1.0 - dp ), 1.0 );   
   float lightTerm = saturate( halfLambertTerm * 1.0 + rimLightTerm * dp );
   lightTerm *= 0.5;
   
   // Use a simple RayleighPhase function to simulate single scattering towards
   // the camera.
   float angle = dot( vLightTS, vViewTS );
   lightTerm *= getRayleighPhase( angle );
   
   // Combine terms and colors into the output color.   
   //float3 lightColor = ( lightTerm * sunColor * fOcclusionShadow ) + ambientColor;   
   float3 lightColor = lerp( ambientColor, sunColor, lightTerm );
   //lightColor = lerp( lightColor, ambientColor, cloudCoverage );
   float3 finalColor = cloudBaseColor * lightColor;
   
   return finalColor;
}   

float4 main( ConnectData IN ) : COLOR
{ 
   //  Normalize the interpolated vectors:
   float3 vViewTS   = normalize( IN.vViewTS  );
   float3 vLightTS  = normalize( IN.vLightTS );
     
   float4 cResultColor = float4( 0, 0, 0, 1 );
    
   float2 texSample = IN.texCoord12.xy;
   
   float4 noise1 = tex2D( normalHeightMap, IN.texCoord12.zw );
   noise1 = normalize( ( noise1 - 0.5 ) * 2.0 );   
   //return noise1;
   
   float4 noise2 = tex2D( normalHeightMap, IN.texCoord34.xy );
   noise2 = normalize( ( noise2 - 0.5 ) * 2.0 );
   //return noise2;
      
   float3 noiseNormal = normalize( noise1 + noise2 ).xyz;
   //return float4( noiseNormal, 1.0 );
   
   float noiseHeight = noise1.a * noise2.a * ( cloudCoverage / 2.0 + 0.5 );         

   float3 vNormalTS = normalize( tex2D( normalHeightMap, texSample ).xyz * 2.0 - 1.0 );   
   vNormalTS += noiseNormal;
   vNormalTS = normalize( vNormalTS );   
   
   // Compute resulting color for the pixel:
   cResultColor.rgb = ComputeIllumination( texSample, vLightTS, vViewTS, vNormalTS );
      
   float coverage = ( cloudCoverage - 0.5 ) * 2.0;
   cResultColor.a = tex2D( normalHeightMap, texSample ).a + coverage + noiseHeight;     
   
   if ( cloudCoverage > -1.0 )
      cResultColor.a /= 1.0 + coverage;
        
   cResultColor.a = saturate( cResultColor.a * pow( saturate(cloudCoverage), 0.25 ) );

   cResultColor.a = lerp( cResultColor.a, 0.0, 1.0 - pow(IN.worldDist,2.0) );
   
   cResultColor.rgb *= cloudExposure;

   return hdrEncode( cResultColor );
}   
