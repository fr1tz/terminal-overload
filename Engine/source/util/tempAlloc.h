// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TEMPALLOC_H_
#define _TEMPALLOC_H_

#ifndef _PLATFORM_H_
#  include "platform/platform.h"
#endif


template< typename T >
struct TempAlloc
{
   T* ptr;
   U32 size;

   TempAlloc()
      : size( 0 ), ptr( 0 ) {}
   TempAlloc( U32 size )
      : size( size )
   {
      ptr = ( T* ) dMalloc( size * sizeof( T ) );
   }
   ~TempAlloc()
   {
      if( ptr )
         dFree( ptr );
   }
   operator T*()
   {
      return ptr;
   }

private:
   // Not safe.
   TempAlloc( const TempAlloc& ) {}
};

#endif // _TEMPALLOC_H_
