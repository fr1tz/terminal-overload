// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//
// A tip of the hat....
//
// The following wind effects were derived from the GPU Gems 
// 3 chapter "Vegetation Procedural Animation and Shading in Crysis"
// by Tiago Sousa of Crytek.
//

float4 smoothCurve( float4 x )
{
   return x * x * ( 3.0 - 2.0 * x );
}

float4 triangleWave( float4 x )
{
   return abs( frac( x + 0.5 ) * 2.0 - 1.0 );
}

float4 smoothTriangleWave( float4 x )
{
   return smoothCurve( triangleWave( x ) );
}

float3 windTrunkBending( float3 vPos, float2 vWind, float fBendFactor )
{
   // Smooth the bending factor and increase 
   // the near by height limit.
   fBendFactor += 1.0;
   fBendFactor *= fBendFactor;
   fBendFactor = fBendFactor * fBendFactor - fBendFactor;

   // Displace the vert.
   float3 vNewPos = vPos;
   vNewPos.xy += vWind * fBendFactor;

   // Limit the length which makes the bend more 
   // spherical and prevents stretching.
   float fLength = length( vPos );
   vPos = normalize( vNewPos ) * fLength;

   return vPos;
}

float3 windBranchBending(  float3 vPos,
                           float3 vNormal,

                           float fTime, 
                           float fWindSpeed,

                           float fBranchPhase,
                           float fBranchAmp,
                           float fBranchAtten,

                           float fDetailPhase,
                           float fDetailAmp,
                           float fDetailFreq,

                           float fEdgeAtten )
{
   float fVertPhase = dot( vPos, fDetailPhase + fBranchPhase );

   float2 vWavesIn = fTime + float2( fVertPhase, fBranchPhase );

   float4 vWaves = ( frac( vWavesIn.xxyy *
                           float4( 1.975, 0.793, 0.375, 0.193 ) ) *
                           2.0 - 1.0 ) * fWindSpeed * fDetailFreq;

   vWaves = smoothTriangleWave( vWaves );

   float2 vWavesSum = vWaves.xz + vWaves.yw;

   // We want the branches to bend both up and down.
   vWavesSum.y = 1 - ( vWavesSum.y * 2 );

   vPos += vWavesSum.xxy * float3(  fEdgeAtten * fDetailAmp * vNormal.xy,
                                    fBranchAtten * fBranchAmp );

   return vPos;
}
