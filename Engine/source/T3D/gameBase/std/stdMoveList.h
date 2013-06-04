// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MOVELIST_STD_H_
#define _MOVELIST_STD_H_

#ifndef _MOVELIST_H_
#include "T3D/gameBase/moveList.h"
#endif

class StdMoveList : public MoveList
{
   typedef MoveList Parent;

public:

   StdMoveList();

   void clientWriteMovePacket(BitStream *);
   void clientReadMovePacket(BitStream *);

   void serverWriteMovePacket(BitStream *);
   void serverReadMovePacket(BitStream *);

   U32 getMoves(Move**,U32* numMoves);
   void clearMoves(U32 count);

   void advanceMove();
   void onAdvanceObjects() {}

protected:

   U32 mMoveCredit;
};

#endif // _MOVELIST_STD_H_
