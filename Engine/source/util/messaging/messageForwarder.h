// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/simBase.h"
#include "util/messaging/dispatcher.h"
#include "util/messaging/scriptMsgListener.h"

#ifndef _MESSAGEFORWARDER_H_
#define _MESSAGEFORWARDER_H_

/// @addtogroup msgsys Message System
// @{

//-----------------------------------------------------------------------------
/// @brief Forward messages from one queue to another
/// 
/// MessageForwarder is a script class that can be used to forward messages
/// from one queue to another.
///
/// <h2>Example</h2>
///
/// @code
/// %fwd = new MessageForwarder()
/// {
///    toQueue = "QueueToSendTo";
/// };
///
/// registerMessageListener("FromQueue", %fwd);
/// @endcode
///
/// Where "QueueToSendTo" is the queue you want to forward to, and
/// "FromQueue" is the queue you want to forward from.
///
//-----------------------------------------------------------------------------
class MessageForwarder : public ScriptMsgListener
{
   typedef ScriptMsgListener Parent;

protected:
   StringTableEntry mToQueue;

public:
   MessageForwarder();
   virtual ~MessageForwarder();
   DECLARE_CONOBJECT(MessageForwarder);

   static void initPersistFields();

   virtual bool onMessageReceived(StringTableEntry queue, const char *event, const char *data);
   virtual bool onMessageObjectReceived(StringTableEntry queue, Message *msg);
};

// @}

#endif // _MESSAGEFORWARDER_H_
