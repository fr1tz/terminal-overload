// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _NODELISTMANAGER_H_
#define _NODELISTMANAGER_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif
#ifndef _MQUAT_H_
#include "math/mQuat.h"
#endif
#ifndef _NETCONNECTION_H_
#include "sim/netConnection.h"
#endif

//-----------------------------------------------------------------------------

class NodeListNotify;

class NodeListManager
{
public:
   
   struct NodeList
   {
      U32   mId;
      U32   mTotalValidNodes;
      bool  mListComplete;

      NodeList() { mTotalValidNodes=0; mListComplete=false; }
      virtual ~NodeList() { }
   };

   static U32 smMaximumNodesPerEvent;

protected:
   bool  mIsServer;
   U32   mNextListId;

   Vector<NodeList*>       mNodeLists;
   Vector<NodeListNotify*> mNotifyList;

public:
   NodeListManager( const bool isServer );
   ~NodeListManager();

   void clearNodeLists();

   U32 nextListId();

   void addNodeList( NodeList* list );

   bool findListById( U32 id, NodeList** list, bool completeOnly=true );

   void clearNotification( U32 listId );
   void clearAllNotifications();
   void registerNotification( NodeListNotify* notify );
   bool dispatchNotification( U32 listId );
   bool dispatchNotification( NodeList* list );
};

extern NodeListManager* gClientNodeListManager;
extern NodeListManager* gServerNodeListManager;

//-----------------------------------------------------------------------------

class NodeListNotify
{
protected:
   U32  mListId;

public:
   NodeListNotify() { }
   virtual ~NodeListNotify() { }

   U32 getListId() { return mListId; }

   virtual void sendNotification( NodeListManager::NodeList* list ) { }
};

//-----------------------------------------------------------------------------

class NodeListEvent : public NetEvent
{
   typedef NetEvent Parent;

public:
   U32         mId;
   U32         mTotalNodes;
   U32         mLocalListStart;

   NodeListManager::NodeList* mNodeList;

public:
   NodeListEvent() { mNodeList=NULL; mTotalNodes = mLocalListStart = 0; }
   virtual ~NodeListEvent();

   virtual void pack(NetConnection*, BitStream*);
   virtual void write(NetConnection*, BitStream*);
   virtual void unpack(NetConnection*, BitStream*);
   virtual void process(NetConnection*);
   virtual void mergeLists(NodeListManager::NodeList* oldList);

   virtual void copyIntoList(NodeListManager::NodeList* copyInto) { }
   virtual void padListToSize() { }

   DECLARE_CONOBJECT(NodeListEvent);
};

#endif   // _NODELISTMANAGER_H_
