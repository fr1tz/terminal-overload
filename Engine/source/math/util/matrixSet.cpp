// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "math/util/matrixSet.h"


MatrixSet::MatrixSet()
{
   // [9/4/2009 Pat] Until we get better control over heap allocations in Torque
   // this class will provide a place where aligned/specalized matrix math can take place.
   // We should be able to plug in any kind of platform-specific optimization 
   // behind the delgates.
   AssertFatal( ((int)this & 0xF) == 0, "MatrixSet has been allocated off a 16-byte boundary!" );

   // Must be initialized by name, not a for(), it's macro magic
   MATRIX_SET_BIND_VALUE(ObjectToWorld);
   MATRIX_SET_BIND_VALUE(WorldToCamera);
   MATRIX_SET_BIND_VALUE(CameraToScreen);
   MATRIX_SET_BIND_VALUE(ObjectToCamera);
   MATRIX_SET_BIND_VALUE(WorldToObject);
   MATRIX_SET_BIND_VALUE(CameraToWorld);
   MATRIX_SET_BIND_VALUE(ObjectToScreen);
   MATRIX_SET_BIND_VALUE(CameraToObject);
   MATRIX_SET_BIND_VALUE(WorldToScreen);
   MATRIX_SET_BIND_VALUE(SceneView);
   MATRIX_SET_BIND_VALUE(SceneProjection);

   mViewSource = NULL;
   mProjectionSource = NULL;
}