// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _LIGHTMAPPARAMS_H_
#define _LIGHTMAPPARAMS_H_

#ifndef _LIGHTINFO_H_
#include "lighting/lightInfo.h"
#endif

class LightMapParams : public LightInfoEx
{
public:
   LightMapParams( LightInfo *light );
   virtual ~LightMapParams();

   /// The LightInfoEx hook type.
   static LightInfoExType Type;

   // LightInfoEx
   virtual void set( const LightInfoEx *ex );
   virtual const LightInfoExType& getType() const { return Type; }
   virtual void packUpdate( BitStream *stream ) const;
   virtual void unpackUpdate( BitStream *stream );

public:
   // We're leaving these public for easy access 
   // for console protected fields.

   bool representedInLightmap;   ///< This light is represented in lightmaps (static light, default: false)
   ColorF shadowDarkenColor;     ///< The color that should be used to multiply-blend dynamic shadows onto lightmapped geometry (ignored if 'representedInLightmap' is false)
   bool includeLightmappedGeometryInShadow; ///< This light should render lightmapped geometry during its shadow-map update (ignored if 'representedInLightmap' is false)
};

#endif
