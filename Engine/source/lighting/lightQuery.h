// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _LIGHTQUERY_H_
#define _LIGHTQUERY_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _MSPHERE_H_
#include "math/mSphere.h"
#endif

#ifndef _MBOX_H_
#include "math/mBox.h"
#endif


class LightManager;
class LightInfo;


/// Used to gather an score lights for rendering.
class LightQuery
{
public:

   LightQuery( U32 maxLights = 4 );
   ~LightQuery();

   /// Set the query volume from a camera position and direction.
   void init(  const Point3F &cameraPos,
               const Point3F &cameraDir, 
               F32 viewDist );

   /// Set the query volume from a sphere.
   void init( const SphereF &bounds );

   /// Set the query volume from a box.
   void init( const Box3F &bounds );

   /// This returns the best lights based on the query volume.
   void getLights( LightInfo** outLights, U32 maxLights );

protected:

   void _scoreLights();

   static S32 _lightScoreCmp( LightInfo* const *a, LightInfo* const *b );

   /// The maximum lights to return from the query.
   const U32 mMaxLights;

   /// The sorted list of best lights.
	Vector<LightInfo*> mLights;

   /// The sphere used to query for lights.
   SphereF mVolume;
};


#endif // _LIGHTQUERY_H_
