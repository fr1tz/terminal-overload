// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PARTICLEEMITTERDUMMY_H_
#define _PARTICLEEMITTERDUMMY_H_

#ifndef _GAMEBASE_H_
#include "T3D/gameBase/gameBase.h"
#endif

class ParticleEmitterData;
class ParticleEmitter;

//*****************************************************************************
// ParticleEmitterNodeData
//*****************************************************************************
class ParticleEmitterNodeData : public GameBaseData
{
   typedef GameBaseData Parent;

  protected:
   bool onAdd();

   //-------------------------------------- Console set variables
  public:
   F32 timeMultiple;

   //-------------------------------------- load set variables
  public:

  public:
   ParticleEmitterNodeData();
   ~ParticleEmitterNodeData();

   void packData(BitStream*);
   void unpackData(BitStream*);
   bool preload(bool server, String &errorStr);

   DECLARE_CONOBJECT(ParticleEmitterNodeData);
   static void initPersistFields();
};


//*****************************************************************************
// ParticleEmitterNode
//*****************************************************************************
class ParticleEmitterNode : public GameBase
{
   typedef GameBase Parent;

   enum MaskBits
   {
      StateMask      = Parent::NextFreeMask << 0,
      EmitterDBMask  = Parent::NextFreeMask << 1,
      NextFreeMask   = Parent::NextFreeMask << 2,
   };

  private:
   ParticleEmitterNodeData* mDataBlock;

  protected:
   bool onAdd();
   void onRemove();
   bool onNewDataBlock( GameBaseData *dptr, bool reload );
   void inspectPostApply();

   ParticleEmitterData* mEmitterDatablock;
   S32                  mEmitterDatablockId;

   bool             mActive;

   SimObjectPtr<ParticleEmitter> mEmitter;
   F32              mVelocity;

  public:
   ParticleEmitterNode();
   ~ParticleEmitterNode();
   
   ParticleEmitter *getParticleEmitter() {return mEmitter;}
   
   // Time/Move Management
  public:
   void processTick(const Move* move);
   void advanceTime(F32 dt);

   DECLARE_CONOBJECT(ParticleEmitterNode);
   static void initPersistFields();

   U32  packUpdate  (NetConnection *conn, U32 mask, BitStream* stream);
   void unpackUpdate(NetConnection *conn,           BitStream* stream);

   inline bool getActive( void )        { return mActive;                             };
   inline void setActive( bool active ) { mActive = active; setMaskBits( StateMask ); };

   void setEmitterDataBlock(ParticleEmitterData* data);
};

#endif // _H_PARTICLEEMISSIONDUMMY

