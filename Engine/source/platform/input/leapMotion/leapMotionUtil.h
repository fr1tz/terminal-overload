// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _LEAPMOTIONUTIL_H_
#define _LEAPMOTIONUTIL_H_

#include "math/mPoint3.h"
#include "math/mMatrix.h"
#include "Leap.h"

namespace LeapMotionUtil
{
   /// Convert from a Leap Motion position to a Torque 3D position
   void convertPosition(const Leap::Vector& inPosition, F32& x, F32& y, F32& z);

   /// Convert from a Leap Motion position to a Torque 3D Point3F
   void convertPosition(const Leap::Vector& inPosition, Point3F& outPosition);

   /// Convert a Leap Motion hand's rotation to a Torque 3D matrix
   void convertHandRotation(const Leap::Hand& hand, MatrixF& outRotation);

   /// Calcualte a hand's rotation as if it were a thumb stick axis
   void calculateHandAxisRotation(const MatrixF& handRotation, const F32& maxHandAxisRadius, Point2F& outRotation);

   /// Convert a Leap Motion pointable's rotation to a Torque 3D matrix
   void convertPointableRotation(const Leap::Pointable& pointable, MatrixF& outRotation);
}

#endif
