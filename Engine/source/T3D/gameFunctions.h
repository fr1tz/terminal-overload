// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GAMEFUNCTIONS_H_
#define _GAMEFUNCTIONS_H_

#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif
#ifndef _MMATRIX_H_
#include "math/mMatrix.h"
#endif

struct CameraQuery;


/// Actually renders the world.  This is the function that will render the
/// scene ONLY - new guis, no damage flashes.
void GameRenderWorld();

/// Renders overlays such as damage flashes, white outs, and water masks.  
/// These are usually a color applied over the entire screen.
void GameRenderFilters(const CameraQuery& camq);

/// Does the same thing as GameGetCameraTransform, but fills in other data 
/// including information about the far and near clipping planes.
bool GameProcessCameraQuery(CameraQuery *query);

/// Gets the position, rotation, and velocity of the camera.
bool GameGetCameraTransform(MatrixF *mat, Point3F *velocity);

/// Gets the camera field of view angle.
F32 GameGetCameraFov();

/// Sets the field of view angle of the camera.
void GameSetCameraFov(F32 fov);

/// Sets where the camera fov will be change to.  This is for 
/// non-instantaneous zooms/retractions.
void GameSetCameraTargetFov(F32 fov);

/// Update the camera fov to be closer to the target fov.
void GameUpdateCameraFov();

#endif // _GAMEFUNCTIONS_H_
