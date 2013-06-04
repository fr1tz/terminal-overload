// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MANGAXIS_H_
#define _MANGAXIS_H_

#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif

class MatrixF;
class QuatF;

//----------------------------------------------------------------------------
// rotation about an arbitrary axis through the origin:

class AngAxisF
{
  public:
   Point3F axis;
   F32  angle;

   AngAxisF();
   AngAxisF( const Point3F & _axis, F32 _angle );
   explicit AngAxisF( const MatrixF &m );
   explicit AngAxisF( const QuatF &q );

   AngAxisF& set( const Point3F & _axis, F32 _angle );
   AngAxisF& set( const MatrixF & m );
   AngAxisF& set( const QuatF & q );

   bool operator ==( const AngAxisF & c ) const;
   bool operator !=( const AngAxisF & c ) const;

   MatrixF * setMatrix( MatrixF * mat ) const;

   static void RotateX(F32 angle, MatrixF * mat);
   static void RotateY(F32 angle, MatrixF * mat);
   static void RotateZ(F32 angle, MatrixF * mat);

   static void RotateX(F32 angle, const Point3F & from, Point3F * to);
   static void RotateY(F32 angle, const Point3F & from, Point3F * to);
   static void RotateZ(F32 angle, const Point3F & from, Point3F * to);
};

//----------------------------------------------------------------------------
// AngAxisF implementation:

inline AngAxisF::AngAxisF()
{
}

inline AngAxisF::AngAxisF( const Point3F & _axis, F32 _angle )
{
   set(_axis,_angle);
}

inline AngAxisF::AngAxisF( const MatrixF & mat )
{
   set(mat);
}

inline AngAxisF::AngAxisF( const QuatF & quat )
{
   set(quat);
}

inline AngAxisF& AngAxisF::set( const Point3F & _axis, F32 _angle )
{
   axis = _axis;
   angle = _angle;
   return *this;
}

inline bool AngAxisF::operator ==( const AngAxisF & c ) const
{
   return mFabs(angle-c.angle) < 0.0001f && (axis == c.axis);
}

inline bool AngAxisF::operator !=( const AngAxisF & c ) const
{
   return !(*this == c);
}

#endif // _MANGAXIS_H_
