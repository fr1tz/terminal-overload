// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GAMEPROCESS_H_
#define _GAMEPROCESS_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _PROCESSLIST_H_
#include "T3D/gameBase/processList.h"
#endif


class GameBase;
class GameConnection;
struct Move;


class ClientProcessList : public ProcessList
{
   typedef ProcessList Parent;
   
public:

   ClientProcessList();
   
   // ProcessList
   void addObject( ProcessObject *pobj );  
   
   /// Called after a correction packet is received from the server.
   /// If the control object was corrected it will now play back any moves
   /// which were rolled back.
   virtual void clientCatchup( GameConnection *conn ) {}

   static ClientProcessList* get() { return smClientProcessList; }

protected:   
   
   // ProcessList
   void onPreTickObject( ProcessObject *pobj );

   /// Returns true if backlogged.
   bool doBacklogged( SimTime timeDelta );

protected:

   static ClientProcessList* smClientProcessList;
};


class ServerProcessList : public ProcessList
{
   typedef ProcessList Parent;

public:

   ServerProcessList();
   
   // ProcessList
   void addObject( ProcessObject *pobj );

   static ServerProcessList* get() { return smServerProcessList; }

protected:

   // ProcessList
   void onPreTickObject( ProcessObject *pobj );
   void advanceObjects();

protected:

   static ServerProcessList* smServerProcessList;
};


#endif // _GAMEPROCESS_H_