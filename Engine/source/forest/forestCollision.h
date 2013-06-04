// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FORESTCOLLISION_H_
#define _FORESTCOLLISION_H_

#ifndef _CONVEX_H_
#include "collision/convex.h"
#endif
#ifndef _COLLISION_H_
#include "collision/collision.h"
#endif


class Forest;
class ForestItem;
class TSForestItemData;


class ForestConvex : public Convex
{
   typedef Convex Parent;
   friend class Forest;

public:

   ForestConvex() 
   { 
      mType = ForestConvexType; 
      mTransform.identity(); 
   }

   ForestConvex( const ForestConvex &cv ) 
   {
      mType          = ForestConvexType;
      mObject        = cv.mObject;
      mForestItemKey = cv.mForestItemKey;
      mTransform     = cv.mTransform;
      mData          = cv.mData;
      mScale         = cv.mScale;
      hullId         = cv.hullId;
      box            = box;
   }

   void           calculateTransform( const MatrixF &worldXfrm );
   const MatrixF& getTransform() const { return mTransform; }
   Box3F          getBoundingBox() const;
   Box3F          getBoundingBox( const MatrixF &mat, const Point3F &scale) const;
   Point3F        support( const VectorF &v ) const;
   void           getFeatures( const MatrixF &mat, const VectorF &n, ConvexFeature *cf );
   void           getPolyList( AbstractPolyList *list);

public:

   U32       hullId;
   Box3F     box;

protected:

   // JCF: ForestItemKey is a U32, didn't want to include forest.h here
   // fix me if ForestItemKey is changed to a class.
   U32 mForestItemKey;
   MatrixF mTransform;
   TSForestItemData *mData;
   F32 mScale;
};


#endif // _FORESTCOLLISION_H_