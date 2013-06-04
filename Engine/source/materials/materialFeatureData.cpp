// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "materials/materialFeatureData.h"


MaterialFeatureData::MaterialFeatureData()
{
}

MaterialFeatureData::MaterialFeatureData( const MaterialFeatureData &data )
   :  features( data.features ),
      materialFeatures( data.materialFeatures )
{
}

MaterialFeatureData::MaterialFeatureData( const FeatureSet &handle )
   :  features( handle )
{
}

void MaterialFeatureData::clear()
{
   features.clear();
   materialFeatures.clear();
}
