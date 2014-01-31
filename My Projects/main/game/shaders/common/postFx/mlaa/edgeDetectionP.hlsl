// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// An implementation of "Practical Morphological Anti-Aliasing" from 
// GPU Pro 2 by Jorge Jimenez, Belen Masia, Jose I. Echevarria, 
// Fernando Navarro, and Diego Gutierrez.
//
// http://www.iryoku.com/mlaa/

#include "shadergen:/autogenConditioners.h"

uniform sampler2D colorMapG  : register(S0);
uniform sampler2D prepassMap : register(S1);

uniform float3 lumaCoefficients;
uniform float threshold;
uniform float depthThreshold;


float4 main(   float2 texcoord : TEXCOORD0,
               float4 offset[2]: TEXCOORD1) : COLOR0 
{
   // Luma calculation requires gamma-corrected colors (texture 'colorMapG').
   //
   // Note that there is a lot of overlapped luma calculations; performance
   // can be improved if this luma calculation is performed in the main pass,
   // which may give you an edge if used in conjunction with a z prepass.

   float L = dot(tex2D(colorMapG, texcoord).rgb, lumaCoefficients);

   float Lleft = dot(tex2D(colorMapG, offset[0].xy).rgb, lumaCoefficients);
   float Ltop = dot(tex2D(colorMapG, offset[0].zw).rgb, lumaCoefficients);  
   float Lright = dot(tex2D(colorMapG, offset[1].xy).rgb, lumaCoefficients);
   float Lbottom = dot(tex2D(colorMapG, offset[1].zw).rgb, lumaCoefficients);

   float4 delta = abs(L.xxxx - float4(Lleft, Ltop, Lright, Lbottom));
   float4 edges = step(threshold, delta);

   // Add depth edges to color edges
   float D = prepassUncondition(prepassMap, texcoord).w;
   float Dleft = prepassUncondition(prepassMap, offset[0].xy).w;
   float Dtop  = prepassUncondition(prepassMap, offset[0].zw).w;
   float Dright = prepassUncondition(prepassMap, offset[1].xy).w;
   float Dbottom = prepassUncondition(prepassMap, offset[1].zw).w;

   delta = abs(D.xxxx - float4(Dleft, Dtop, Dright, Dbottom));
   edges += step(depthThreshold, delta);

   if (dot(edges, 1.0) == 0.0)
      discard;

   return edges;
}