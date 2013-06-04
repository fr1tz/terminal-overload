// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//-----------------------------------------------------------------------------
// Ray to triangle intersection test code originally by Tomas Akenine-Möller
// and Ben Trumbore.
// http://www.cs.lth.se/home/Tomas_Akenine_Moller/code/
// Ported to TGE by DAW, 2005-7-15
//-----------------------------------------------------------------------------

#ifndef _TRIRAYCHECK_H_
#define _TRIRAYCHECK_H_

#include "math/mPoint2.h"
#include "math/mPoint3.h"

bool intersect_triangle(Point3F orig, Point3F dir,
                   Point3F vert0, Point3F vert1, Point3F vert2,
                   F32& t, F32& u, F32& v);

//*** Taken from TSE, but based on the above
bool castRayTriangle(Point3F orig, Point3F dir, Point3F vert0, Point3F vert1, Point3F vert2, F32 &t, Point2F &bary);
bool castRayTriangle(const Point3D &orig, const Point3D &dir, const Point3D &vert0, const Point3D &vert1, const Point3D &vert2);

#endif // _TRIRAYCHECK_H_
