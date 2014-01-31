// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

/// The vertex shader used in the generation and caching of the
/// base terrain texture.

varying vec2 layerCoord;
varying vec2 texCoord;

uniform vec2 texScale;

void main()
{
   gl_Position = vec4(gl_Vertex.xyz, 1.0);
   layerCoord = gl_MultiTexCoord0.st;
   texCoord = gl_MultiTexCoord0.st * texScale;
}
