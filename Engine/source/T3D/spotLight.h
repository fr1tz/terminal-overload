// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#ifndef _LIGHTBASE_H_
#include "T3D/lightBase.h"
#endif


class SpotLight : public LightBase
{
   typedef LightBase Parent;

protected:

   F32 mRange;

   F32 mInnerConeAngle;

   F32 mOuterConeAngle;

   // LightBase
   void _conformLights();
   void _renderViz( SceneRenderState *state );

public:

   SpotLight();
   virtual ~SpotLight();

   // ConsoleObject
   DECLARE_CONOBJECT( SpotLight );
   static void initPersistFields();

   // SceneObject
   virtual void setScale( const VectorF &scale );

   // NetObject
   U32 packUpdate( NetConnection *conn, U32 mask, BitStream *stream );
   void unpackUpdate( NetConnection *conn, BitStream *stream );  
};

#endif // _SPOTLIGHT_H_
