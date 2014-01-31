//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Features:
// Vert Position
// Diffuse Color
// Forward Shaded Material

struct VertData
{
   float3 position        : POSITION;
};


struct ConnectData
{
   float4 hpos            : POSITION;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
ConnectData main( VertData IN,
                  uniform float4x4 modelview       : register(C0)
)
{
   ConnectData OUT;

   // Vert Position
   OUT.hpos = mul(modelview, float4(IN.position.xyz,1));
   
   // Diffuse Color
   
   // Forward Shaded Material
   
   return OUT;
}
