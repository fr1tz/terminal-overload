// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MOVELIST_HIFI_H_
#define _MOVELIST_HIFI_H_

#ifndef _MOVELIST_H_
#include "T3D/gameBase/moveList.h"
#endif

class HifiMoveList : public MoveList
{
   typedef MoveList Parent;

public:

   HifiMoveList();

   void init() { mTotalServerTicks = ServerTicksUninitialized; }

   void ghostReadExtra(NetObject *,BitStream *, bool newGhost);
   void ghostPreRead(NetObject *, bool newGhost);

   void clientWriteMovePacket(BitStream *bstream);
   void clientReadMovePacket(BitStream *);
   void serverWriteMovePacket(BitStream *);
   void serverReadMovePacket(BitStream *bstream);

   void markControlDirty();
   U32 getMoves(Move**,U32* numMoves);
   void onAdvanceObjects() { if (mMoveVec.size() > mLastSentMove-mFirstMoveIndex) mLastSentMove++; }

   void advanceMove();

protected:
   void resetMoveList();
   S32 getServerTicks(U32 serverTickNum);
   void updateClientServerTickDiff(S32 & tickDiff);
   bool serverTicksInitialized() { return mTotalServerTicks!=ServerTicksUninitialized; }

protected:
   U32 mLastSentMove;
   F32 mAvgMoveQueueSize;

   // server side move list management
   U32 mTargetMoveListSize;       // Target size of move buffer on server
   U32 mMaxMoveListSize;          // Max size move buffer allowed to grow to
   F32 mSmoothMoveAvg;            // Smoothing parameter for move list size running average
   F32 mMoveListSizeSlack;        // Amount above/below target size move list running average allowed to diverge
   bool mSuppressMove;            // If true, don't return move on server

   // client side tracking of server ticks
   enum { TotalTicksBits=10, TotalTicksMask = (1<<TotalTicksBits)-1, ServerTicksUninitialized=0xFFFFFFFF };
   U32 mTotalServerTicks;
};

#endif // _MOVELIST_HIFI_H_
