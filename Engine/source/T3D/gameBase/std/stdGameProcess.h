// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GAMEPROCESS_STD_H_
#define _GAMEPROCESS_STD_H_

//#include "T3D/gameBase/processList.h"
#ifndef _GAMEPROCESS_H_
#include "T3D/gameBase/gameProcess.h"
#endif

class GameBase;
class GameConnection;
struct Move;

//----------------------------------------------------------------------------

/// List to keep track of GameBases to process.
class StdClientProcessList : public ClientProcessList
{
   typedef ClientProcessList Parent;

protected:
   
   // ProcessList
   void onTickObject(ProcessObject *);
   void advanceObjects();
   void onAdvanceObjects();
   
public:

   StdClientProcessList();  

   // ProcessList
   bool advanceTime( SimTime timeDelta );
   
   // ClientProcessList
   void clientCatchup( GameConnection *conn );
   
   static void init();
   static void shutdown();
};

class StdServerProcessList : public ServerProcessList
{
   typedef ServerProcessList Parent;

protected:

   // ProcessList
   void onPreTickObject( ProcessObject *pobj );
   void onTickObject( ProcessObject *pobj );
   void advanceObjects();

public:

   StdServerProcessList();  

   static void init();
   static void shutdown();
};

#endif // _GAMEPROCESS_STD_H_