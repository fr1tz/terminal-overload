// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TCPOBJECT_H_
#define _TCPOBJECT_H_

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif

#include "platform/platformNet.h"

class TCPObject : public SimObject
{
public:
   enum State {Disconnected, DNSResolved, Connected, Listening };

	DECLARE_CALLBACK(void, onConnectionRequest, (const char* address, const char* ID));
	DECLARE_CALLBACK(void, onLine, (const char* line));
	DECLARE_CALLBACK(void, onDNSResolved,());
	DECLARE_CALLBACK(void, onDNSFailed, ());
	DECLARE_CALLBACK(void, onConnected, ());
	DECLARE_CALLBACK(void, onConnectFailed, ());
	DECLARE_CALLBACK(void, onDisconnect, ());

private:
   NetSocket mTag;
   TCPObject *mNext;
   enum { TableSize = 256, TableMask = 0xFF };
   static TCPObject *table[TableSize];
   State mState;

protected:
   typedef SimObject Parent;
   U8 *mBuffer;
   U32 mBufferSize;
   U16 mPort;

public:
   TCPObject();
   virtual ~TCPObject();

   void parseLine(U8 *buffer, U32 *start, U32 bufferLen);
   void finishLastLine();

   static TCPObject *find(NetSocket tag);

   // onReceive gets called continuously until all bytes are processed
   // return # of bytes processed each time.
   virtual U32 onReceive(U8 *buffer, U32 bufferLen); // process a buffer of raw packet data
   virtual bool processLine(UTF8 *line); // process a complete line of text... default action is to call into script
   virtual void onDNSResolved();
   virtual void onDNSFailed();
   virtual void onConnected();
   virtual void onConnectFailed();
   virtual void onConnectionRequest(const NetAddress *addr, U32 connectId);
   virtual void onDisconnect();
   void connect(const char *address);
   void listen(U16 port);
   void disconnect();
   State getState() { return mState; }

   bool processArguments(S32 argc, const char **argv);
   void send(const U8 *buffer, U32 bufferLen);
   void addToTable(NetSocket newTag);
   void removeFromTable();

   void setPort(U16 port) { mPort = port; }

   bool onAdd();

   DECLARE_CONOBJECT(TCPObject);

};


#endif  // _H_TCPOBJECT_
