// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "lighting/common/lightMapParams.h"
#include "core/stream/bitStream.h"
#include "core/module.h"

MODULE_BEGIN( LightMapParams )
MODULE_INIT_AFTER( ShadowMapParams )
MODULE_INIT
{
   LightMapParams::Type = "LightMapParams";
}
MODULE_END;

LightInfoExType LightMapParams::Type( "" );

LightMapParams::LightMapParams( LightInfo *light ) :
   representedInLightmap(false), 
   includeLightmappedGeometryInShadow(false), 
   shadowDarkenColor(0.0f, 0.0f, 0.0f, -1.0f)
{
   
}

LightMapParams::~LightMapParams()
{

}

void LightMapParams::set( const LightInfoEx *ex )
{
   // TODO: Do we even need this?
}

void LightMapParams::packUpdate( BitStream *stream ) const
{
   stream->writeFlag(representedInLightmap);
   stream->writeFlag(includeLightmappedGeometryInShadow);
   stream->write(shadowDarkenColor);
}

void LightMapParams::unpackUpdate( BitStream *stream )
{
   representedInLightmap = stream->readFlag();
   includeLightmappedGeometryInShadow = stream->readFlag();
   stream->read(&shadowDarkenColor);

   // Always make sure that the alpha value of the shadowDarkenColor is -1.0
   shadowDarkenColor.alpha = -1.0f;
}