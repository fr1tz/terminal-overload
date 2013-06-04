// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/simBase.h"

#ifndef _SCRIPTMSGLISTENER_H_
#define _SCRIPTMSGLISTENER_H_

#ifndef _DISPATCHER_H_
#include "util/messaging/dispatcher.h"
#endif

/// @addtogroup msgsys Message System
// @{

//-----------------------------------------------------------------------------
/// @brief Script accessible version of Dispatcher::IMessageListener
///
/// The main use of ScriptMsgListener is to allow script to listen for
/// messages. You can subclass ScriptMsgListener in script to receive
/// the Dispatcher::IMessageListener callbacks.
///
/// Alternatively, you can derive from it in C++ instead of SimObject to
/// get an object that implements Dispatcher::IMessageListener with script
/// callbacks. If you need to derive from something other then SimObject,
/// then you will need to implement the Dispatcher::IMessageListener
/// interface yourself.
//-----------------------------------------------------------------------------
class ScriptMsgListener : public SimObject, public virtual Dispatcher::IMessageListener
{
   typedef SimObject Parent;
   typedef Dispatcher::IMessageListener IMLParent;

public:
   ScriptMsgListener();

   DECLARE_CONOBJECT(ScriptMsgListener);
   
   DECLARE_CALLBACK( void, onAdd, () );
   DECLARE_CALLBACK( void, onRemove, () );

   DECLARE_CALLBACK( bool, onMessageReceived, ( const char* queue, const char* event, const char* data ) );
   DECLARE_CALLBACK( bool, onMessageObjectReceived, ( const char* queue, Message *msg ) );
   
   DECLARE_CALLBACK( void, onAddToQueue, ( const char* queue ) );
   DECLARE_CALLBACK( void, onRemoveFromQueue, ( const char* queue ) );

   ///////////////////////////////////////////////////////////////////////

   virtual bool onAdd();
   virtual void onRemove();

   ///////////////////////////////////////////////////////////////////////

   virtual bool onMessageReceived(StringTableEntry queue, const char* event, const char* data);
   virtual bool onMessageObjectReceived(StringTableEntry queue, Message *msg);

   virtual void onAddToQueue(StringTableEntry queue);
   virtual void onRemoveFromQueue(StringTableEntry queue);
};

// @}

#endif // _SCRIPTMSGLISTENER_H_
