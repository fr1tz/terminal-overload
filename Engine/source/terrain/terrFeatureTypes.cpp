// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "terrain/terrFeatureTypes.h"

#include "materials/materialFeatureTypes.h"


ImplementFeatureType( MFT_TerrainBaseMap, MFG_Texture, 100.0f, false );
ImplementFeatureType( MFT_TerrainParallaxMap, MFG_Texture, 101.0f, false );
ImplementFeatureType( MFT_TerrainDetailMap, MFG_Texture, 102.0f, false );
ImplementFeatureType( MFT_TerrainNormalMap, MFG_Texture, 103.0f, false );
ImplementFeatureType( MFT_TerrainMacroMap, MFG_Texture, 104.0f, false );
ImplementFeatureType( MFT_TerrainLightMap, MFG_Texture, 105.0f, false );
ImplementFeatureType( MFT_TerrainSideProject, MFG_Texture, 106.0f, false );
ImplementFeatureType( MFT_TerrainAdditive, MFG_PostProcess, 999.0f, false );

