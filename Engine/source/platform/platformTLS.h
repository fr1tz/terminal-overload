// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PLATFORMTLS_H_
#define _PLATFORMTLS_H_

#ifndef _TORQUE_TYPES_H_
#include "platform/types.h"
#endif

struct PlatformThreadStorage;

/// Platform independent per-thread storage class.
class ThreadStorage
{
   enum
   {
      PlatformThreadStorageStorageSize = 32,
   };

   PlatformThreadStorage *mThreadStorage;
   U8 mStorage[PlatformThreadStorageStorageSize];
public:
   /// ThreadStorage constructor.
   ThreadStorage();
   /// ThreadStorage destructor.
   ~ThreadStorage();

   /// returns the per-thread stored void pointer for this ThreadStorage.  The default value is NULL.
   void *get();
   /// sets the per-thread stored void pointer for this ThreadStorage object.
   void set(void *data);
};


#endif
