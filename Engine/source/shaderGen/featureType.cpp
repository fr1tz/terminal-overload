// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "shaderGen/featureType.h"

#include "shaderGen/featureSet.h"

FeatureTypeVector& FeatureType::_getTypes()
{
   // We create it as a method static so that 
   // its available to other statics regardless
   // of initialization order.
   static FeatureTypeVector theTypes;
   return theTypes;
}

void FeatureType::addDefaultTypes( FeatureSet *outFeatures )
{
   const FeatureTypeVector &types = _getTypes();
   for ( U32 i=0; i < types.size(); i++ )
   {
      if ( types[i]->isDefault() )
         outFeatures->addFeature( *types[i] );
   }   
}

FeatureType::FeatureType( const char *name, U32 group, F32 order, bool isDefault )
   :  mName( name ),
      mGroup( group ),
      mOrder( order ),
      mIsDefault( isDefault )
{
   FeatureTypeVector &types = _getTypes();

   #ifdef TORQUE_DEBUG
      for ( U32 i=0; i < types.size(); i++ )
         AssertFatal( !mName.equal( types[i]->getName() ), "FeatureType - This feature already exists!" );
   #endif

   mId = types.size();
   types.push_back( this );
}
