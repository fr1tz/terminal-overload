// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TORQUE_PLATFORM_PLATFORMINTRINSICS_VISUALC_H_
#define _TORQUE_PLATFORM_PLATFORMINTRINSICS_VISUALC_H_

/// @file
/// Compiler intrinsics for Visual C++.

#if defined(TORQUE_OS_XENON)
#  include <Xtl.h>
#  define _InterlockedExchangeAdd InterlockedExchangeAdd
#  define _InterlockedExchangeAdd64 InterlockedExchangeAdd64
#else
#	include <intrin.h>
#endif

// Fetch-And-Add
//
// NOTE: These do not return the pre-add value because
// not all platforms (damn you OSX) can do that.
//
inline void dFetchAndAdd( volatile U32& ref, U32 val )
{  
   _InterlockedExchangeAdd( ( volatile long* ) &ref, val );
}
inline void dFetchAndAdd( volatile S32& ref, S32 val )
{
   _InterlockedExchangeAdd( ( volatile long* ) &ref, val );
}

#if defined(TORQUE_OS_XENON)
// Not available on x86
inline void dFetchAndAdd( volatile U64& ref, U64 val )
{
   _InterlockedExchangeAdd64( ( volatile __int64* ) &ref, val );
}
#endif

// Compare-And-Swap

inline bool dCompareAndSwap( volatile U32& ref, U32 oldVal, U32 newVal )
{
   return ( _InterlockedCompareExchange( ( volatile long* ) &ref, newVal, oldVal ) == oldVal );
}
inline bool dCompareAndSwap( volatile U64& ref, U64 oldVal, U64 newVal )
{
   return ( _InterlockedCompareExchange64( ( volatile __int64* ) &ref, newVal, oldVal ) == oldVal );
}

/// Performs an atomic read operation.
inline U32 dAtomicRead( volatile U32 &ref )
{
   return _InterlockedExchangeAdd( ( volatile long* )&ref, 0 );
}

#endif // _TORQUE_PLATFORM_PLATFORMINTRINSICS_VISUALC_H_
