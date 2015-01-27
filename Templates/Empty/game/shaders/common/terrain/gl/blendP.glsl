// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "../terrain.glsl"
#include "../../gl/hlslCompat.glsl"

in vec2 layerCoord;
#define IN_layerCoord layerCoord
in vec2 texCoord;
#define IN_texCoord texCoord

uniform sampler2D layerTex;
uniform sampler2D textureMap;
uniform float texId;
uniform float layerSize;

out vec4 OUT_col;

void main()
{
   vec4 layerSample = round(texture( layerTex, IN_layerCoord ) * 255.0);

   float blend = calcBlend( texId, IN_layerCoord, layerSize, layerSample );

   if(blend - 0.0001 < 0.0)
      discard;

   OUT_col = vec4( texture( textureMap, IN_texCoord ).rgb, blend );
}
