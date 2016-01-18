// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _VITCPACKETRECEIVENOTIFICATIONOBJECT_H_
#define _VITCPACKETRECEIVENOTIFICATIONOBJECT_H_

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif

#include "platform/platformNet.h"

class vitcPacketReceiveNotificationObject : public SimObject
{
public:
	DECLARE_CALLBACK(void, onPacketReceive, (const char* address, const char* base64data));

protected:
   typedef SimObject Parent;

public:
   vitcPacketReceiveNotificationObject();
   virtual ~vitcPacketReceiveNotificationObject();

   void processPacketReceiveEvent(NetAddress srcAddress, RawData packetData);

   bool onAdd();

   DECLARE_CONOBJECT(vitcPacketReceiveNotificationObject);
};


#endif  // _VITCPACKETRECEIVENOTIFICATIONOBJECT_H_
