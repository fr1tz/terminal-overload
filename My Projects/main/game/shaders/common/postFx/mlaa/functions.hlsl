// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// An implementation of "Practical Morphological Anti-Aliasing" from 
// GPU Pro 2 by Jorge Jimenez, Belen Masia, Jose I. Echevarria, 
// Fernando Navarro, and Diego Gutierrez.
//
// http://www.iryoku.com/mlaa/


uniform float2 texSize0;

#if !defined(PIXEL_SIZE)
#define PIXEL_SIZE (1.0 / texSize0)
#define MAX_SEARCH_STEPS 8    
#define MAX_DISTANCE 33
#endif

// Typical Multiply-Add operation to ease translation to assembly code.

float4 mad(float4 m, float4 a, float4 b) 
{
   #if defined(XBOX)
      float4 result;
      asm {
         mad result, m, a, b
      };
      return result;
   #else
      return m * a + b;
   #endif
}


// This one just returns the first level of a mip map chain, which allow us to
// avoid the nasty ddx/ddy warnings, even improving the performance a little 
// bit.
float4 tex2Dlevel0(sampler2D map, float2 texcoord) 
{
   return tex2Dlod(map, float4(texcoord, 0.0, 0.0));
}


// Same as above, this eases translation to assembly code;
float4 tex2Doffset(sampler2D map, float2 texcoord, float2 offset) 
{
   #if defined(XBOX) && MAX_SEARCH_STEPS < 6
      float4 result;
      float x = offset.x;
      float y = offset.y;
      asm {
         tfetch2D result, texcoord, map, OffsetX = x, OffsetY = y
      };
      return result;
   #else
      return tex2Dlevel0(map, texcoord + PIXEL_SIZE * offset);
   #endif
}


// Ok, we have the distance and both crossing edges, can you please return 
// the float2 blending weights?
float2 Area(float2 distance, float e1, float e2) 
{
   // * By dividing by areaSize - 1.0 below we are implicitely offsetting to
   //   always fall inside of a pixel
   // * Rounding prevents bilinear access precision problems
   float areaSize = MAX_DISTANCE * 5.0;
   float2 pixcoord = MAX_DISTANCE * round(4.0 * float2(e1, e2)) + distance;
   float2 texcoord = pixcoord / (areaSize - 1.0);
   return tex2Dlevel0(areaMap, texcoord).rg;
}


// Search functions for the 2nd pass.
float SearchXLeft(float2 texcoord) 
{
   // We compare with 0.9 to prevent bilinear access precision problems.
   float i;
   float e = 0.0;
   for (i = -1.5; i > -2.0 * MAX_SEARCH_STEPS; i -= 2.0) 
   {
      e = tex2Doffset(edgesMapL, texcoord, float2(i, 0.0)).g;
      [flatten] if (e < 0.9) break;
   }
   return max(i + 1.5 - 2.0 * e, -2.0 * MAX_SEARCH_STEPS);
}

// Search functions for the 2nd pass.
float SearchXRight(float2 texcoord) 
{
   float i;
   float e = 0.0;
   for (i = 1.5; i < 2.0 * MAX_SEARCH_STEPS; i += 2.0) 
   {
      e = tex2Doffset(edgesMapL, texcoord, float2(i, 0.0)).g;
      [flatten] if (e < 0.9) break;
   }
   return min(i - 1.5 + 2.0 * e, 2.0 * MAX_SEARCH_STEPS);
}

// Search functions for the 2nd pass.
float SearchYUp(float2 texcoord) 
{
   float i;
   float e = 0.0;
   for (i = -1.5; i > -2.0 * MAX_SEARCH_STEPS; i -= 2.0) 
   {
      e = tex2Doffset(edgesMapL, texcoord, float2(i, 0.0).yx).r;
      [flatten] if (e < 0.9) break;
   }
   return max(i + 1.5 - 2.0 * e, -2.0 * MAX_SEARCH_STEPS);
}

// Search functions for the 2nd pass.
float SearchYDown(float2 texcoord)
{
   float i;
   float e = 0.0;
   for (i = 1.5; i < 2.0 * MAX_SEARCH_STEPS; i += 2.0) 
   {
      e = tex2Doffset(edgesMapL, texcoord, float2(i, 0.0).yx).r;
      [flatten] if (e < 0.9) break;
   }
   return min(i - 1.5 + 2.0 * e, 2.0 * MAX_SEARCH_STEPS);
}
