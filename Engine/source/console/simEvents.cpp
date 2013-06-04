// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/console.h"
#include "console/consoleInternal.h"
#include "platform/threads/semaphore.h"
#include "console/simEvents.h"

// Stupid globals not declared in a header
extern ExprEvalState gEvalState;

SimConsoleEvent::SimConsoleEvent(S32 argc, const char **argv, bool onObject)
{
   mOnObject = onObject;
   mArgc = argc;
   U32 totalSize = 0;
   S32 i;
   for(i = 0; i < argc; i++)
      totalSize += dStrlen(argv[i]) + 1;
   totalSize += sizeof(char *) * argc;

   mArgv = (char **) dMalloc(totalSize);
   char *argBase = (char *) &mArgv[argc];

   for(i = 0; i < argc; i++)
   {
      mArgv[i] = argBase;
      dStrcpy(mArgv[i], argv[i]);
      argBase += dStrlen(argv[i]) + 1;
   }
}

SimConsoleEvent::~SimConsoleEvent()
{
   dFree(mArgv);
}

void SimConsoleEvent::process(SimObject* object)
{
   // #ifdef DEBUG
   //    Con::printf("Executing schedule: %d", sequenceCount);
   // #endif
   if(mOnObject)
      Con::execute(object, mArgc, const_cast<const char**>( mArgv ));
   else
   {
      // Grab the function name. If '::' doesn't exist, then the schedule is
      // on a global function.
      char* func = dStrstr( mArgv[0], (char*)"::" );
      if( func )
      {
         // Set the first colon to NULL, so we can reference the namespace.
         // This is okay because events are deleted immediately after
         // processing. Maybe a bad idea anyway?
         func[0] = '\0';

         // Move the pointer forward to the function name.
         func += 2;

         // Lookup the namespace and function entry.
         Namespace* ns = Namespace::find( StringTable->insert( mArgv[0] ) );
         if( ns )
         {
            Namespace::Entry* nse = ns->lookup( StringTable->insert( func ) );
            if( nse )
               // Execute.
               nse->execute( mArgc, (const char**)mArgv, &gEvalState );
         }
      }

      else
         Con::execute(mArgc, const_cast<const char**>( mArgv ));
   }
}

//-----------------------------------------------------------------------------

SimConsoleThreadExecCallback::SimConsoleThreadExecCallback() : retVal(NULL)
{
   sem = new Semaphore(0);
}

SimConsoleThreadExecCallback::~SimConsoleThreadExecCallback()
{
   delete sem;
}

void SimConsoleThreadExecCallback::handleCallback(const char *ret)
{
   retVal = ret;
   sem->release();
}

const char *SimConsoleThreadExecCallback::waitForResult()
{
   if(sem->acquire(true))
   {
      return retVal;
   }

   return NULL;
}

//-----------------------------------------------------------------------------

SimConsoleThreadExecEvent::SimConsoleThreadExecEvent(S32 argc, const char **argv, bool onObject, SimConsoleThreadExecCallback *callback) :
   SimConsoleEvent(argc, argv, onObject), cb(callback)
{
}

void SimConsoleThreadExecEvent::process(SimObject* object)
{
   const char *retVal;
   if(mOnObject)
      retVal = Con::execute(object, mArgc, const_cast<const char**>( mArgv ));
   else
      retVal = Con::execute(mArgc, const_cast<const char**>( mArgv ));

   if(cb)
      cb->handleCallback(retVal);
}
