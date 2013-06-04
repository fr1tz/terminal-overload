// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/input/oculusVR/oculusVRUtil.h"

namespace OculusVRUtil
{

void convertRotation(const F32 inRotMat[4][4], MatrixF& outRotation)
{
   // Set rotation.  We need to convert from sensor coordinates to
   // Torque coordinates.  The sensor matrix is stored row-major.
   // The conversion is:
   //
   // Sensor                       Torque
   // a b c         a  b  c        a -c  b
   // d e f   -->  -g -h -i  -->  -g  i -h
   // g h i         d  e  f        d -f  e
   outRotation.setColumn(0, Point4F( inRotMat[0][0], -inRotMat[2][0],  inRotMat[1][0], 0.0f));
   outRotation.setColumn(1, Point4F(-inRotMat[0][2],  inRotMat[2][2], -inRotMat[1][2], 0.0f));
   outRotation.setColumn(2, Point4F( inRotMat[0][1], -inRotMat[2][1],  inRotMat[1][1], 0.0f));
   outRotation.setPosition(Point3F::Zero);
}

void convertRotation(OVR::Quatf& inRotation, EulerF& outRotation)
{
   F32 yaw, pitch, roll;
   inRotation.GetEulerAngles<OVR::Axis_Y, OVR::Axis_X, OVR::Axis_Z>(&yaw, &pitch, &roll);
   outRotation.x = -pitch;
   outRotation.y = roll;
   outRotation.z = -yaw;
}

void calculateAxisRotation(const MatrixF& inRotation, const F32& maxAxisRadius, Point2F& outRotation)
{
   const VectorF& controllerUp = inRotation.getUpVector();
   Point2F axis(0,0);
   axis.x = controllerUp.x;
   axis.y = controllerUp.y;

   // Limit the axis angle to that given to us
   if(axis.len() > maxAxisRadius)
   {
      axis.normalize(maxAxisRadius);
   }

   // Renormalize to the range of 0..1
   if(maxAxisRadius != 0.0f)
   {
      axis /= maxAxisRadius;
   }

   outRotation.x = axis.x;
   outRotation.y = axis.y;
}

}