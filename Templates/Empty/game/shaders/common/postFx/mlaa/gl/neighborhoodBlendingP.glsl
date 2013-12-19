//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

// An implementation of "Practical Morphological Anti-Aliasing" from 
// GPU Pro 2 by Jorge Jimenez, Belen Masia, Jose I. Echevarria, 
// Fernando Navarro, and Diego Gutierrez.
//
// http://www.iryoku.com/mlaa/

#include "../../../gl/hlslCompat.glsl"

varying float2 texcoord;
varying float4 offset[2];

uniform sampler2D blendMap;
uniform sampler2D colorMapL;
uniform sampler2D colorMap;

// Dummy sampers to please include.
uniform sampler2D areaMap;
uniform sampler2D edgesMapL;
#include "./functions.glsl"


void main()
{
   // Fetch the blending weights for current pixel:
   float4 topLeft = tex2D(blendMap, texcoord);
   float bottom = tex2D(blendMap, offset[1].zw).g;
   float right = tex2D(blendMap, offset[1].xy).a;
   float4 a = float4(topLeft.r, bottom, topLeft.b, right);

   // Up to 4 lines can be crossing a pixel (one in each edge). So, we perform
   // a weighted average, where the weight of each line is 'a' cubed, which
   // favors blending and works well in practice.
   float4 w = a * a * a;

   // There is some blending weight with a value greater than 0.0?
   float sum = dot(w, float4(1.0));
   if (sum < 1e-5)
      discard;

   float4 color = float4(0.0);

   // Add the contributions of the possible 4 lines that can cross this pixel:
   #ifdef BILINEAR_FILTER_TRICK
      float4 coords = mad(float4( 0.0, -a.r, 0.0,  a.g), PIXEL_SIZE.yyyy, texcoord.xyxy);
      color = mad(tex2D(colorMapL, coords.xy), float4(w.r), color);
      color = mad(tex2D(colorMapL, coords.zw), float4(w.g), color);

      coords = mad(float4(-a.b,  0.0, a.a,  0.0), PIXEL_SIZE.xxxx, texcoord.xyxy);
      color = mad(tex2D(colorMapL, coords.xy), float4(w.b), color);
      color = mad(tex2D(colorMapL, coords.zw), float4(w.a), color);
   #else
      float4 C = tex2D(colorMap, texcoord);
      float4 Cleft = tex2D(colorMap, offset[0].xy);
      float4 Ctop = tex2D(colorMap, offset[0].zw);
      float4 Cright = tex2D(colorMap, offset[1].xy);
      float4 Cbottom = tex2D(colorMap, offset[1].zw);
      color = mad(lerp(C, Ctop, a.r), float4(w.r), color);
      color = mad(lerp(C, Cbottom, a.g), float4(w.g), color);
      color = mad(lerp(C, Cleft, a.b), float4(w.b), color);
      color = mad(lerp(C, Cright, a.a), float4(w.a), color);
   #endif

   // Normalize the resulting color and we are finished!
   gl_FragColor = color / sum; 
}