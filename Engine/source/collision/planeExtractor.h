// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PLANEEXTRACTOR_H_
#define _PLANEEXTRACTOR_H_

#ifndef _MMATH_H_
#include "math/mMath.h"
#endif
#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _ABSTRACTPOLYLIST_H_
#include "collision/abstractPolyList.h"
#endif


//----------------------------------------------------------------------------

/// Fill a Vector<PlaneF> with the planes from the geometry passed through this
/// PolyList.
///
/// @see AbstractPolyList
class PlaneExtractorPolyList: public AbstractPolyList
{
public:
   // Internal data
   typedef Vector<Point3F> VertexList;
   VertexList mVertexList;

   Vector<PlaneF> mPolyPlaneList;

   // Set by caller
   Vector<PlaneF>* mPlaneList;

   //
   PlaneExtractorPolyList();
   ~PlaneExtractorPolyList();
   void clear();

   // Virtual methods
   bool isEmpty() const;
   U32  addPoint(const Point3F& p);
   U32  addPlane(const PlaneF& plane);
   void begin(BaseMatInstance* material,U32 surfaceKey);
   void plane(U32 v1,U32 v2,U32 v3);
   void plane(const PlaneF& p);
   void plane(const U32 index);
   void vertex(U32 vi);
   void end();

  protected:
   const PlaneF& getIndexedPlane(const U32 index);
};


#endif
