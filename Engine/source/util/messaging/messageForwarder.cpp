// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "util/messaging/messageForwarder.h"

#include "console/consoleTypes.h"

//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------

MessageForwarder::MessageForwarder()
{
   mToQueue = "";
}

MessageForwarder::~MessageForwarder()
{
}

IMPLEMENT_CONOBJECT(MessageForwarder);

ConsoleDocClass( MessageForwarder,
	"@brief Forward messages from one queue to another\n\n"

	"MessageForwarder is a script class that can be used to forward messages "
	"from one queue to another.\n\n"
	
	"@tsexample\n"
	"%fwd = new MessageForwarder()\n"
	"{\n"
	"	toQueue = \"QueueToSendTo\";\n"
	"};\n\n"
	"registerMessageListener(\"FromQueue\", %fwd);\n"
	"@endtsexample\n\n"

	"Where \"QueueToSendTo\" is the queue you want to forward to, and "
	"\"FromQueue\" is the queue you want to forward from.\n\n"

   "@ingroup Messaging\n"
);

//-----------------------------------------------------------------------------

void MessageForwarder::initPersistFields()
{
   addField("toQueue", TypeCaseString, Offset(mToQueue, MessageForwarder), "Name of queue to forward to");

   Parent::initPersistFields();
}

//-----------------------------------------------------------------------------
// Public Methods
//-----------------------------------------------------------------------------

bool MessageForwarder::onMessageReceived(StringTableEntry queue, const char *event, const char *data)
{
   if(*mToQueue)
      Dispatcher::dispatchMessage(queue, event, data);
   return Parent::onMessageReceived(queue, event, data);
}

bool MessageForwarder::onMessageObjectReceived(StringTableEntry queue, Message *msg)
{
   if(*mToQueue)
      Dispatcher::dispatchMessageObject(mToQueue, msg);
   return Parent::onMessageObjectReceived(queue, msg);
}
