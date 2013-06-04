// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "collision/vertexPolyList.h"


VertexPolyList::VertexPolyList()
{
   VECTOR_SET_ASSOCIATION(mVertexList);
   mVertexList.reserve(100);

   mCurrObject       = NULL;
   mBaseMatrix       = MatrixF::Identity;
   mMatrix           = MatrixF::Identity;
   mTransformMatrix  = MatrixF::Identity;
   mScale.set(1.0f, 1.0f, 1.0f);

   mPlaneTransformer.setIdentity();

   mInterestNormalRegistered = false;
}

void VertexPolyList::clear()
{
   mVertexList.clear();
}

const PlaneF& VertexPolyList::getIndexedPlane(const U32 index)
{
   static const PlaneF dummy( 0, 0, 0, -1 );
   return dummy;
}

U32 VertexPolyList::addPoint( const Point3F &p )
{
   // Apply the transform
   Point3F tp = p * mScale;
   mMatrix.mulP( tp );

   Vector<Point3F>::iterator iter = mVertexList.begin();
   for ( ; iter != mVertexList.end(); iter++ )
   {
      if ( iter->equal( tp ) )
         return iter - mVertexList.begin();
   }

   mVertexList.push_back( tp );
   return mVertexList.size() - 1;
}
