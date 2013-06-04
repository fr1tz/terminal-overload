// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MATERIALFEATUREDATA_H_
#define _MATERIALFEATUREDATA_H_

#ifndef _UTIL_DELEGATE_H_
#include "core/util/delegate.h"
#endif
#ifndef _FEATURESET_H_
#include "shaderGen/featureSet.h"
#endif


class ProcessedMaterial;


//-----------------------------------------------------------------------------
// MaterialFeatureData, this is basically a series of flags which a material can
// ask for.  Shader processed materials will use the shadergen system to accomplish this,
// FF processed materials will do the best they can.  
//-----------------------------------------------------------------------------
struct MaterialFeatureData
{
public:

   // General feature data for a pass or for other purposes.
   FeatureSet features;

   // This is to give hints to shader creation code.  It contains
   //    all the features that are in a material stage instead of just
   //    the current pass.
   FeatureSet materialFeatures;

public:

   MaterialFeatureData();

   MaterialFeatureData( const MaterialFeatureData &data );

   MaterialFeatureData( const FeatureSet &handle );

   void clear();

   const FeatureSet& codify() const { return features; }

};


///
typedef Delegate< void( ProcessedMaterial *mat,
                        U32 stageNum,
                        MaterialFeatureData &fd, 
                        const FeatureSet &features) > MatFeaturesDelegate;

#endif // _MATERIALFEATUREDATA_H_
