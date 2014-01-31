// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//*****************************************************************************
// Box Filter
//*****************************************************************************
//-----------------------------------------------------------------------------
// Structures                                                                  
//-----------------------------------------------------------------------------
struct VertData
{
   float2 texCoord        : TEXCOORD0;
   float4 position        : POSITION;
};

struct ConnectData
{
   float4 hpos            : POSITION;
   float2 tex0            : TEXCOORD0;
};


//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0))
{
   ConnectData OUT;

   OUT.hpos = mul(modelview, IN.position);   
   OUT.tex0 = IN.texCoord;

   return OUT;
}
