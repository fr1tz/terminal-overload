// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _HASHFUNCTION_H_
#define _HASHFUNCTION_H_

#ifndef _TORQUE_TYPES_H_
#include "platform/types.h"
#endif

namespace Torque
{

extern U32 hash(register const U8 *k, register U32 length, register U32 initval);

extern U64 hash64(register const U8 *k, register U32 length, register U64 initval);

}

#endif // _HASHFUNCTION_H_
