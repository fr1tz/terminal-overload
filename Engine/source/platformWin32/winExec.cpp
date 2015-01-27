// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platformWin32/platformWin32.h"
#include "console/console.h"
#include "console/engineAPI.h"
#include "console/simBase.h"
#include "core/strings/unicode.h"
#include "platform/threads/thread.h"
#include "platform/threads/mutex.h"
#include "core/util/safeDelete.h"
#include "util/tempAlloc.h"

//-----------------------------------------------------------------------------
// Thread for executing in
//-----------------------------------------------------------------------------

class ExecuteThread : public Thread
{
   // [tom, 12/14/2006] mProcess is only used in the constructor before the thread
   // is started and in the thread itself so we should be OK without a mutex.
   HANDLE mProcess;

public:
   ExecuteThread(const char *executable, const char *args = NULL, const char *directory = NULL);

   virtual void run(void *arg = 0);
};

//-----------------------------------------------------------------------------
// Event for cleanup
//-----------------------------------------------------------------------------

class ExecuteCleanupEvent : public SimEvent
{
   ExecuteThread *mThread;
   bool mOK;

public:
   ExecuteCleanupEvent(ExecuteThread *thread, bool ok)
   {
      mThread = thread;
      mOK = ok;
   }

   virtual void process(SimObject *object)
   {
      if( Con::isFunction( "onExecuteDone" ) )
         Con::executef( "onExecuteDone", Con::getIntArg( mOK ) );
      SAFE_DELETE(mThread);
   }
};

//-----------------------------------------------------------------------------

ExecuteThread::ExecuteThread(const char *executable, const char *args /* = NULL */, const char *directory /* = NULL */) : Thread(0, NULL, false)
{
   SHELLEXECUTEINFO shl;
   dMemset(&shl, 0, sizeof(shl));

   shl.cbSize = sizeof(shl);
   shl.fMask = SEE_MASK_NOCLOSEPROCESS;
   
   char exeBuf[1024];
   Platform::makeFullPathName(executable, exeBuf, sizeof(exeBuf));
   
   TempAlloc< TCHAR > dirBuf( ( directory ? dStrlen( directory ) : 0 ) + 1 );
   dirBuf[ dirBuf.size - 1 ] = 0;

#ifdef UNICODE
   WCHAR exe[ 1024 ];
   convertUTF8toUTF16( exeBuf, exe, sizeof( exe ) / sizeof( exe[ 0 ] ) );

   TempAlloc< WCHAR > argsBuf( ( args ? dStrlen( args ) : 0 ) + 1 );
   argsBuf[ argsBuf.size - 1 ] = 0;

   if( args )
      convertUTF8toUTF16( args, argsBuf, argsBuf.size );
   if( directory )
      convertUTF8toUTF16( directory, dirBuf, dirBuf.size );
#else
   char* exe = exeBuf;
   char* argsBuf = args;
   if( directory )
      dStrpcy( dirBuf, directory );
#endif

   backslash( exe );
   backslash( dirBuf );
   
   shl.lpVerb = TEXT( "open" );
   shl.lpFile = exe;
   shl.lpParameters = argsBuf;
   shl.lpDirectory = dirBuf;

   shl.nShow = SW_SHOWNORMAL;

   if(ShellExecuteEx(&shl) && shl.hProcess)
   {
      mProcess = shl.hProcess;
      start();
   }
}

void ExecuteThread::run(void *arg /* = 0 */)
{
   if(mProcess == NULL)
      return;

   DWORD wait = WAIT_OBJECT_0 - 1; // i.e., not WAIT_OBJECT_0
   while(! checkForStop() && (wait = WaitForSingleObject(mProcess, 200)) != WAIT_OBJECT_0) ;

   Sim::postEvent(Sim::getRootGroup(), new ExecuteCleanupEvent(this, wait == WAIT_OBJECT_0), -1);
}

//-----------------------------------------------------------------------------
// Console Functions
//-----------------------------------------------------------------------------

DefineConsoleFunction( shellExecute, bool, (const char * executable, const char * args, const char * directory), ("", ""), "(string executable, string args, string directory)"
				"@brief Launches an outside executable or batch file\n\n"
				"@param executable Name of the executable or batch file\n"
				"@param args Optional list of arguments, in string format, to pass to the executable\n"
				"@param directory Optional string containing path to output or shell\n"
				"@ingroup Platform")
{
   ExecuteThread *et = new ExecuteThread( executable, args, directory );
   if(! et->isAlive())
   {
      delete et;
      return false;
   }

   return true;
}

#ifndef TORQUE_SDL

void Platform::openFolder(const char* path )
{
   char filePath[1024];
   Platform::makeFullPathName(path, filePath, sizeof(filePath));

#ifdef UNICODE
   WCHAR p[ 1024 ];
   convertUTF8toUTF16( filePath, p, sizeof( p ) / sizeof( p[ 0 ] ) );
#else
   char* p = filePath;
#endif

   backslash( p );

   ::ShellExecute( NULL,TEXT("explore"),p, NULL, NULL, SW_SHOWNORMAL);
}

void Platform::openFile(const char* path )
{
   char filePath[1024];
   Platform::makeFullPathName(path, filePath, sizeof(filePath));

#ifdef UNICODE
   WCHAR p[ 1024 ];
   convertUTF8toUTF16( filePath, p, sizeof( p ) / sizeof( p[ 0 ] ) );
#else
   char* p = filePath;
#endif

   backslash( p );

   ::ShellExecute( NULL,TEXT("open"),p, NULL, NULL, SW_SHOWNORMAL);
}

#endif // !TORQUE_SDL

