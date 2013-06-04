// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#ifndef _LIGHTBASE_H_
#include "T3D/lightBase.h"
#endif


class PointLight : public LightBase
{
   typedef LightBase Parent;

protected:

   F32 mRadius;
 
   // LightBase
   void _conformLights();
   void _renderViz( SceneRenderState *state );

public:

   PointLight();
   virtual ~PointLight();

   // ConsoleObject
   DECLARE_CONOBJECT( PointLight );
   static void initPersistFields();

   // SceneObject
   virtual void setScale( const VectorF &scale );

   // NetObject
   U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
   void unpackUpdate( NetConnection *conn, BitStream *stream );  
};

#endif // _POINTLIGHT_H_
