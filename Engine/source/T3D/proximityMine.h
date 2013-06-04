// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PROXIMITYMINE_H_
#define _PROXIMITYMINE_H_

#ifndef _ITEM_H_
   #include "T3D/item.h"
#endif

class ExplosionData;
class SFXTrack;
class ProximityMine;

//----------------------------------------------------------------------------

struct ProximityMineData: public ItemData
{
   typedef ItemData Parent;

   DECLARE_CALLBACK( void, onTriggered, ( ProximityMine* obj, SceneObject* target ) );
   DECLARE_CALLBACK( void, onExplode, ( ProximityMine* obj, Point3F pos ) );

public:
   F32               armingDelay;
   S32               armingSequence;
   SFXTrack*         armingSound;

   F32               autoTriggerDelay;
   bool              triggerOnOwner;
   F32               triggerRadius;
   F32               triggerSpeed;
   F32               triggerDelay;
   S32               triggerSequence;
   SFXTrack*         triggerSound;

   F32               explosionOffset;

   ProximityMineData();
   DECLARE_CONOBJECT( ProximityMineData );
   static void initPersistFields();
   bool preload( bool server, String& errorStr );
   virtual void packData( BitStream* stream );
   virtual void unpackData( BitStream* stream );
};

//----------------------------------------------------------------------------

class ProximityMine: public Item
{
   typedef Item Parent;

protected:
   enum MaskBits {
      DeployedMask   = Parent::NextFreeMask,
      ExplosionMask  = Parent::NextFreeMask << 1,
      NextFreeMask   = Parent::NextFreeMask << 2
   };

   enum State
   {
      Thrown = 0,       //!< Mine has been thrown, but not yet attached to a surface
      Deployed,         //!< Mine has attached to a surface but is not yet armed
      Armed,            //!< Mine is armed and will trigger if any object enters the trigger area
      Triggered,        //!< Mine has been triggered and will explode soon
      Exploded,         //!< Mine has exploded and will be deleted on the server shortly
      NumStates
   };

   ProximityMineData*   mDataBlock;

   TSThread*            mAnimThread;
   SceneObject*         mOwner;

   State                mState;
   F32                  mStateTimeout;

   void setDeployedPos( const Point3F& pos, const Point3F& normal );

   void prepRenderImage( SceneRenderState* state );
   void renderObject( ObjectRenderInst* ri, SceneRenderState* state, BaseMatInstance* overrideMat );

public:
   DECLARE_CONOBJECT( ProximityMine );

   ProximityMine();
   ~ProximityMine();

   static void consoleInit();

   bool onAdd();
   void onRemove();
   bool onNewDataBlock( GameBaseData* dptr, bool reload );

   virtual void setTransform( const MatrixF& mat );
   void processTick( const Move* move );
   void explode();

   void advanceTime( F32 dt );

   U32  packUpdate  ( NetConnection* conn, U32 mask, BitStream* stream );
   void unpackUpdate( NetConnection* conn, BitStream* stream );
};

#endif // _PROXIMITYMINE_H_
