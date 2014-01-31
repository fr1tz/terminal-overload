// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// An implementation of "Practical Morphological Anti-Aliasing" from 
// GPU Pro 2 by Jorge Jimenez, Belen Masia, Jose I. Echevarria, 
// Fernando Navarro, and Diego Gutierrez.
//
// http://www.iryoku.com/mlaa/


uniform float2 texSize0;

void main( inout float4 position : POSITION0,
           inout float2 texcoord : TEXCOORD0)
{
   float2 PIXEL_SIZE = 1.0 / texSize0;   
   texcoord.xy += PIXEL_SIZE * 0.5;   
}
