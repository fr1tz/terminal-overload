// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/// The vertex shader used in the generation and caching of the
/// base terrain texture.

in vec4 vPosition;
in vec2 vTexCoord0;

out vec2 layerCoord;
out vec2 texCoord;

uniform vec2 texScale;

void main()
{
   gl_Position = vec4(vPosition.xyz, 1.0);
   layerCoord = vTexCoord0.st;
   texCoord = vTexCoord0.st * texScale;

   gl_Position.y *= -1;	
}
