// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platformX86UNIX/platformX86UNIX.h"
#include <stdlib.h>
#include <mm_malloc.h>

void* dMemcpy(void *dst, const void *src, dsize_t size)
{
   return memcpy(dst,src,size);
}

//--------------------------------------
void* dMemmove(void *dst, const void *src, dsize_t size)
{
   return memmove(dst,src,size);
}

//--------------------------------------
void* dMemset(void *dst, S32 c, dsize_t size)
{
   return memset(dst,c,size);
}

//--------------------------------------
S32 dMemcmp(const void *ptr1, const void *ptr2, dsize_t len)
{
   return memcmp(ptr1, ptr2, len);
}

void* dRealMalloc(dsize_t s)
{
   return malloc(s);
}

void dRealFree(void* p)
{
   free(p);
}

void *dMalloc_aligned(dsize_t in_size, int alignment)
{
   return _mm_malloc(in_size, alignment);
}

void dFree_aligned(void* p)
{
   return _mm_free(p);
}
