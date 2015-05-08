// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MOVELIST_H_
#define _MOVELIST_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _MOVEMANAGER_H_
#include "T3D/gameBase/moveManager.h"
#endif

class BitStream;
class ResizeBitStream;
class NetObject;
class GameConnection;
class PlayerRep;
class ProcessList;

class MoveList
{
public:

   MoveList();
   virtual ~MoveList() {}
   
   virtual void init() {}

   void setConnection( GameConnection *connection) { mConnection = connection; }

   /// @name Move Packets
   /// Write/read move data to the packet.
   /// @{

   virtual void ghostReadExtra( NetObject *, BitStream *, bool newGhost) {};
   virtual void ghostWriteExtra( NetObject *,BitStream * ) {};
   virtual void ghostPreRead( NetObject *, bool newGhost ) {};

   virtual void clientWriteMovePacket( BitStream *bstream ) = 0;
   virtual void clientReadMovePacket( BitStream * ) = 0;

   virtual void serverWriteMovePacket( BitStream * ) = 0;
   virtual void serverReadMovePacket( BitStream *bstream ) = 0;

   virtual void writeDemoStartBlock( ResizeBitStream *stream );
   virtual void readDemoStartBlock( BitStream *stream );
   /// @}

   virtual void advanceMove() = 0;
   virtual void onAdvanceObjects() = 0;
   virtual U32 getMoves( Move**, U32 *numMoves );

   /// Reset to beginning of client move list.
   void resetClientMoves() { mLastClientMove = mFirstMoveIndex; }

   /// Reset move list back to last acknowledged move.
   void resetCatchup() { mLastClientMove = mLastMoveAck; }

   virtual void collectMove();
   virtual void pushMove( const Move &mv );
   virtual void clearMoves( U32 count );

   virtual void markControlDirty() { mLastClientMove = mLastMoveAck; }
   bool isMismatch() { return mControlMismatch; }
   void clearMismatch() { mControlMismatch = false; }
   
   /// Clear out all moves in the list and reset to initial state.
   virtual void reset();

   /// If there are no pending moves and the input queue is full,
   /// then the connection to the server must be clogged.
   virtual bool isBacklogged();

   virtual bool areMovesPending();

   virtual void ackMoves( U32 count );

   U32 getLastMoveAck() const { return mLastMoveAck; }
   U32 getLastClientMove() const { return mLastClientMove; }
   U32 getFirstMoveIndex() const { return mFirstMoveIndex; }
   U32 getMoveVecSize() const { return mMoveVec.size(); }

protected:

   bool getNextMove( Move &curMove );

protected:

   enum 
   {
      MoveCountBits = 5,
      /// MaxMoveCount should not exceed the MoveManager's
      /// own maximum (MaxMoveQueueSize)
      MaxMoveCount = 30,
   };

   U32 mLastMoveAck;
   U32 mLastClientMove;
   U32 mFirstMoveIndex;
   bool mControlMismatch;

   GameConnection *mConnection;

   Vector<Move> mMoveVec;
};

#endif // _MOVELIST_H_
