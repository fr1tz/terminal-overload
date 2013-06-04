// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _SG_SYSTEM_INTERFACE_H
#define _SG_SYSTEM_INTERFACE_H

#ifndef _SGSCENEPERSIST_H_
#include "lighting/common/scenePersist.h"
#endif

#ifndef _SCENELIGHTING_H_
#include "lighting/common/sceneLighting.h"
#endif

class ObjectProxy;
class ObjectProxyList;
class SceneLightingInterface;

template <class T> class Vector;
typedef Vector<SceneLightingInterface*> SceneLightingInterfaces; 

// List of available "systems" that the lighting kit can use
class AvailableSLInterfaces
{
protected:

   bool mDirty;
   
public:
   AvailableSLInterfaces()
      :  mAvailableObjectTypes( 0 ),
         mClippingMask( 0 ),
         mZoneLightSkipMask( 0 ),
         mDirty( true )
   {
      VECTOR_SET_ASSOCIATION( mAvailableSystemInterfaces );      
   }
      
   // Register a system 
   void registerSystem(SceneLightingInterface* si);

   // Init the interfaces
   void initInterfaces();
   
   // The actual list of SceneLightingInterfaces
   SceneLightingInterfaces mAvailableSystemInterfaces;  

   // Object types that are registered with the system
   U32 mAvailableObjectTypes;

   // Clipping typemask
   U32 mClippingMask;

   // Object types that we should skip zone lighting for
   U32 mZoneLightSkipMask;
};

// This object is responsible for returning PersistChunk and ObjectProxy classes for the lighting system to use
// We may want to eventually split this into scene lighting vs. dynamic lighting.  getColorFromRayInfo is a dynamic
// lighting thing.
class SceneLightingInterface
{
public:
   SceneLightingInterface()
   {
   }
   virtual ~SceneLightingInterface() { }

   virtual void init() { }

   //
   // Scene lighting methods
   //
   // Creates an object proxy for obj
   virtual SceneLighting::ObjectProxy* createObjectProxy(SceneObject* obj, SceneLighting::ObjectProxyList* sceneObjects) = 0;

   // Creates a PersistChunk based on the chunkType flag
   virtual PersistInfo::PersistChunk* createPersistChunk(const U32 chunkType) = 0;

   // Creates a PersistChunk if needed for a proxy, returns true if it's "handled" by the system and ret contains the PersistChunk if needed.
   virtual bool createPersistChunkFromProxy(SceneLighting::ObjectProxy* proxy, PersistInfo::PersistChunk** ret) = 0;

   // Returns which object type flag this system supports (used to query scene graph for objects to light)
   virtual U32 addObjectType() = 0;

   // Add an object type flag to the "allow clipping mask" (used for blob shadows)
   virtual U32 addToClippingMask() { return 0; }

   // Add an object type flag to skip zone lighting
   virtual U32 addToZoneLightSkipMask() { return 0; }

   // Allows for processing/validating of the scene list after loading cached persistant info, return false if a relight is required or true if the data looks good.
   virtual bool postProcessLoad(PersistInfo* pi, SceneLighting::ObjectProxyList* sceneObjects) { return true; }
   
   virtual void processLightingBegin() { }
   virtual void processLightingCompleted(bool success) { }

   //
   // Runtime / dynamic methods
   //
   // Given a ray, this will return the color from the lightmap of this object, return true if handled
   virtual bool getColorFromRayInfo(const RayInfo & collision, ColorF& result) const { return false; }
};

#endif
