// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "math/mOrientedBox.h"

#include "math/mMatrix.h"



//-----------------------------------------------------------------------------

bool OrientedBox3F::isContained( const Point3F& point ) const
{
   Point3F distToCenter = point - getCenter();
   for( U32 i = 0; i < 3; ++ i )
   {
      F32 coeff = mDot( distToCenter, getAxis( i ) );
      if( mFabs( coeff ) > getHalfExtents()[ i ] )
         return false;
   }

   return true;
}

//-----------------------------------------------------------------------------

void OrientedBox3F::set( const MatrixF& transform, const Point3F& extents )
{
   mCenter = transform.getPosition();

   mAxes[ RightVector ] = transform.getRightVector();
   mAxes[ ForwardVector ] = transform.getForwardVector();
   mAxes[ UpVector ] = transform.getUpVector();

   mHalfExtents = extents * 0.5f;

   _initPoints();
}

//-----------------------------------------------------------------------------

void OrientedBox3F::set( const MatrixF& transform, const Box3F& aabb )
{
   mCenter = aabb.getCenter();
   transform.mulP( mCenter );

   mAxes[ RightVector ] = transform.getRightVector();
   mAxes[ ForwardVector ] = transform.getForwardVector();
   mAxes[ UpVector ] = transform.getUpVector();

   mHalfExtents[ 0 ] = aabb.len_x() / 2.f;
   mHalfExtents[ 1 ] = aabb.len_y() / 2.f;
   mHalfExtents[ 2 ] = aabb.len_z() / 2.f;

   _initPoints();
}

//-----------------------------------------------------------------------------

void OrientedBox3F::_initPoints()
{
   const Point3F right = mAxes[ RightVector ] * mHalfExtents.x;
   const Point3F forward = mAxes[ ForwardVector ] * mHalfExtents.y;
   const Point3F up = mAxes[ UpVector ] * mHalfExtents.z;

   mPoints[ NearBottomLeft ] = mCenter - forward - right - up;
   mPoints[ NearBottomRight ] = mCenter - forward + right - up;
   mPoints[ NearTopLeft ] = mCenter - forward - right + up;
   mPoints[ NearTopRight ] = mCenter - forward + right + up;

   mPoints[ FarBottomLeft ] = mCenter + forward - right - up;
   mPoints[ FarBottomRight ] = mCenter + forward + right - up;
   mPoints[ FarTopLeft ] = mCenter + forward - right + up;
   mPoints[ FarTopRight ] = mCenter + forward + right + up;
}
