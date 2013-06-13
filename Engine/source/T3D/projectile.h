// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif
#ifndef __RESOURCE_H__
#include "core/resource.h"
#endif
#ifndef _TSSHAPE_H_
#include "ts/tsShape.h"
#endif
#ifndef _LIGHTDESCRIPTION_H_
#include "T3D/lightDescription.h"
#endif
#ifndef _LIGHTINFO_H_
#include "lighting/lightInfo.h"
#endif


class ExplosionData;
class SplashData;
class ShapeBase;
class TSShapeInstance;
class TSThread;
class PhysicsWorld;
class DecalData;
class LightDescription;
class SFXTrack;
class SFXSource;
class ParticleEmitterData;
class ParticleEmitter;
class Projectile;

//--------------------------------------------------------------------------
/// Datablock for projectiles.  This class is the base class for all other projectiles.
class ProjectileData : public GameBaseData
{
   typedef GameBaseData Parent;

protected:
   bool onAdd();

public:
   // variables set in datablock definition:
   // Shape related
   const char* projectileShapeName;

   /// Set to true if it is a billboard and want it to always face the viewer, false otherwise
   bool faceViewer;
   Point3F scale;


   /// [0,1] scale of how much velocity should be inherited from the parent object
   F32 velInheritFactor;
   /// Speed of the projectile when fired
   F32 muzzleVelocity;

   /// Force imparted on a hit object.
   F32 impactForce;

   /// Should it arc?
   bool isBallistic;

   /// How HIGH should it bounce (parallel to normal), [0,1]
   F32 bounceElasticity;
   /// How much momentum should be lost when it bounces (perpendicular to normal), [0,1]
   F32 bounceFriction;

   /// Should this projectile fall/rise different than a default object?
   F32 gravityMod;

   /// How long the projectile should exist before deleting itself
   U32 lifetime;     // all times are internally represented as ticks
   /// How long it should not detonate on impact
   S32 armingDelay;  // the values are converted on initialization with
   S32 fadeDelay;    // the IRangeValidatorScaled field validator

   ExplosionData* explosion;
   S32 explosionId;

   ExplosionData* waterExplosion;      // Water Explosion Datablock
   S32 waterExplosionId;               // Water Explosion ID

   SplashData* splash;                 // Water Splash Datablock
   S32 splashId;                       // Water splash ID

   DecalData *decal;                   // (impact) Decal Datablock
   S32 decalId;                        // (impact) Decal ID

   SFXTrack* sound;                    // Projectile Sound
   
   LightDescription *lightDesc;
   S32 lightDescId;   

   // variables set on preload:
   Resource<TSShape> projectileShape;
   S32 activateSeq;
   S32 maintainSeq;

   ParticleEmitterData* particleEmitter;
   S32 particleEmitterId;

   ParticleEmitterData* particleWaterEmitter;
   S32 particleWaterEmitterId;

   ProjectileData();

   void packData(BitStream*);
   void unpackData(BitStream*);
   bool preload(bool server, String &errorStr);

   static bool setLifetime( void *object, const char *index, const char *data );
   static bool setArmingDelay( void *object, const char *index, const char *data );
   static bool setFadeDelay( void *object, const char *index, const char *data );
   static const char *getScaledValue( void *obj, const char *data);
   static S32 scaleValue( S32 value, bool down = true );

   static void initPersistFields();
   DECLARE_CONOBJECT(ProjectileData);

   
   DECLARE_CALLBACK( void, onExplode, ( Projectile* proj, Point3F pos, F32 fade ) );
   DECLARE_CALLBACK( void, onCollision, ( Projectile* proj, SceneObject* col, F32 fade, Point3F pos, Point3F normal ) );
};


//--------------------------------------------------------------------------
/// Base class for all projectiles.
class Projectile : public GameBase, public ISceneLight
{
   typedef GameBase Parent;

   static bool _setInitialPosition( void* object, const char* index, const char* data );
   static bool _setInitialVelocity( void* object, const char* index, const char* data );

public:

   // Initial conditions
   enum ProjectileConstants {
      SourceIdTimeoutTicks = 7,   // = 231 ms
      DeleteWaitTime       = 500, ///< 500 ms delete timeout (for network transmission delays)
      ExcessVelDirBits     = 7,
      MaxLivingTicks       = 4095,
   };
   enum UpdateMasks {
      BounceMask    = Parent::NextFreeMask,
      ExplosionMask = Parent::NextFreeMask << 1,
      NextFreeMask  = Parent::NextFreeMask << 2
   };

   
   Projectile();
   ~Projectile();

   DECLARE_CONOBJECT(Projectile);

   // SimObject
   bool onAdd();
   void onRemove();
   static void initPersistFields();

   // NetObject
   F32 getUpdatePriority(CameraScopeQuery *focusObject, U32 updateMask, S32 updateSkips);
   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream *stream);
   void unpackUpdate(NetConnection *conn,           BitStream *stream);

   // SceneObject
   Point3F getVelocity() const { return mCurrVelocity; }
   void processTick( const Move *move );   
   void advanceTime( F32 dt );
   void interpolateTick( F32 delta );   

   // GameBase
   bool onNewDataBlock( GameBaseData *dptr, bool reload );      

   // Rendering
   void prepRenderImage( SceneRenderState *state );
   void prepBatchRender( SceneRenderState *state );   

   /// Updates velocity and position, and performs collision testing.
   void simulate( F32 dt );

   /// What to do once this projectile collides with something
   virtual void onCollision(const Point3F& p, const Point3F& n, SceneObject*);

   /// What to do when this projectile explodes
   virtual void explode(const Point3F& p, const Point3F& n, const U32 collideType );
      
   bool pointInWater(const Point3F &point);

   void emitParticles(const Point3F&, const Point3F&, const Point3F&, const U32);

   void updateSound();    

   virtual bool calculateImpact( float simTime,
                                 Point3F &pointOfImpact,
                                 float &impactTime );

   void setInitialPosition( const Point3F& pos );
   void setInitialVelocity( const Point3F& vel );

public:
   Point3F  mCurrPosition;
   Point3F  mCurrVelocity;

	SimObjectPtr<ShapeBase> mSourceObject; ///< Actual pointer to the source object
	                                       ///  (never times out for Alux3D)

   S32      mSourceObjectId;
   S32      mSourceObjectSlot;

protected:

   static const U32 csmStaticCollisionMask;
   static const U32 csmDynamicCollisionMask;
   static const U32 csmDamageableMask;   
   static U32 smProjectileWarpTicks;

   PhysicsWorld *mPhysicsWorld;

   ProjectileData* mDataBlock;

   SimObjectPtr< ParticleEmitter > mParticleEmitter;
   SimObjectPtr< ParticleEmitter > mParticleWaterEmitter;

   SFXSource* mSound;

   Point3F  mInitialPosition;
   Point3F  mInitialVelocity;

   // Time related variables common to all projectiles, managed by processTick
   U32 mCurrTick;                         ///< Current time in ticks


   // Rendering related variables
   TSShapeInstance* mProjectileShape;
   TSThread*        mActivateThread;
   TSThread*        mMaintainThread;

   // ISceneLight
   virtual void submitLights( LightManager *lm, bool staticLighting );
   virtual LightInfo* getLight() { return mLight; }
   
   LightInfo *mLight;
   LightState mLightState;   

   bool             mHasExploded;   ///< Prevent rendering, lighting, and duplicate explosions.
   F32              mFadeValue;     ///< set in processTick, interpolation between fadeDelay and lifetime
                                    ///< in data block

   // Warping and back delta variables.  Only valid on the client
   //
   Point3F mWarpStart;
   Point3F mWarpEnd;
   U32     mWarpTicksRemaining;

   Point3F mCurrDeltaBase;
   Point3F mCurrBackDelta;

   Point3F mExplosionPosition;
   Point3F mExplosionNormal;
   U32     mCollideHitType;   
};

#endif // _PROJECTILE_H_

