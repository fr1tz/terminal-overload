// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "T3D/physics/bullet/btDebugDraw.h"

#include "T3D/physics/bullet/btCasts.h"
#include "gfx/gfxDevice.h"
#include "math/util/frustum.h"
#include "gfx/primBuilder.h"


void BtDebugDraw::drawLine( const btVector3 &fromBt, const btVector3 &toBt, const btVector3 &color )
{
   Point3F from = btCast<Point3F>( fromBt );
   Point3F to = btCast<Point3F>( toBt );

   // Cull first if we have a frustum.
   //F32 distSquared = ( mCuller->getPosition() - from ).lenSquared();
   //if ( mCuller && distSquared > ( 150 * 150 ) ) //!mCuller->clipSegment( from, to ) )
      //return;

   // Do we need to flush the builder?
   if ( mVertexCount + 2 >= 1000 )
      flush();

   // Are we starting a new primitive?
   if ( mVertexCount == 0 )
      PrimBuild::begin( GFXLineList, 1000 );

   PrimBuild::color3f( color.x(), color.y(), color.z() );
   PrimBuild::vertex3f( from.x, from.y, from.z );
   PrimBuild::vertex3f( to.x, to.y, to.z );

   mVertexCount += 2;
}

void BtDebugDraw::drawTriangle(  const btVector3 &v0,
                                 const btVector3 &v1,
                                 const btVector3 &v2,
                                 const btVector3 &color, 
                                 btScalar /*alpha*/ )
{
	drawLine(v0,v1,color);
	drawLine(v1,v2,color);
	drawLine(v2,v0,color);
}

void BtDebugDraw::drawContactPoint( const btVector3 &pointOnB, 
                                    const btVector3 &normalOnB, 
                                    btScalar distance, 
                                    int lifeTime, const 
                                    btVector3 &color )
{
   drawLine( pointOnB, pointOnB+normalOnB*distance, color );
}

void BtDebugDraw::flush()
{
   // Do we have verts to render?
   if ( mVertexCount == 0 )
      return;

   PrimBuild::end();
   mVertexCount = 0;
}
