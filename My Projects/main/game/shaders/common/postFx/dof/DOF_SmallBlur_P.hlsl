// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// This vertex and pixel shader applies a 3 x 3 blur to the image in  
// colorMapSampler, which is the same size as the render target.  
// The sample weights are 1/16 in the corners, 2/16 on the edges,  
// and 4/16 in the center.  

uniform sampler2D colorSampler;  // Output of DofNearCoc()  

struct Pixel
{  
   float4 position : POSITION;  
   float4 texCoords : TEXCOORD0;  
};  

float4 main( Pixel IN ) : COLOR
{  
   float4 color;  
   color = 0.0;  
   color += tex2D( colorSampler, IN.texCoords.xz );  
   color += tex2D( colorSampler, IN.texCoords.yz );  
   color += tex2D( colorSampler, IN.texCoords.xw );  
   color += tex2D( colorSampler, IN.texCoords.yw );  
   return color / 4.0;  
}  