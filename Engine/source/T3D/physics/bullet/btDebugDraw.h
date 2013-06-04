// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_BTDEBUGDRAW_H_
#define _T3D_PHYSICS_BTDEBUGDRAW_H_

#ifndef _BULLET_H_
#include "T3D/physics/bullet/bt.h"
#endif

class Frustum;


class BtDebugDraw : public btIDebugDraw
{
protected:

   /// The number of verts we've used in rendering.
   U32 mVertexCount;

   /// The frustum to use for culling or NULL.
   const Frustum *mCuller;

public:

   BtDebugDraw()
      :  mVertexCount( 0 ),
         mCuller( NULL )
   {
   }

   /// Sets the culler which we use to cull out primitives
   /// that are completely offscreen.
   void setCuller( const Frustum *culler ) { mCuller = culler; }

   /// Call this after debug drawing to submit any
   /// remaining primitives for rendering.
   void flush();

   // btIDebugDraw
	virtual void drawLine( const btVector3 &from, const btVector3 &to, const btVector3 &color );
   virtual void drawTriangle(const btVector3& v0,const btVector3& v1,const btVector3& v2,const btVector3& color, btScalar /*alpha*/);
   virtual void drawContactPoint( const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color );
   virtual void reportErrorWarning( const char *warningString ) {}
   virtual void draw3dText( const btVector3 &location, const char *textString ) {}
   virtual void setDebugMode( int debugMode ) {}
   virtual int getDebugMode() const { return DBG_DrawWireframe; }
};


#endif // _T3D_PHYSICS_BTDEBUGDRAW_H_