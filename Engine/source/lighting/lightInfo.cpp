// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "lighting/lightInfo.h"

#include "math/mMath.h"
#include "core/color.h"
#include "gfx/gfxCubemap.h"
#include "console/simObject.h"
#include "math/mathUtils.h"


LightInfoExType::LightInfoExType( const char *type )
{
   TypeMap::Iterator iter = getTypeMap().find( type );
   if ( iter == getTypeMap().end() )
      iter = getTypeMap().insertUnique( type, getTypeMap().size() );

   mTypeIndex = iter->value;
}


LightInfo::LightInfo() 
   :  mTransform( true ), 
      mColor( 0.0f, 0.0f, 0.0f, 1.0f ), 
      mBrightness( 1.0f ),
      mAmbient( 0.0f, 0.0f, 0.0f, 1.0f ), 
      mRange( 1.0f, 1.0f, 1.0f ),
      mInnerConeAngle( 90.0f ), 
      mOuterConeAngle( 90.0f ),
      mType( Vector ),
      mCastShadows( false ),
      mPriority( 1.0f ),
      mScore( 0.0f ),
      mDebugRender( false )
{
}

LightInfo::~LightInfo()
{
   deleteAllLightInfoEx();
}

void LightInfo::set( const LightInfo *light )
{
   mTransform = light->mTransform;
   mColor = light->mColor;
   mBrightness = light->mBrightness;
   mAmbient = light->mAmbient;
   mRange = light->mRange;
   mInnerConeAngle = light->mInnerConeAngle;
   mOuterConeAngle = light->mOuterConeAngle;
   mType = light->mType;
   mCastShadows = light->mCastShadows;

   for ( U32 i=0; i < mExtended.size(); i++ )
   {
      LightInfoEx *ex = light->mExtended[ i ];
      if ( ex )
         mExtended[i]->set( ex );
      else
      {
         delete mExtended[i];
         mExtended[i] = NULL;
      }
   }
}

void LightInfo::setGFXLight( GFXLightInfo *outLight )
{
   switch( getType() )
   {
      case LightInfo::Point :
         outLight->mType = GFXLightInfo::Point;
         break;
      case LightInfo::Spot :
         outLight->mType = GFXLightInfo::Spot;
         break;
      case LightInfo::Vector:
         outLight->mType = GFXLightInfo::Vector;
         break;
      case LightInfo::Ambient:
         outLight->mType = GFXLightInfo::Ambient;
         break;
      default:
         break;
   }

   outLight->mPos = getPosition();
   outLight->mDirection = getDirection();
   outLight->mColor = mColor * mBrightness;
   outLight->mAmbient = mAmbient;
   outLight->mRadius = mRange.x;
   outLight->mInnerConeAngle = mInnerConeAngle;
   outLight->mOuterConeAngle = mOuterConeAngle;
}

void LightInfo::setDirection( const VectorF &dir )
{
   MathUtils::getMatrixFromForwardVector( mNormalize( dir ), &mTransform );
}

void LightInfo::deleteExtended( const LightInfoExType& type )
{
   if ( type >= mExtended.size() )
      return;

   SAFE_DELETE( mExtended[ type ] );
}

void LightInfo::deleteAllLightInfoEx()
{
   for ( U32 i = 0; i < mExtended.size(); i++ )
      delete mExtended[ i ];

   mExtended.clear();
}

LightInfoEx* LightInfo::getExtended( const LightInfoExType &type ) const
{
   if ( type >= mExtended.size() )
      return NULL;

   return mExtended[ type ];
}

void LightInfo::addExtended( LightInfoEx *lightInfoEx )
{
   AssertFatal( lightInfoEx, "LightInfo::addExtended() - Got null extended light info!" );
   
   const LightInfoExType &type = lightInfoEx->getType();

   while ( mExtended.size() <= type )
      mExtended.push_back( NULL );

   delete mExtended[type];
   mExtended[type] = lightInfoEx;
}

void LightInfo::packExtended( BitStream *stream ) const
{
   for ( U32 i = 0; i < mExtended.size(); i++ )
      if ( mExtended[ i ] ) 
         mExtended[ i ]->packUpdate( stream );
}

void LightInfo::unpackExtended( BitStream *stream )
{
   for ( U32 i = 0; i < mExtended.size(); i++ )
      if ( mExtended[ i ] ) 
         mExtended[ i ]->unpackUpdate( stream );
}

void LightInfo::getWorldToLightProj( MatrixF *outMatrix ) const
{
   if ( mType == Spot )
   {
      // For spots we need to include the cone projection.
      F32 fov = mDegToRad( getOuterConeAngle() );
      F32 range = getRange().x;
      MatrixF proj;
      MathUtils::makeProjection( &proj, fov, 1.0f, range * 0.01f, range, true );
      
      MatrixF light = getTransform();
      light.inverse();

      *outMatrix = proj * light;
      return;
   }
   else
   {
      // The other lights just use the light transform.
      *outMatrix = getTransform();
      outMatrix->inverse();
   }
}

void LightInfoList::registerLight( LightInfo *light )
{
   if(!light)
      return;
   // just add the light, we'll try to scan for dupes later...
   push_back(light);
}

void LightInfoList::unregisterLight( LightInfo *light )
{
   // remove all of them...
   LightInfoList &list = *this;
   for(U32 i=0; i<list.size(); i++)
   {
      if(list[i] != light)
         continue;

      // this moves last to i, which allows
      // the search to continue forward...
      list.erase_fast(i);
      // want to check this location again...
      i--;
   }
}
