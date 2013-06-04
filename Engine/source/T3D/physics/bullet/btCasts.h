// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BULLET_CASTS_H_
#define _BULLET_CASTS_H_

#ifndef _BULLET_H_
#include "T3D/physics/bullet/bt.h"
#endif
#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif
#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif
#ifndef _MQUAT_H_
#include "math/mQuat.h"
#endif

template <class T, class F> inline T btCast( const F &from );

//-------------------------------------------------------------------------

template<>
inline Point3F btCast( const btVector3 &vec )
{
   return Point3F( vec.x(), vec.y(), vec.z() );
}

template<>
inline btVector3 btCast( const Point3F &point )
{
   return btVector3( point.x, point.y, point.z );
}

template<>
inline QuatF btCast( const btQuaternion &quat )
{
   /// The Torque quat has the opposite winding order.
   return QuatF( -quat.x(), -quat.y(), -quat.z(), quat.w() );
}

template<>
inline btQuaternion btCast( const QuatF &quat )
{
   /// The Torque quat has the opposite winding order.
   return btQuaternion( -quat.x, -quat.y, -quat.z, quat.w );
}

template<>
inline btTransform btCast( const MatrixF &xfm )
{
   btTransform out;
   out.getBasis().setValue(   xfm[0], xfm[1], xfm[2],
                              xfm[4], xfm[5], xfm[6],
                              xfm[8], xfm[9], xfm[10] );
   out.getOrigin().setValue(  xfm[3], xfm[7], xfm[11] );
   return out;
}

template<>
inline MatrixF btCast( const btTransform &xfm )
{
   MatrixF out;

   // Set the rotation.
   out.setRow( 0, btCast<Point3F>( xfm.getBasis()[0] ) );
   out.setRow( 1, btCast<Point3F>( xfm.getBasis()[1] ) );
   out.setRow( 2, btCast<Point3F>( xfm.getBasis()[2] ) );
   
   // The position.
   out[3] = xfm.getOrigin().x();
   out[7] = xfm.getOrigin().y();
   out[11] = xfm.getOrigin().z();

   // Clear out the rest.
   out[12] = out[13] = out[14] = 0.0f;
   out[15] = 1.0f;

   return out;
}

#endif // _BULLET_CASTS_H_