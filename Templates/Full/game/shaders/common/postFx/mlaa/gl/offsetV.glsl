// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

// An implementation of "Practical Morphological Anti-Aliasing" from 
// GPU Pro 2 by Jorge Jimenez, Belen Masia, Jose I. Echevarria, 
// Fernando Navarro, and Diego Gutierrez.
//
// http://www.iryoku.com/mlaa/

#include "../../../gl/hlslCompat.glsl"

attribute vec4 vPosition;
attribute vec2 vTexCoord0;

#define IN_position  vPosition
#define IN_texcoord  vTexCoord0

#define OUT_position gl_Position
varying vec2 texcoord;
#define OUT_texcoord texcoord
varying vec4 offset[2];
#define OUT_offset offset

uniform vec2 texSize0;

void main()
{
   OUT_position = IN_position;
   vec2 PIXEL_SIZE = 1.0 / texSize0;

   OUT_texcoord = IN_texcoord;
   OUT_texcoord.xy += PIXEL_SIZE * 0.5;

   OUT_offset[0] = OUT_texcoord.xyxy + PIXEL_SIZE.xyxy * vec4(-1.0, 0.0, 0.0, -1.0);
   OUT_offset[1] = OUT_texcoord.xyxy + PIXEL_SIZE.xyxy * vec4( 1.0, 0.0, 0.0,  1.0);
   
   correctSSP(gl_Position);
}
