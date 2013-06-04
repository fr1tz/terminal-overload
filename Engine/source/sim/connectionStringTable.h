// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _H_CONNECTIONSTRINGTABLE
#define _H_CONNECTIONSTRINGTABLE

/// Maintain a table of strings which are shared across the network.
///
/// This allows us to reference strings in our network streams more efficiently.
class ConnectionStringTable
{
public:
   enum Constants {
      EntryCount = 32,
      EntryBitSize = 5,
      InvalidEntryId = 32,
   };
private:
   struct Entry {
      NetStringHandle string;   ///< Global string table entry of this string
                             ///  will be 0 if this string is unused.

      U32 index;             ///< index of this entry
      Entry *nextHash;       ///< the next hash entry for this id
      Entry *nextLink;       ///< the next in the LRU list
      Entry *prevLink;       ///< the prev entry in the LRU list
      bool receiveConfirmed; ///< The other side now has this string.
   };

   Entry mEntryTable[EntryCount];
   Entry *mHashTable[EntryCount];
   NetStringHandle mRemoteStringTable[EntryCount];
   Entry mLRUHead, mLRUTail;

   /// Connection over which we are maintaining this string table.
   NetConnection *mParent;

   inline void pushBack(Entry *entry) // pushes an entry to the back of the LRU list
   {
      entry->prevLink->nextLink = entry->nextLink;
      entry->nextLink->prevLink = entry->prevLink;
      entry->nextLink = &mLRUTail;
      entry->prevLink = mLRUTail.prevLink;
      entry->nextLink->prevLink = entry;
      entry->prevLink->nextLink = entry;
   }

public:
   /// Initialize the connection string table.
   ///
   /// @param  parent   Connection over which we are maintaining this string table.
   ConnectionStringTable(NetConnection *parent);

   /// Has the specified string been received on the other side?
   inline void confirmStringReceived(NetStringHandle &string, U32 index)
   {
      if(mEntryTable[index].string == string)
         mEntryTable[index].receiveConfirmed = true;
   }

   U32 checkString(NetStringHandle &stringTableId, bool *stringOnOtherSide = NULL);  ///< Checks if the global string ID is
                                                                                  ///  currently valid for this connection
                                                                                  ///  and returns the table ID.
                                                                                  ///  Sends a string event to the other side
                                                                                  ///  if it is not active.
                                                                                  ///  It will fill in stringOnOtherSide.

   U32 getNetSendId(NetStringHandle &stringTableId); ///< Same return value as checkString
                                                  ///  but will assert if the string is not
                                                  ///  valid.

   void mapString(U32 netId, NetStringHandle &string); ///< Maps a string that
                                                    ///  was just sent over the net
                                                    ///  to the corresponding net ID.

   inline NetStringHandle lookupString(U32 netId) ///< looks up the string ID and returns
   {                                           /// the global string table ID for that string.
      return mRemoteStringTable[netId];
   }

   /// @name Demo functionality
   /// @{

   void readDemoStartBlock(BitStream *stream);
   void writeDemoStartBlock(ResizeBitStream *stream);
   /// @}
};

#endif

