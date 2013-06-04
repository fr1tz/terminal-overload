// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "math/mPoint2.h"
#include "math/mPoint3.h"
#include "math/mPoint4.h"


const Point2I Point2I::One(1, 1);
const Point2I Point2I::Zero(0, 0);
const Point2I Point2I::Min(S32_MIN, S32_MIN);
const Point2I Point2I::Max(S32_MAX, S32_MAX);

const Point2F Point2F::One(1.0f, 1.0f);
const Point2F Point2F::Zero(0.0f, 0.0f);
const Point2F Point2F::Min(F32_MIN, F32_MIN);
const Point2F Point2F::Max(F32_MAX, F32_MAX);

const Point2D Point2D::One(1.0, 1.0);
const Point2D Point2D::Zero(0.0, 0.0);

const Point3I Point3I::One(1, 1, 1);
const Point3I Point3I::Zero(0, 0, 0);

const Point3F Point3F::One(1.0f, 1.0f, 1.0f);
const Point3F Point3F::Zero(0.0f, 0.0f, 0.0f);
const Point3F Point3F::Min(F32_MIN, F32_MIN, F32_MIN);
const Point3F Point3F::Max(F32_MAX, F32_MAX, F32_MAX);
const Point3F Point3F::UnitX(1.0f, 0.0f, 0.0f);
const Point3F Point3F::UnitY(0.0f, 1.0f, 0.0f);
const Point3F Point3F::UnitZ(0.0f, 0.0f, 1.0f);

const Point3D Point3D::One(1.0, 1.0, 1.0);
const Point3D Point3D::Zero(0.0, 0.0, 0.0);

const Point4I Point4I::One(1, 1, 1, 1);
const Point4I Point4I::Zero(0, 0, 0, 0);

const Point4F Point4F::One(1.0f, 1.0f, 1.0f, 1.0f);
const Point4F Point4F::Zero(0.0f, 0.0f, 0.0f, 0.0f);


Point3F mPerp( const Point3F &inVec )
{   
   AssertFatal( inVec.len() > 0.0f, "mPerp() - zero length vector has no perp!" );
   AssertFatal( inVec.isUnitLength(), "mPerp() - passed vector must be normalized!" );

   U32 idx = inVec.getLeastComponentIndex();

   Point3F vec( 0.0f, 0.0f, 0.0f );
   vec[idx] = 1.0f;

   Point3F outVec = mCross( inVec, vec );
   outVec.normalize();

   //AssertFatal( mIsZero( mDot( inVec, outVec ) ), "mPerp, failed to generate perpendicular" );

   return outVec;   
}

