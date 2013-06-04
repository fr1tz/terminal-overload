// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ASYNCUPDATE_H_
#define _ASYNCUPDATE_H_

#ifndef _PLATFORM_THREADS_THREAD_H_
#  include "platform/threads/thread.h"
#endif
#ifndef _THREADSAFEREFCOUNT_H_
#  include "platform/threads/threadSafeRefCount.h"
#endif
#ifndef _THREADSAFEDEQUE_H_
#  include "platform/threads/threadSafeDeque.h"
#endif


class IPolled;

//--------------------------------------------------------------------------
//    Async update list.
//--------------------------------------------------------------------------

/// This structure keeps track of the objects that need
/// updating.
class AsyncUpdateList : public ThreadSafeRefCount< AsyncUpdateList >
{
   protected:

      typedef ThreadSafeDeque< IPolled* > UpdateList;

      /// List of structures currently in the update loop.
      UpdateList mUpdateList;

   public:

      virtual ~AsyncUpdateList() {}

      /// Update the structures currently on the processing list.
      ///
      /// @param timeOut Soft limit in milliseconds on the time
      ///   spent on flushing the list.  Default of -1 means no
      ///   limit and function will only return, if update list
      ///   has been fully flushed.
      virtual void process( S32 timeOut = -1 );

      /// Add the structure to the update list.  It will stay
      /// on this list, until its update() method returns false.
      ///
      /// @note This can be called on different threads.
      virtual void add( IPolled* ptr )
      {
         mUpdateList.pushBack( ptr );
      }
};

//--------------------------------------------------------------------------
//    Async update thread.
//--------------------------------------------------------------------------

/// Abstract baseclass for async update threads.
class AsyncUpdateThread : public Thread, public ThreadSafeRefCount< AsyncUpdateThread >
{
   public:

      typedef Thread Parent;

   protected:

      /// Name of this thread.
      String mName;

      /// Platform-dependent event data.
      void* mUpdateEvent;

      /// The update list processed on this thread.
      ThreadSafeRef< AsyncUpdateList > mUpdateList;

      /// Wait for an update event being triggered and
      /// immediately reset the event.
      ///
      /// @note Note that this must be an atomic operation to avoid
      ///   a race condition.  Immediately resetting the event shields
      ///   us from event releases happening during us updating getting
      ///   ignored.
      virtual void _waitForEventAndReset();

   public:

      /// Create the update thread.
      /// The thread won't immediately start (we have virtual functions
      /// so construction needs to finish first) and will not auto-delete
      /// itself.
      AsyncUpdateThread( String name, AsyncUpdateList* updateList );

      virtual ~AsyncUpdateThread();

      virtual void run( void* );

      /// Trigger the update event to notify the thread about
      /// pending updates.
      virtual void triggerUpdate();

      ///
      const String& getName() const { return mName; }

      ///
      void* getUpdateEvent() const { return mUpdateEvent; }
};

/// Extension to update thread that also does automatic
/// periodic updates.
class AsyncPeriodicUpdateThread : public AsyncUpdateThread
{
      typedef AsyncUpdateThread Parent;

   protected:

      /// Platform-dependent timer event.
      void* mUpdateTimer;
      
      /// Time between periodic updates in milliseconds.
      U32 mIntervalMS;

      virtual void _waitForEventAndReset();

   public:

      enum
      {
         /// Default interval between periodic updates in milliseconds.
         DEFAULT_UPDATE_INTERVAL = 4000
      };

      ///
      AsyncPeriodicUpdateThread(  String name,
                                  AsyncUpdateList* updateList,
                                  U32 intervalMS = DEFAULT_UPDATE_INTERVAL );

      virtual ~AsyncPeriodicUpdateThread();
};

#endif // _TORQUE_CORE_ASYNC_ASYNCUPDATE_H_
