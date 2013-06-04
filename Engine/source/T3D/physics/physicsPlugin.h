// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _T3D_PHYSICS_PHYSICSPLUGIN_H_
#define _T3D_PHYSICS_PHYSICSPLUGIN_H_

#ifndef _SIMSET_H_
#include "console/simSet.h"
#endif
#ifndef _TSIGNAL_H_
#include "core/util/tSignal.h"
#endif
#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _UTIL_DELEGATE_H_
#include "core/util/delegate.h"
#endif
#ifndef _T3D_PHYSICSCOMMON_H_
#include "T3D/physics/physicsCommon.h"
#endif


class Player;
class SceneRenderState;
class SceneManager;
class SceneObject;
class PhysicsObject;
class PhysicsBody;
class PhysicsWorld;
class PhysicsPlayer;
class PhysicsCollision;


typedef Delegate<PhysicsObject*( const SceneObject *)> CreatePhysicsObjectFn; 
typedef Map<StringNoCase, CreatePhysicsObjectFn> CreateFnMap;


///
class PhysicsPlugin
{

protected:

   /// The current active physics plugin.
   static PhysicsPlugin* smSingleton;

   static PhysicsResetSignal smPhysicsResetSignal;

   // Our map of Strings to PhysicsWorld pointers.
   Map<StringNoCase, PhysicsWorld*> mPhysicsWorldLookup;

   static String smServerWorldName;
   static String smClientWorldName;

   /// A SimSet of objects to delete before the
   /// physics reset/restore event occurs.
   SimObjectPtr<SimSet> mPhysicsCleanup;      

   /// Delegate method for debug drawing.
   static void _debugDraw( SceneManager *graph, const SceneRenderState *state );

public:

   /// Note this should go away when we have "real" singleplayer.
   static bool smSinglePlayer;
   static bool isSinglePlayer() { return smSinglePlayer; }
   
   /// Number of threads to use if supported by the plugin.
   static U32 smThreadCount;
   static U32 getThreadCount() { return smThreadCount; }

   /// Returns the active physics plugin.
   /// @see PHYSICSPLUGIN
   static PhysicsPlugin* getSingleton() { return smSingleton; }

   ///
   static bool activate( const char *library );

   PhysicsPlugin();
   virtual ~PhysicsPlugin();

   /// Cleans up, deactivates, and deletes the plugin.
   virtual void destroyPlugin() = 0;

   virtual void reset() = 0;

   /// Returns the physics cleanup set.
   SimSet* getPhysicsCleanup() const { return mPhysicsCleanup; }      

   void enableDebugDraw( bool enabled );

   virtual PhysicsCollision* createCollision() = 0;

   virtual PhysicsBody* createBody() = 0;

   virtual PhysicsPlayer* createPlayer() = 0;

   virtual bool isSimulationEnabled() const = 0;
   virtual void enableSimulation( const String &worldName, bool enable ) = 0;

   virtual void setTimeScale( const F32 timeScale ) = 0;
   virtual const F32 getTimeScale() const = 0;

   static PhysicsResetSignal& getPhysicsResetSignal() { return smPhysicsResetSignal; } 

   virtual bool createWorld( const String &worldName ) = 0;
   virtual void destroyWorld( const String &worldName ) = 0;

   virtual PhysicsWorld* getWorld( const String &worldName ) const = 0;

protected:

   /// Overload this to toggle any physics engine specific stuff
   /// when debug rendering is enabled or disabled.
   virtual void _onDebugDrawEnabled( bool enabled ) {}

};

/// Helper macro for accessing the physics plugin.  It will
/// return NULL if no plugin is initialized.
/// @see PhysicsPlugin
#define PHYSICSMGR PhysicsPlugin::getSingleton()

#endif // _T3D_PHYSICS_PHYSICSPLUGIN_H_