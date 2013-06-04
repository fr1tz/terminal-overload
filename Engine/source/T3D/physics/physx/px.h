// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

//
// This PhysX implementation for Torque was originally based on
// the "PhysX in TGEA" resource written by Shannon Scarvaci.
//
// http://www.garagegames.com/index.php?sec=mg&mod=resource&page=view&qid=12711
//

#ifndef _PHYSX_H_
#define _PHYSX_H_

/*
#ifndef _TORQUE_TYPES_H_
#	include "platform/types.h"
#endif
*/

#include "platform/tmm_off.h"

#ifdef TORQUE_DEBUG
#include <crtdbg.h>
#endif

#if defined(TORQUE_OS_MAC) && !defined(__APPLE__)
   #define __APPLE__
#elif defined(TORQUE_OS_LINUX) && !defined(LINUX)
   #define LINUX
#elif defined(TORQUE_OS_WIN32) && !defined(WIN32)
   #define WIN32
#endif

#ifndef NX_PHYSICS_NXPHYSICS
#include <NxPhysics.h>
#endif
#ifndef NX_FOUNDATION_NXSTREAM
#include <NxStream.h>
#endif
#ifndef NX_COOKING_H
#include <NxCooking.h>
#endif
#ifndef NX_FOUNDATION_NXUSEROUTPUTSTREAM
#include <NxUserOutputStream.h>
#endif
#ifndef NX_PHYSICS_NXBIG
#include "NxExtended.h"
#endif
#include <NxUserAllocatorDefault.h>
#include <CCTAllocator.h>
#include <NxControllerManager.h>
#include <CharacterControllerManager.h>
#include <NxController.h>
#include <NxCapsuleController.h>

/// The single global physx sdk object for this process.
extern NxPhysicsSDK *gPhysicsSDK;

#include "platform/tmm_on.h"

#endif // _PHYSX_H_