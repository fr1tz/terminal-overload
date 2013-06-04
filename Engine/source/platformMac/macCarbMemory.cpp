// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include <stdlib.h>
#include <string.h>
#include <mm_malloc.h>

//--------------------------------------
void* dRealMalloc(dsize_t in_size)
{
   return malloc(in_size);
}


//--------------------------------------
void dRealFree(void* in_pFree)
{
   free(in_pFree);
}

void *dMalloc_aligned(dsize_t in_size, int alignment)
{
   return _mm_malloc(in_size, alignment);
}

void dFree_aligned(void* p)
{
   return _mm_free(p);
}

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
void* dMemset(void *dst, int c, dsize_t size)
{
   return memset(dst,c,size);   
}   

//--------------------------------------
int dMemcmp(const void *ptr1, const void *ptr2, dsize_t len)
{
   return(memcmp(ptr1, ptr2, len));
}
