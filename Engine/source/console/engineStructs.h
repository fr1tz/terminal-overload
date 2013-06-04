// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ENGINESTRUCTS_H_
#define _ENGINESTRUCTS_H_

#ifndef _ENGINETYPES_H_
   #include "console/engineTypes.h"
#endif


/// @file
/// Definitions for the core engine structured types.


template< typename T > class Vector;
namespace Torque {
   class UUID;
}

class ColorI;
class ColorF;


DECLARE_STRUCT( Vector< bool > );
DECLARE_STRUCT( Vector< S32 > );
DECLARE_STRUCT( Vector< F32 > );
DECLARE_STRUCT( Torque::UUID );
DECLARE_STRUCT( ColorI );
DECLARE_STRUCT( ColorF );

#endif // !_ENGINESTRUCTS_H_
