// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BLTERRAINSYSTEM_H_
#define _BLTERRAINSYSTEM_H_

#ifndef _SCENELIGHTING_H_
   #include "lighting/common/sceneLighting.h"
#endif
#ifndef _SG_SYSTEM_INTERFACE_H
   #include "lighting/lightingInterfaces.h"
#endif

//
// Lighting system interface
//
class blTerrainSystem : public SceneLightingInterface
{
public:
   virtual void init();
   virtual U32 addObjectType();
   virtual SceneLighting::ObjectProxy* createObjectProxy(SceneObject* obj, SceneLighting::ObjectProxyList* sceneObjects);
   virtual PersistInfo::PersistChunk* createPersistChunk(const U32 chunkType);
   virtual bool createPersistChunkFromProxy(SceneLighting::ObjectProxy* objproxy, PersistInfo::PersistChunk **ret);      

   // Given a ray, this will return the color from the lightmap of this object, return true if handled
   virtual bool getColorFromRayInfo(const RayInfo & collision, ColorF& result) const;
};

#endif // !_BLTERRAINSYSTEM_H_
