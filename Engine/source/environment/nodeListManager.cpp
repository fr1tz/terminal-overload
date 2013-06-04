// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "environment/nodeListManager.h"
#include "core/module.h"
#include "core/stream/bitStream.h"

MODULE_BEGIN( NodeListManager )

   MODULE_INIT
   {
      AssertFatal(gClientNodeListManager == NULL && gServerNodeListManager == NULL, "Error, already initialized the node list manager!");

      gClientNodeListManager = new NodeListManager(false);
      gServerNodeListManager = new NodeListManager(true);
   }

   MODULE_SHUTDOWN
   {
      AssertFatal(gClientNodeListManager != NULL && gServerNodeListManager != NULL, "Error, node list manager not initialized!");

      delete gClientNodeListManager;
      gClientNodeListManager = NULL;
      delete gServerNodeListManager;
      gServerNodeListManager = NULL;
   }

MODULE_END;

//-----------------------------------------------------------------------------
// NodeListEvent Class
//-----------------------------------------------------------------------------

NodeListEvent::~NodeListEvent()
{
   if (mNodeList)
   {
      // This means the node list wasn't processed
      delete mNodeList;
   }
}

void NodeListEvent::pack(NetConnection* conn, BitStream* stream)
{
   stream->write(mId);
   stream->write(mTotalNodes);
   stream->write(mLocalListStart);

   // NOTE: Child class needs to transmit the nodes
}

void NodeListEvent::write(NetConnection* conn, BitStream *stream)
{
   pack(conn, stream);
}

void NodeListEvent::unpack(NetConnection* conn, BitStream* stream)
{
   stream->read(&mId);
   stream->read(&mTotalNodes);
   stream->read(&mLocalListStart);

   mNodeList->mId = mId;

   // NOTE: Child class needs to populate the local node list
}

void NodeListEvent::process(NetConnection* conn)
{
   if (mNodeList)
   {
      NodeListManager::NodeList* oldList = NULL;

      gClientNodeListManager->findListById(mNodeList->mId, &oldList, false);
      mergeLists(oldList);

      gClientNodeListManager->addNodeList(mNodeList);
      mNodeList = NULL;
   }
}

void NodeListEvent::mergeLists(NodeListManager::NodeList* oldList)
{
   if (oldList)
   {
      if ( !mNodeList->mListComplete)
      {
         copyIntoList( oldList );

         // Is the node list now complete?
         oldList->mTotalValidNodes += mNodeList->mTotalValidNodes;
         if (oldList->mTotalValidNodes >= mTotalNodes)
         {
            oldList->mListComplete = true;
         }

         delete mNodeList;
         mNodeList = oldList;
      }
   }
   else
   {
      padListToSize();
   }
}

IMPLEMENT_CO_NETEVENT_V1(NodeListEvent);

ConsoleDocClass( NodeListEvent,
   "@brief Base class for events used by node editors, like River\n\n"
   "Editor use only.\n\n"
   "@internal"
);
//-----------------------------------------------------------------------------
// NodeListManager Class
//-----------------------------------------------------------------------------

NodeListManager* gClientNodeListManager = NULL;
NodeListManager* gServerNodeListManager = NULL;

U32 NodeListManager::smMaximumNodesPerEvent = 20;

//-----------------------------------------------------------------------------

NodeListManager::NodeListManager(const bool isServer)
{
   mIsServer = isServer;
   mNextListId = 0;
}

NodeListManager::~NodeListManager()
{
   clearAllNotifications();
   clearNodeLists();
}

void NodeListManager::clearNodeLists()
{
   for ( U32 i=0; i<mNodeLists.size(); ++i )
   {
      delete mNodeLists[i];
   }
   mNodeLists.clear();
}

U32 NodeListManager::nextListId()
{
   U32 id = mNextListId;
   ++mNextListId;
   return id;
}

void NodeListManager::addNodeList( NodeList* list )
{
   // Before we store the node list, we should check if anyone has registered
   // an interest in it, but only if the list is complete.
   if (list->mListComplete)
   {
      if (dispatchNotification( list ))
      {
         delete list;
         return;
      }
   }

   // Nothing is registered or the list is not complete, so store the list for later
   mNodeLists.push_back( list );
}

bool NodeListManager::findListById(U32 id, NodeList** list, bool completeOnly)
{
   *list = NULL;

   for (U32 i=0; i<mNodeLists.size(); ++i)
   {
      if (mNodeLists[i]->mId == id)
      {
         if (completeOnly && !mNodeLists[i]->mListComplete)
         {
            // Found the list, but it is not complete.
            return false;
         }

         // Return the node list (complete or not) and remove 
         // it from our list of lists
         *list = mNodeLists[i];
         mNodeLists.erase(i);
         return true;
      }
   }

   return false;
}

void NodeListManager::clearNotification( U32 listId )
{
   for (U32 i=0; i<mNotifyList.size(); ++i)
   {
      if (mNotifyList[i]->getListId() == listId)
      {
         delete mNotifyList[i];
         mNotifyList.erase(i);
         return;
      }
   }
}

void NodeListManager::clearAllNotifications()
{
   for (U32 i=0; i<mNotifyList.size(); ++i)
   {
      delete mNotifyList[i];
   }
   mNotifyList.clear();
}

void NodeListManager::registerNotification( NodeListNotify* notify )
{
   mNotifyList.push_back( notify );
}

bool NodeListManager::dispatchNotification( U32 listId )
{
   // Find the matching list
   NodeList* list = NULL;
   for (U32 i=0; i<mNodeLists.size(); ++i)
   {
      if (mNodeLists[i]->mId == listId)
      {
         list = mNodeLists[i];
         break;
      }
   }

   if (list)
      return dispatchNotification( list );

   return false;
}

bool NodeListManager::dispatchNotification( NodeList* list )
{
   for (U32 i=0; i<mNotifyList.size(); ++i)
   {
      if (mNotifyList[i]->getListId() == list->mId)
      {
         mNotifyList[i]->sendNotification( list );
         delete mNotifyList[i];
         mNotifyList.erase(i);

         return true;
      }
   }

   return false;
}
