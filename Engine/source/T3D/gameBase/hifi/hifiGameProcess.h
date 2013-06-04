// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GAMEPROCESS_HIFI_H_
#define _GAMEPROCESS_HIFI_H_

#ifndef _GAMEPROCESS_H_
#include "T3D/gameBase/gameProcess.h"
#endif


/// List to keep track of GameBases to process.
class HifiClientProcessList : public ClientProcessList
{
   typedef ClientProcessList Parent;
   friend class HifiMoveList;

public:

   HifiClientProcessList();

   // ProcessList
   bool advanceTime(SimTime timeDelta);

   // ClientProcessList
   void clientCatchup(GameConnection*);

   static void init();
   static void shutdown();

protected:

   // tick cache functions -- client only
   void ageTickCache(S32 numToAge, S32 len);
   void forceHifiReset(bool reset) { mForceHifiReset=reset; }
   U32 getTotalTicks() { return mTotalTicks; }
   void updateMoveSync(S32 moveDiff);
   void skipAdvanceObjects(U32 ms) { mSkipAdvanceObjectsMs += ms; }

   // ProcessList
   void onTickObject(ProcessObject *);
   void advanceObjects();
   void onAdvanceObjects();

   void setCatchup(U32 catchup) { mCatchup = catchup; }

protected:

   U32 mSkipAdvanceObjectsMs;
   bool mForceHifiReset;
   U32 mCatchup;
};


class HifiServerProcessList : public ServerProcessList
{
   typedef ServerProcessList Parent;

public:

   HifiServerProcessList() {}

   static void init();
   static void shutdown();

protected:

   // ProcessList
   void onTickObject(ProcessObject *);
};

#endif // _GAMEPROCESS_HIFI_H_