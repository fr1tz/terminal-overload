// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/// The vertex shader used in the generation and caching of the
/// base terrain texture.

struct VertData
{
   float3 position : POSITION;
   float2 texCoord : TEXCOORD0;
};

struct ConnectData
{
   float4 hpos : POSITION;
   float2 layerCoord : TEXCOORD0;
   float2 texCoord : TEXCOORD1;
};

ConnectData main( VertData IN,
                  uniform float2 texScale : register(C0) )
{
   ConnectData OUT;

   OUT.hpos = float4( IN.position.xyz, 1 );
   OUT.layerCoord = IN.texCoord;
   OUT.texCoord = IN.texCoord * texScale;

   return OUT;
}
