// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/engineAPI.h"
#include "platform/platform.h"
#include "T3D/gameBase/gameProcess.h"

#include "T3D/gameBase/gameBase.h"
#include "T3D/gameBase/gameConnection.h"
#include "T3D/gameBase/moveList.h"

//----------------------------------------------------------------------------

ClientProcessList* ClientProcessList::smClientProcessList = NULL;
ServerProcessList* ServerProcessList::smServerProcessList = NULL;
static U32 gNetOrderNextId = 0;

DefineConsoleFunction( dumpProcessList, void, ( ), ,
   "Dumps all ProcessObjects in ServerProcessList and ClientProcessList to the console." )
{
   Con::printf( "client process list:" );
   ClientProcessList::get()->dumpToConsole();
   Con::printf( "server process list:" );
   ServerProcessList::get()->dumpToConsole();
}

//--------------------------------------------------------------------------
// ClientProcessList
//--------------------------------------------------------------------------

ClientProcessList::ClientProcessList()
{
}

void ClientProcessList::addObject( ProcessObject *pobj ) 
{
   AssertFatal( static_cast<SceneObject*>( pobj )->isClientObject(), "Tried to add server object to ClientProcessList." );

   GameBase *obj = getGameBase( pobj );   

   if ( obj && obj->isNetOrdered() )
   {
      if ( ( gNetOrderNextId & 0xFFFF ) == 0 )
         // don't let it be zero
         gNetOrderNextId++;

      pobj->mOrderGUID = ( gNetOrderNextId++ ) & 0xFFFF; // 16 bits should be enough
      pobj->plLinkBefore( &mHead );
      mDirty = true;
   }
   else if ( obj && obj->isTickLast() )
   {
      pobj->mOrderGUID = 0xFFFFFFFF;
      pobj->plLinkBefore( &mHead );
      // not dirty
   }
   else
   {
      pobj->plLinkAfter( &mHead );
      // not dirty
   }
}

bool ClientProcessList::doBacklogged( SimTime timeDelta )
{
   #ifdef TORQUE_DEBUG   
   static bool backlogged = false;
   static U32 backloggedTime = 0;
   #endif

   // See if the control object has pending moves.
   GameConnection *connection = GameConnection::getConnectionToServer();

   if ( connection )
   {
      // If the connection to the server is backlogged
      // the simulation is frozen.
      if ( connection->mMoveList->isBacklogged() )
      {
         #ifdef TORQUE_DEBUG   
         if ( !backlogged )
         {
            Con::printf( "client is backlogged, time is frozen" );
            backlogged = true;
         }

         backloggedTime += timeDelta;
         #endif

         return true;
      }
   }

   #ifdef TORQUE_DEBUG   
   if ( backlogged )
   {
      Con::printf( "client is no longer backlogged, time is unfrozen (%i ms elapsed)", backloggedTime );
      backlogged = false;
      backloggedTime = 0;
   }
   #endif

   return false;
}

void ClientProcessList::onPreTickObject( ProcessObject *pobj )
{
   // reset to tick boundary
   pobj->interpolateTick( 0.0f );
}


//--------------------------------------------------------------------------
// ServerProcessList
//--------------------------------------------------------------------------
   
ServerProcessList::ServerProcessList()
{
}

void ServerProcessList::addObject( ProcessObject *pobj ) 
{
   AssertFatal( static_cast<SceneObject*>( pobj )->isServerObject(), "Tried to add client object to ServerProcessList." );

   GameBase *obj = getGameBase( pobj );   

   if ( obj && obj->isNetOrdered() )
   {
      if ( ( gNetOrderNextId & 0xFFFF ) == 0)
         // don't let it be zero
         gNetOrderNextId++;

      pobj->mOrderGUID = ( gNetOrderNextId++ ) & 0xFFFF; // 16 bits should be enough
      pobj->plLinkBefore( &mHead );
      mDirty = true;
   }
   else if ( obj && obj->isTickLast() )
   {
      pobj->mOrderGUID = 0xFFFFFFFF;
      pobj->plLinkBefore( &mHead );
      // not dirty
   }
   else
   {
      pobj->plLinkAfter( &mHead );
      // not dirty
   }
}

void ServerProcessList::advanceObjects()
{
   #ifdef TORQUE_DEBUG_NET_MOVES
   Con::printf("Advance server time...");
   #endif

   Parent::advanceObjects();

   #ifdef TORQUE_DEBUG_NET_MOVES
   Con::printf("---------");
   #endif
}

void ServerProcessList::onPreTickObject( ProcessObject *pobj )
{
}

