// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "shaderGen/featureMgr.h"

#include "shaderGen/featureType.h"
#include "shaderGen/shaderFeature.h"
#include "core/util/safeDelete.h"
#include "core/module.h"


MODULE_BEGIN( ShaderGenFeatureMgr )

   MODULE_INIT_BEFORE( ShaderGen )
   MODULE_SHUTDOWN_AFTER( Sim ) // allow registered features to be removed before destroying singleton

   MODULE_INIT
   {
      ManagedSingleton< FeatureMgr >::createSingleton();
   }
   
   MODULE_SHUTDOWN
   {
      ManagedSingleton< FeatureMgr >::deleteSingleton();
   }

MODULE_END;


FeatureMgr::FeatureMgr()
   : mNeedsSort( false )
{
   VECTOR_SET_ASSOCIATION( mFeatures );
}

FeatureMgr::~FeatureMgr()
{
   unregisterAll();
}

void FeatureMgr::unregisterAll()
{
   FeatureInfoVector::iterator iter = mFeatures.begin();
   for ( ; iter != mFeatures.end(); iter++ )
   {
      if ( iter->feature )
         delete iter->feature;
   }

   mFeatures.clear();
   mNeedsSort = false;
}

const FeatureInfo& FeatureMgr::getAt( U32 index )
{
   if ( mNeedsSort )
   {
      mFeatures.sort( _featureInfoCompare );
      mNeedsSort = false;
   }

   AssertFatal( index < mFeatures.size(), "FeatureMgr::getAt() - Index out of range!" );

   return mFeatures[index];
}

ShaderFeature* FeatureMgr::getByType( const FeatureType &type )
{
   FeatureInfoVector::iterator iter = mFeatures.begin();
   for ( ; iter != mFeatures.end(); iter++ )
   {
      if ( *iter->type == type )
         return iter->feature;
   }

   return NULL;
}

void FeatureMgr::registerFeature(   const FeatureType &type, 
                                    ShaderFeature *feature )
{
   // Remove any existing feature first.
   unregisterFeature( type );

   // Now add the new feature.
   mFeatures.increment();
   mFeatures.last().type = &type;
   mFeatures.last().feature = feature;

   // Make sure we resort the features.
   mNeedsSort = true;
}

S32 QSORT_CALLBACK FeatureMgr::_featureInfoCompare( const FeatureInfo* a, const FeatureInfo* b )
{
   const FeatureType *typeA = a->type;
   const FeatureType *typeB = b->type;

   if ( typeA->getGroup() < typeB->getGroup() )
      return -1;
   else if ( typeA->getGroup() > typeB->getGroup() )
      return 1;
   else if ( typeA->getOrder() < typeB->getOrder() )
      return -1;
   else if ( typeA->getOrder() > typeB->getOrder() )
      return 1;
   else
      return 0;
}

void FeatureMgr::unregisterFeature( const FeatureType &type )
{
   FeatureInfoVector::iterator iter = mFeatures.begin();
   for ( ; iter != mFeatures.end(); iter++ )
   {
      if ( *iter->type != type )
         continue;

      delete iter->feature;
      mFeatures.erase( iter );
      return;
   }
}
