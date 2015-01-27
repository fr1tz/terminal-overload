// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/console.h"
#include "console/consoleInternal.h"
#include "platform/threads/semaphore.h"
#include "console/simEvents.h"

// Stupid globals not declared in a header
extern ExprEvalState gEvalState;

SimConsoleEvent::SimConsoleEvent(S32 argc, ConsoleValueRef *argv, bool onObject)
{
   mOnObject = onObject;
   mArgc = argc;

   mArgv = new ConsoleValueRef[argc];
   for (int i=0; i<argc; i++)
   {
      mArgv[i].value = new ConsoleValue();
      mArgv[i].value->type = ConsoleValue::TypeInternalString;
      mArgv[i].value->init();
      mArgv[i].value->setStringValue((const char*)argv[i]);
   }
}

SimConsoleEvent::~SimConsoleEvent()
{
   for (int i=0; i<mArgc; i++)
   {
      delete mArgv[i].value;
   }
   delete[] mArgv;
}

void SimConsoleEvent::process(SimObject* object)
{
   // #ifdef DEBUG
   //    Con::printf("Executing schedule: %d", sequenceCount);
   // #endif
   if(mOnObject)
      Con::execute(object, mArgc, mArgv );
   else
   {
      // Grab the function name. If '::' doesn't exist, then the schedule is
      // on a global function.
      char funcName[256];
      dStrncpy(funcName, (const char*)mArgv[0], 256);
      char* func = dStrstr( funcName, (char*)"::" );
      if( func )
      {
         // Set the first colon to NULL, so we can reference the namespace.
         // This is okay because events are deleted immediately after
         // processing. Maybe a bad idea anyway?
         func[0] = '\0';

         // Move the pointer forward to the function name.
         func += 2;

         // Lookup the namespace and function entry.
         Namespace* ns = Namespace::find( StringTable->insert( funcName ) );
         if( ns )
         {
            Namespace::Entry* nse = ns->lookup( StringTable->insert( func ) );
            if( nse )
               // Execute.
               nse->execute( mArgc, mArgv, &gEvalState );
         }
      }

      else
         Con::execute(mArgc, mArgv );
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

SimConsoleThreadExecEvent::SimConsoleThreadExecEvent(S32 argc, ConsoleValueRef *argv, bool onObject, SimConsoleThreadExecCallback *callback) :
   SimConsoleEvent(argc, argv, onObject), cb(callback)
{
}

void SimConsoleThreadExecEvent::process(SimObject* object)
{
   const char *retVal;
   if(mOnObject)
      retVal = Con::execute(object, mArgc, mArgv);
   else
      retVal = Con::execute(mArgc, mArgv);

   if(cb)
      cb->handleCallback(retVal);
}
