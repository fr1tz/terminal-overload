// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _OCULUSVRSENSORDATA_H_
#define _OCULUSVRSENSORDATA_H_

#include "platform/types.h"
#include "math/mMatrix.h"
#include "math/mQuat.h"
#include "math/mPoint2.h"
#include "OVR.h"

struct OculusVRSensorData
{
   enum DataDifferences {
      DIFF_NONE            = 0,
      DIFF_ROT             = (1<<0),
      DIFF_ROTAXISX        = (1<<1),
      DIFF_ROTAXISY        = (1<<2),

      DIFF_ROTAXIS = (DIFF_ROTAXISX | DIFF_ROTAXISY),
   };

   bool mDataSet;

   // Rotation
   MatrixF mRot;
   QuatF   mRotQuat;
   EulerF  mRotEuler;

   // Controller rotation as axis x, y
   Point2F mRotAxis;

   OculusVRSensorData();

   /// Reset the data
   void reset();

   /// Set data based on given sensor fusion
   void setData(const OVR::SensorFusion& data, const F32& maxAxisRadius);

   /// Simulate valid data
   void simulateData(const F32& maxAxisRadius);

   /// Compare this data and given and return differences
   U32 compare(OculusVRSensorData* other);
};

#endif   // _OCULUSVRSENSORDATA_H_
