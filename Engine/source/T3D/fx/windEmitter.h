// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _WINDEMITTER_H_
#define _WINDEMITTER_H_

#ifndef _MPOINT3_H_
   #include "math/mPoint3.h"
#endif
#ifndef _MSPHERE_H_
   #include "math/mSphere.h"
#endif
#ifndef _TVECTOR_H_
   #include "core/util/tVector.h"
#endif

class WindEmitter;

/// A vector of WindEmitter pointers.
typedef Vector<WindEmitter*> WindEmitterList;


class WindEmitter
{
public:
   WindEmitter();
   ~WindEmitter();

   operator const SphereF&() const { return mSphere; }

   void update( const Point3F& pos, const VectorF& velocity );

   void setPosition( const Point3F& pos );

   void setRadius( F32 radius );

   void setStrength( F32 strength );

   void setTurbulency( F32 frequency, F32 strength );

   const Point3F& getCenter() const { return mSphere.center; }

   F32 getRadius() const { return mSphere.radius; }

   F32 getStrength() const { return mStrength; }

   F32 getTurbulenceFrequency() const { return mTurbulenceFrequency; }

   F32 getTurbulenceStrength() const { return mTurbulenceStrength; }

   const VectorF& getVelocity() const { return mVelocity; }


   static bool findBest( const Point3F& cameraPos, 
                         const VectorF& cameraDir,
                         F32 viewDistance,
                         U32 maxResults,
                         WindEmitterList* results );

protected:
   SphereF mSphere;

   VectorF mVelocity;

   F32 mStrength;
   F32 mTurbulenceFrequency;
   F32 mTurbulenceStrength;
   F32 mScore;

   bool mEnabled;

   static WindEmitterList smAllEmitters;

   static S32 QSORT_CALLBACK _sortByScore( const void* a, const void* b );
};

#endif // _WINDEMITTER_H_
