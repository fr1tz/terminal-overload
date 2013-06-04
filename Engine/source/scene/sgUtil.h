// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SGUTIL_H_
#define _SGUTIL_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif

class Frustum;
class RectI;
class MatrixF;
class PlaneF;

struct SGWinding
{
   Point3F points[32];
   U32     numPoints;
};

bool sgComputeNewFrustum(const Frustum    &oldFrustum,
                         const F64        nearPlane,
                         const F64        farPlane,
                         const RectI&     oldViewport,
                         const SGWinding* windings,
                         const U32        numWindings,
                         const MatrixF&   modelview,
                         F64              *newFrustum,
                         RectI&           newViewport,
                         const bool       flippedMatrix);

/// Compute frustrum planes.
///
/// Frustum parameters are:
///  - [0] = left
///  - [1] = right
///  - [2] = top
///  - [3] = bottom
///  - [4] = near
///  - [5] = far
void sgComputeOSFrustumPlanes(const F64      frustumParameters[6],
                              const MatrixF& worldSpaceToObjectSpace,
                              const Point3F& wsCamPoint,
                              PlaneF&        outFarPlane,
                              PlaneF&        outXMinPlane,
                              PlaneF&        outXMaxPlane,
                              PlaneF&        outYMinPlane,
                              PlaneF&        outYMaxPlane);

void sgOrientClipPlanes(PlaneF * planes, const Point3F & camPos, const Point3F & leftUp, const Point3F & leftDown, const Point3F & rightUp, const Point3F & rightDown);

#endif  // _H_SGUTIL_
