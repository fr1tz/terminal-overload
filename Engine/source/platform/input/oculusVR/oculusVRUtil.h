// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _OCULUSVRUTIL_H_
#define _OCULUSVRUTIL_H_

#include "math/mPoint2.h"
#include "math/mMatrix.h"
#include "OVR.h"

namespace OculusVRUtil
{
   /// Convert an OVR sensor's rotation to a Torque 3D matrix
   void convertRotation(const F32 inRotMat[4][4], MatrixF& outRotation);

   /// Convert an OVR sensor's rotation to Torque 3D Euler angles (in radians)
   void convertRotation(OVR::Quatf& inRotation, EulerF& outRotation);

   /// Calcualte a sensor's rotation as if it were a thumb stick axis
   void calculateAxisRotation(const MatrixF& inRotation, const F32& maxAxisRadius, Point2F& outRotation);
}

#endif   // _OCULUSVRUTIL_H_
