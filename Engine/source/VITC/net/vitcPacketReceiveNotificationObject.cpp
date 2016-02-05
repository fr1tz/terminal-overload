// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "VITC/net/vitcPacketReceiveNotificationObject.h"

#include "platform/platform.h"
#include "console/simBase.h"
#include "console/consoleInternal.h"
#include "console/engineAPI.h"
#include "core/base64.h"
#include "core/strings/stringUnit.h"
#include "sim/netConnection.h"
#include "sim/netInterface.h"

IMPLEMENT_CONOBJECT(vitcPacketReceiveNotificationObject);

IMPLEMENT_CALLBACK(vitcPacketReceiveNotificationObject, onAdd, void, (), (),
	"Called when the object is registered with the system after the object has been created.");
IMPLEMENT_CALLBACK(vitcPacketReceiveNotificationObject, onRemove, void, (), (),
	"Called when the object is removed from the system before it is deleted.");
IMPLEMENT_CALLBACK(vitcPacketReceiveNotificationObject, onPacketReceive, void, (const char* address, const char* base64data), (address, base64data),
   "@brief Called whenever a packet has been received.\n\n"
   "@param address Packet source address.\n"
   "@param base64data Raw data of the packet (base64 encoded).\n"
   );

vitcPacketReceiveNotificationObject::vitcPacketReceiveNotificationObject()
{
	Net::smPacketReceive.notify(this, &vitcPacketReceiveNotificationObject::processPacketReceiveEvent);
}

vitcPacketReceiveNotificationObject::~vitcPacketReceiveNotificationObject()
{
	Net::smPacketReceive.remove(this, &vitcPacketReceiveNotificationObject::processPacketReceiveEvent);
}

bool vitcPacketReceiveNotificationObject::onAdd()
{
   if(!Parent::onAdd())
      return false;

   const char *name = this->getName();

   if(name && name[0] && getClassRep())
   {
      Namespace *parent = getClassRep()->getNameSpace();
      Con::linkNamespaces(parent->mName, name);
      mNameSpace = Con::lookupNamespace(name);
   }

   // Notify Script.
   onAdd_callback();

   return true;
}

void vitcPacketReceiveNotificationObject::onRemove()
{
	// Notify Script.
	onRemove_callback();

	Parent::onRemove();
}

void vitcPacketReceiveNotificationObject::processPacketReceiveEvent(NetAddress srcAddress, RawData packetData)
{
	char addrBuf[256];
	Net::addressToString(&srcAddress, addrBuf);

	U8* buffer = (U8*)packetData.data;
	U32 size = packetData.size;

#if 0
	Con::printf("Packet from %s:", addrBuf);
	for(U32 i = 0; i < size; i++)
		Con::printf("%i: %i", i, buffer[i]);
#endif

	String data = base64_encode(buffer, size);
	onPacketReceive_callback(addrBuf, data.c_str());

#if 0
	ArrayObject* data = new ArrayObject();
	data->registerObject();

	char keyBuf[256];
	char valBuf[256];
	for(U32 i = 0; i < size; i++)
	{
		dSprintf(keyBuf, 256, "%i", i);
		dSprintf(valBuf, 256, "%i", buffer[i]);
		data->push_back(String(keyBuf), String(valBuf));
	}

	onPacketReceive_callback(addrBuf, data);

	data->deleteObject();
#endif
}

DefineConsoleFunction(vitcSendPacket, S32, (const char* address, const char* base64data), (""),
	"TODO")
{
	NetAddress addr;
	if(!Net::stringToAddress(address, &addr))
		return -1;

	U8* data = NULL;
	size_t dataSize = 0;
	if(base64data)
	{
		data = (U8*)dMalloc(dStrlen(base64data));
		dataSize = base64_decode(base64data, data);
	}

	int error = Net::sendto(&addr, data, dataSize);

	dFree(data);

	return error;
}