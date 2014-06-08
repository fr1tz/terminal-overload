// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MQUADPATCH_H_
#define _MQUADPATCH_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif
#ifndef _MSPLINEPATCH_H_
#include "math/mSplinePatch.h"
#endif

//------------------------------------------------------------------------------
/// Quadratic spline patch.  This is a special type of spline that only had 3 control points.
/// @see SplinePatch
class QuadPatch : public SplinePatch
{
   typedef SplinePatch Parent;

private:
   Point3F a, b, c;

   void calcABC( const Point3F *points );

public:

   QuadPatch();

   virtual void   calc( F32 t, Point3F &result );
   virtual void   calc( Point3F *points, F32 t, Point3F &result );
   virtual void   setControlPoint( Point3F &point, S32 index );
   virtual void   submitControlPoints( SplCtrlPts &points );


};



#endif
