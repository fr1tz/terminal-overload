// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/input/razerHydra/razerHydraUtil.h"

namespace RazerHydraUtil
{

enum Components
{
   X = 0,
   Y = 1,
   Z = 2,
};

void convertPosition(const F32 inPosition[3], F32& x, F32& y, F32& z)
{
   // Convert to Torque coordinates.  The conversion is:
   //
   // Motion       Torque
   // x y z   -->  x -z y
   x = inPosition[X];    // x = x
   y = -inPosition[Z];   // y = -z
   z = inPosition[Y];    // z = y;
}

void convertPosition(const F32 inPosition[3], Point3F& outPosition)
{
   // Convert to Torque coordinates.  The conversion is:
   //
   // Motion       Torque
   // x y z   -->  x -z y
   outPosition.x = inPosition[X];    // x = x
   outPosition.y = -inPosition[Z];   // y = -z
   outPosition.z = inPosition[Y];    // z = y;
}

void convertRotation(const F32 inRotMat[3][3], MatrixF& outRotation)
{
   // Set rotation.  We need to convert from sixense coordinates to
   // Torque coordinates.  The conversion is:
   //
   // Sixense                      Torque
   // a b c         a  b  c        a -c  b
   // d e f   -->  -g -h -i  -->  -g  i -h
   // g h i         d  e  f        d -f  e
   outRotation.setColumn(0, Point4F( inRotMat[0][0], -inRotMat[0][2],  inRotMat[0][1], 0.0f));
   outRotation.setColumn(1, Point4F(-inRotMat[2][0],  inRotMat[2][2], -inRotMat[2][1], 0.0f));
   outRotation.setColumn(2, Point4F( inRotMat[1][0], -inRotMat[1][2],  inRotMat[1][1], 0.0f));
   outRotation.setPosition(Point3F::Zero);
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
