// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MSPHERE_H_
#define _MSPHERE_H_

#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif


class SphereF
{
public:
   Point3F center;
   F32     radius;

public:
   SphereF() { }
   SphereF( const Point3F& in_rPosition, const F32 in_rRadius )
    : center(in_rPosition),
      radius(in_rRadius)
   {
      if ( radius < 0.0f )
         radius = 0.0f;
   }

   bool isContained( const Point3F& in_rContain ) const;
   bool isContained( const SphereF& in_rContain ) const;
   bool isIntersecting( const SphereF& in_rIntersect ) const;
   bool intersectsRay( const Point3F &start, const Point3F &end ) const;

   F32 distanceTo( const Point3F &pt ) const;
   F32 squareDistanceTo( const Point3F &pt ) const;
};

//-------------------------------------- INLINES
//
inline bool SphereF::isContained( const Point3F& in_rContain ) const
{
   F32 distSq = (center - in_rContain).lenSquared();

   return (distSq <= (radius * radius));
}

inline bool SphereF::isContained( const SphereF& in_rContain ) const
{
   if (radius < in_rContain.radius)
      return false;

   // Since our radius is guaranteed to be >= other's, we
   //  can dodge the sqrt() here.
   //
   F32 dist = (in_rContain.center - center).lenSquared();

   return (dist <= ((radius - in_rContain.radius) *
                    (radius - in_rContain.radius)));
}

inline bool SphereF::isIntersecting( const SphereF& in_rIntersect ) const
{
   F32 distSq = (in_rIntersect.center - center).lenSquared();

   return (distSq <= ((in_rIntersect.radius + radius) *
                      (in_rIntersect.radius + radius)));
}

inline F32 SphereF::distanceTo( const Point3F &toPt ) const
{
   return (center - toPt).len() - radius;
}

#endif //_SPHERE_H_
