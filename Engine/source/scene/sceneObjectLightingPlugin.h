// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SCENEOBJECTLIGHTINGPLUGIN_H_
#define _SCENEOBJECTLIGHTINGPLUGIN_H_

class SceneObject;
class NetConnection;
class BitStream;

class SceneObjectLightingPlugin 
{
   public:

      virtual ~SceneObjectLightingPlugin() {}

      /// Reset light plugin to clean state.
      virtual void reset() {}

      // Called by statics
      virtual U32  packUpdate( SceneObject* obj, U32 checkMask, NetConnection* conn, U32 mask, BitStream* stream ) = 0;
      virtual void unpackUpdate( SceneObject* obj, NetConnection* conn, BitStream* stream ) = 0;     
};

#endif // !_SCENEOBJECTLIGHTINGPLUGIN_H_
