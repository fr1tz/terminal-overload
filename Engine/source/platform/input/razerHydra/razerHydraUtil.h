// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RAZERHYDRAUTIL_H_
#define _RAZERHYDRAUTIL_H_

#include "math/mPoint3.h"
#include "math/mMatrix.h"

namespace RazerHydraUtil
{
   /// Convert from a Razer Hydra controller position to a Torque 3D position
   void convertPosition(const F32 inPosition[3], F32& x, F32& y, F32& z);

   /// Convert from a Razer Hydra controller position to a Torque 3D Point3F
   void convertPosition(const F32 inPosition[3], Point3F& outPosition);

   /// Convert a Razer Hydra controller's rotation to a Torque 3D matrix
   void convertRotation(const F32 inRotMat[3][3], MatrixF& outRotation);

   /// Calcualte a controller's rotation as if it were a thumb stick axis
   void calculateAxisRotation(const MatrixF& inRotation, const F32& maxAxisRadius, Point2F& outRotation);
}

#endif   // _RAZERHYDRAUTIL_H_
