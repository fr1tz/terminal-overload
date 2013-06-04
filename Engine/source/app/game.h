// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GAME_H_
#define _GAME_H_

#ifndef _TORQUE_TYPES_H_
#include "platform/types.h"
#endif

/// Processes the next frame, including gui, rendering, and tick interpolation.
/// This function will only have an effect when executed on the client.
bool clientProcess(U32 timeDelta);

/// Processes the next cycle on the server.  This function will only have an effect when executed on the server.
bool serverProcess(U32 timeDelta);

#endif
