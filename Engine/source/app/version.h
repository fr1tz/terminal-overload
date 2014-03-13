// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _VERSION_H_
#define _VERSION_H_

/// Since we can build different engine "products" out of the same
/// base engine source we need a way to differentiate which product
/// this particular game is using.
///
/// TGE             0001
/// TGEA            0002
/// TGB             0003
/// TGEA 360        0004
/// TGE  WII        0005
/// Torque 3D       0006
/// Torque 3D MIT   0007
/// NOTC            0010
#define TORQUE_ENGINE_PRODUCT      0010

/// This is our global version number for the engine source code that
/// we are using. See <game>/source/torqueConfig.h for the game's source
/// code version, the game name, and which type of game it is (TGB, TGE, TGEA, etc.).
///
/// Version number is major * 1000 + minor * 100 + revision * 10.
#define TORQUE_GAME_ENGINE          3500

/// Human readable engine version string.
#define TORQUE_GAME_ENGINE_VERSION_STRING  "3.5"

/// Gets the engine version number.  The version number is specified as a global in version.cc
U32 getVersionNumber();
/// Gets the engine version number in a human readable form
const char* getVersionString();
/// Gets the engine product name in string form
const char* getEngineProductString();
/// Gets the compile date and time
const char* getCompileTimeString();

/// Gets the application version number.  The version number is specified as a global in torqueConfig.h
U32 getAppVersionNumber();
/// Gets the human readable application version string.
const char* getAppVersionString();

#endif
