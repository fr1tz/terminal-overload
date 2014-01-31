//*****************************************************************************
// Torque -- HLSL procedural shader
//*****************************************************************************

// Features:
// Vert Position
// Diffuse Color
// Forward Shaded Material

struct ConnectData
{
};


struct Fragout
{
   float4 col : COLOR0;
};


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------
Fragout main( ConnectData IN,
              uniform float4    diffuseMaterialColor : register(C0)
)
{
   Fragout OUT;

   // Vert Position
   
   // Diffuse Color
   OUT.col = diffuseMaterialColor;
   
   // Forward Shaded Material
   

   return OUT;
}
