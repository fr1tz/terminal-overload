// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "core/util/tVector.h"

#include "platform/profiler.h"


#ifdef TORQUE_DEBUG_GUARD

bool VectorResize(U32 *aSize, U32 *aCount, void **arrayPtr, U32 newCount, U32 elemSize,
                  const char* fileName,
                  const U32   lineNum)
{
   PROFILE_SCOPE( VectorResize );

   if (newCount > 0) 
   {
      U32 blocks = newCount / VectorBlockSize;
      if (newCount % VectorBlockSize)
         blocks++;
      S32 mem_size = blocks * VectorBlockSize * elemSize;

      const char* pUseFileName = fileName != NULL ? fileName : __FILE__;
      U32 useLineNum           = fileName != NULL ? lineNum  : __LINE__;

      if (*arrayPtr != NULL)
         *arrayPtr = dRealloc_r(*arrayPtr, mem_size, pUseFileName, useLineNum);
      else
         *arrayPtr = dMalloc_r(mem_size, pUseFileName, useLineNum);

      AssertFatal( *arrayPtr, "VectorResize - Allocation failed." );

      *aCount = newCount;
      *aSize = blocks * VectorBlockSize;
      return true;
   }

   if (*arrayPtr) 
   {
      dFree(*arrayPtr);
      *arrayPtr = 0;
   }

   *aSize  = 0;
   *aCount = 0;
   return true;
}

#else

bool VectorResize(U32 *aSize, U32 *aCount, void **arrayPtr, U32 newCount, U32 elemSize)
{
   PROFILE_SCOPE( VectorResize );

   if (newCount > 0)
   {
      U32 blocks = newCount / VectorBlockSize;
      if (newCount % VectorBlockSize)
         blocks++;
      S32 mem_size = blocks * VectorBlockSize * elemSize;
      *arrayPtr = *arrayPtr ? dRealloc(*arrayPtr,mem_size) :
         dMalloc(mem_size);

      *aCount = newCount;
      *aSize = blocks * VectorBlockSize;
      return true;
   }

   if (*arrayPtr) 
   {
      dFree(*arrayPtr);
      *arrayPtr = 0;
   }

   *aSize = 0;
   *aCount = 0;
   return true;
}

#endif
