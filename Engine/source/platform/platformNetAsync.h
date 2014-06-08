// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef PLATFORM_NET_ASYNC_H
#define PLATFORM_NET_ASYNC_H

#include "platform/platform.h"
#include "platform/platformNet.h"
#include "core/util/tVector.h"

// class for doing asynchronous network operations on unix (linux and 
// hopefully osx) platforms.  right now it only implements dns lookups
class NetAsync
{
   private:
      struct NameLookupRequest;
      struct NameLookupWorkItem;

      typedef Vector< NameLookupRequest > RequestVector;
      typedef RequestVector::iterator RequestIterator;

      RequestVector mLookupRequests;

   public:
      NetAsync();

      // queue a DNS lookup.  only one dns lookup can be queued per socket at
      // a time.  subsequent queue request for the socket are ignored.  use
      // checkLookup() to check the status of a request.
      void queueLookup(const char* remoteAddr, NetSocket socket);

      // check on the status of a dns lookup for a socket.  if the lookup is 
      // not yet complete, the function will return false.  if it is 
      // complete, the function will return true, and out_h_addr and 
      // out_h_length will be set appropriately.  if out_h_length is -1, then
      // name could not be resolved.  otherwise, it provides the number of
      // address bytes copied into out_h_addr.
      bool checkLookup(NetSocket socket, char* out_h_addr, int* out_h_length, S32 out_h_addr_size);
};

// the global net async object
extern NetAsync gNetAsync;

#endif
