// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BASICSCENEOBJECTLIGHTINGPLUGIN_H_
#define _BASICSCENEOBJECTLIGHTINGPLUGIN_H_

#ifndef _SCENEOBJECTLIGHTINGPLUGIN_H_
#include "scene/sceneObjectLightingPlugin.h"
#endif

#ifndef _SCENEOBJECT_H_
#include "scene/sceneObject.h"
#endif

#ifndef _TSINGLETON_H_
#include "core/util/tSingleton.h"
#endif


class ShadowBase;

class BasicSceneObjectLightingPlugin : public SceneObjectLightingPlugin
{
private:

   ShadowBase* mShadow;
   SceneObject* mParentObject;

   static Vector<BasicSceneObjectLightingPlugin*> smPluginInstances;
   
public:
   BasicSceneObjectLightingPlugin(SceneObject* parent);
   ~BasicSceneObjectLightingPlugin();

   static Vector<BasicSceneObjectLightingPlugin*>* getPluginInstances() { return &smPluginInstances; }

   static void cleanupPluginInstances();
   static void resetAll();

   const F32 getScore() const;

   // Called from BasicLightManager
   virtual void updateShadow( SceneRenderState *state );
   virtual void renderShadow( SceneRenderState *state );

   // Called by statics
   virtual U32  packUpdate(SceneObject* obj, U32 checkMask, NetConnection *conn, U32 mask, BitStream *stream) { return 0; }
   virtual void unpackUpdate(SceneObject* obj, NetConnection *conn, BitStream *stream) { }

   virtual void reset();
};

class BasicSceneObjectPluginFactory : public ManagedSingleton< BasicSceneObjectPluginFactory >
{
protected:

   /// Called from the light manager on activation.
   /// @see LightManager::addActivateCallback
   void _onLMActivate( const char *lm, bool enable );   
   
   void _onDecalManagerClear();

   void removeLightPlugin(SceneObject* obj);
   void addLightPlugin(SceneObject* obj);
   void addToExistingObjects();

   bool mEnabled;

public:

   BasicSceneObjectPluginFactory();
   ~BasicSceneObjectPluginFactory();
   
   // For ManagedSingleton.
   static const char* getSingletonName() { return "BasicSceneObjectPluginFactory"; }
   
   void _setEnabled();
};

#endif // !_BASICSCENEOBJECTLIGHTINGPLUGIN_H_
