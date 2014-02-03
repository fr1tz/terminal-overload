// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

attribute vec4 vPosition;
attribute vec2 vTexCoord0;

uniform mat4x4 modelview;

varying vec4 hpos;
varying vec2 uv0;


void main()
{
   hpos = vec4( modelview * vPosition );
   gl_Position = hpos;

   uv0 = vTexCoord0.st;
   gl_Position.y *= -1;
}
