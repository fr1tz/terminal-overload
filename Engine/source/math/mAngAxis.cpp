// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "math/mAngAxis.h"
#include "math/mQuat.h"
#include "math/mMatrix.h"

AngAxisF & AngAxisF::set( const QuatF & q )
{
   angle = 2.0f * mAcos( q.w );
   F32 sinHalfAngle = mSqrt(q.x * q.x + q.y * q.y + q.z * q.z);
   if (sinHalfAngle != 0.0f)
      axis.set( q.x / sinHalfAngle, q.y / sinHalfAngle, q.z / sinHalfAngle );
   else
      axis.set(1.0f,0.0f,0.0f);
   return *this;
}

AngAxisF & AngAxisF::set( const MatrixF & mat )
{
   QuatF q( mat );
   set( q );
   return *this;
}

MatrixF * AngAxisF::setMatrix( MatrixF * mat ) const
{
   QuatF q( *this );
   return q.setMatrix( mat );
}

void AngAxisF::RotateX(F32 angle, MatrixF * mat)
{
   // for now...do it the easy way
   AngAxisF rotX(Point3F(1.0f,0.0f,0.0f),angle);
   rotX.setMatrix(mat);
}

void AngAxisF::RotateY(F32 angle, MatrixF * mat)
{
   // for now...do it the easy way
   AngAxisF rotY(Point3F(0.0f,1.0f,0.0f),angle);
   rotY.setMatrix(mat);
}

void AngAxisF::RotateZ(F32 angle, MatrixF * mat)
{
   // for now...do it the easy way
   AngAxisF rotZ(Point3F(0.0f,0.0f,1.0f),angle);
   rotZ.setMatrix(mat);
}

void AngAxisF::RotateX(F32 angle, const Point3F & from, Point3F * to)
{
   // for now...do it the easy way
   MatrixF mat;
   AngAxisF::RotateX(angle,&mat);
   mat.mulV(from,to);
}

void AngAxisF::RotateY(F32 angle, const Point3F & from, Point3F * to)
{
   // for now...do it the easy way
   MatrixF mat;
   AngAxisF::RotateY(angle,&mat);
   mat.mulV(from,to);
}

void AngAxisF::RotateZ(F32 angle, const Point3F & from, Point3F * to)
{
   // for now...do it the easy way
   MatrixF mat;
   AngAxisF::RotateZ(angle,&mat);
   mat.mulV(from,to);
}

