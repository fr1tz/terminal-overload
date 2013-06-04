// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TORQUE_CORE_UTIL_SAFECAST_H_
#define _TORQUE_CORE_UTIL_SAFECAST_H_

#include "platform/platform.h"

template< class T, typename I >
inline T* safeCast( I* inPtr )
{
   if( !inPtr )
      return 0;
   else
   {
      T* outPtr = dynamic_cast< T* >( inPtr );
      AssertFatal( outPtr != 0, "safeCast failed" );
      return outPtr;
   }
}

template<>
inline void* safeCast< void >( void* inPtr )
{
   return inPtr;
}

template< class T, typename I >
inline T* safeCastISV( I* inPtr )
{
   if( !inPtr )
      return 0;
   else
   {
      T* outPtr = dynamic_cast< T* >( inPtr );
      AssertISV( outPtr != 0, "safeCast failed" );
      return outPtr;
   }
}

#endif // _TORQUE_CORE_UTIL_SAFECAST_H_
