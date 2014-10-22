// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PLATFORMINTRINSICS_H_
#define _PLATFORMINTRINSICS_H_

#ifndef _TORQUE_TYPES_H_
#  include "platform/types.h"
#endif

#if defined( TORQUE_COMPILER_VISUALC )
#  include "platform/platformIntrinsics.visualc.h"
#elif defined ( TORQUE_COMPILER_GCC )
#  include "platform/platformIntrinsics.gcc.h"
#else
#  error No intrinsics implemented for compiler.
#endif

//TODO: 64bit safe

template< typename T >
inline bool dCompareAndSwap( T* volatile& refPtr, T* oldPtr, T* newPtr )
{
   return dCompareAndSwap( *reinterpret_cast< volatile size_t* >( &refPtr ), ( size_t ) oldPtr, ( size_t ) newPtr );
}

// Test-And-Set

inline bool dTestAndSet( volatile U32& ref )
{
   return dCompareAndSwap( ref, 0, 1 );
}
inline bool dTestAndSet( volatile U64& ref )
{
   return dCompareAndSwap( ref, 0, 1 );
}

#endif // _PLATFORMINTRINSICS_H_
