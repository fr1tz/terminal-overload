// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#define IN_HLSL
#include "hlslStructs.h"

//-----------------------------------------------------------------------------
// Structures                                                                  
//-----------------------------------------------------------------------------

struct ConnectData
{
   float4 hpos            : POSITION;
   float2 texCoord        : TEXCOORD0;
   float4 tex2            : TEXCOORD1;
};

//-----------------------------------------------------------------------------
// Main                                                                        
//-----------------------------------------------------------------------------
ConnectData main( VertexIn_PNTTTB IN,
                  uniform float4x4 modelview   : register(C0)
)
{
   ConnectData OUT;
   OUT.hpos = mul(modelview, IN.pos);

   float4x4 texGenTest = { 0.5,  0.0,  0.0,  0.5,
                           0.0, -0.5,  0.0,  0.5,
                           0.0,  0.0,  1.0,  0.0,
                           0.0,  0.0,  0.0,  1.0 };
                           
   OUT.texCoord = IN.uv0;
   OUT.tex2 = mul( texGenTest, OUT.hpos );
   
   return OUT;
}
