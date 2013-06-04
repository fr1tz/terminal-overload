// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FORESTWINDMGR_H_
#define _FORESTWINDMGR_H_

#ifndef _FORESTWINDEMITTER_H_
#include "forest/forestWindEmitter.h"
#endif
#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif
#ifndef _ITICKABLE_H_
#include "core/iTickable.h"
#endif
#ifndef _FORESTITEM_H_
#include "forest/forestItem.h"
#endif 
#ifndef _TSINGLETON_H_
#include "core/util/tSingleton.h"
#endif

struct TreePlacementInfo
{
   F32 scale;
   Point3F pos;
   ForestItemKey itemKey; 
   ForestItemData *dataBlock;
}; 

class ForestWindMgr : public virtual ITickable
{
protected:

   ForestWindEmitterList mEmitters;

   typedef HashTable<U32,ForestWindAccumulator*> IdToWindMap;
   typedef Signal<void( const Point3F &camPos, const F32 radius, Vector<TreePlacementInfo> *placementInfo )> WindAdvanceSignal;

   IdToWindMap *mSources;
   IdToWindMap *mPrevSources;
   Vector<TreePlacementInfo> mPlacementInfo;

   static WindAdvanceSignal smAdvanceSignal;

   virtual void interpolateTick( F32 delta ) {};
   virtual void processTick();
   virtual void advanceTime( F32 timeDelta ) {};   

public:

   ForestWindMgr();
   virtual ~ForestWindMgr();

   void addEmitter( ForestWindEmitter *emitter );

   void removeEmitter( ForestWindEmitter *emitter );

   void updateWind(  const Point3F &camPos, 
                     const TreePlacementInfo &info,
                     F32 timeDelta );

   ForestWindAccumulator* getLocalWind( ForestItemKey key );

   // Returns the first non-radial emitter in the list.
   ForestWindEmitter* getGlobalWind();


   static WindAdvanceSignal& getAdvanceSignal() { return smAdvanceSignal; }

   static F32 smWindEffectRadius;

   static void initConsole();

   // For ManagedSingleton.
   static const char* getSingletonName() { return "ForestWindMgr"; }    
};

/// Returns the ReflectionManager singleton.
#define WINDMGR ManagedSingleton<ForestWindMgr>::instance()

#endif // _FORESTWINDMGR_H_