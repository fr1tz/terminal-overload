// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/// The vertex shader used in the generation and caching of the
/// base terrain texture.

attribute vec4 vPosition;
attribute vec2 vTexCoord0;

varying vec2 layerCoord;
varying vec2 texCoord;

uniform vec2 texScale;

void main()
{
   gl_Position = vec4(vPosition.xyz, 1.0);
   layerCoord = vTexCoord0.st;
   texCoord = vTexCoord0.st * texScale;

   gl_Position.y *= -1;	
}
