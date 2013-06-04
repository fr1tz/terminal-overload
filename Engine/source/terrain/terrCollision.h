// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TERRCOLL_H_
#define _TERRCOLL_H_

#ifndef _CONVEX_H_
#include "collision/convex.h"
#endif


class TerrainConvex : public Convex
{
   friend class TerrainBlock;
   TerrainConvex *square;     ///< Alternate convex if square is concave
   bool halfA;                ///< Which half of square
   bool split45;              ///< Square split pattern
   U32 squareId;              ///< Used to match squares
   U32 material;
   Point3F point[4];          ///< 3-4 vertices
   VectorF normal[2];
   Box3F box;                 ///< Bounding box

  public:

   TerrainConvex();
   
   TerrainConvex( const TerrainConvex& cv );

   // Convex
   Box3F getBoundingBox() const;
   Box3F getBoundingBox(const MatrixF& mat, const Point3F& scale) const;
   Point3F support(const VectorF& v) const;
   void getFeatures(const MatrixF& mat,const VectorF& n, ConvexFeature* cf);
   void getPolyList(AbstractPolyList* list);
};

#endif // _TERRCOLL_H_
