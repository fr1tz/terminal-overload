// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TORQUE_PLATFORM_PLATFORMMEMORY_H_
#define _TORQUE_PLATFORM_PLATFORMMEMORY_H_

#include "platform/platform.h"

namespace Memory
{
   enum EFlag
   {
      FLAG_Debug,
      FLAG_Global,
      FLAG_Static
   };

   struct Info
   {
      U32         mAllocNumber;
      U32         mAllocSize;
      const char* mFileName;
      U32         mLineNumber;
      bool        mIsArray;
      bool        mIsGlobal;
      bool        mIsStatic;
   };

   void        checkPtr( void* ptr );
   void        flagCurrentAllocs( EFlag flag = FLAG_Debug );
   void        ensureAllFreed();
   void        dumpUnflaggedAllocs(const char *file, EFlag flag = FLAG_Debug );
   S32         countUnflaggedAllocs(const char *file, S32 *outUnflaggedRealloc = NULL, EFlag flag = FLAG_Debug );
   dsize_t     getMemoryUsed();
   dsize_t     getMemoryAllocated();
   void        getMemoryInfo( void* ptr, Info& info );
   void        validate();
}

#endif // _TORQUE_PLATFORM_PLATFORMMEMORY_H_
