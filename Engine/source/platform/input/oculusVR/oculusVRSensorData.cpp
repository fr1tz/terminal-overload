// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/input/oculusVR/oculusVRSensorData.h"
#include "platform/input/oculusVR/oculusVRUtil.h"
#include "console/console.h"

OculusVRSensorData::OculusVRSensorData()
{
   reset();
}

void OculusVRSensorData::reset()
{
   mDataSet = false;
}

void OculusVRSensorData::setData(const OVR::SensorFusion& data, const F32& maxAxisRadius)
{
   // Sensor rotation
   OVR::Quatf orientation;
   if(data.GetPredictionDelta() > 0)
   {
      orientation = data.GetPredictedOrientation();
   }
   else
   {
      orientation = data.GetOrientation();
   }
   OVR::Matrix4f orientMat(orientation);
   OculusVRUtil::convertRotation(orientMat.M, mRot);
   mRotQuat.set(mRot);

   // Sensor rotation in Euler format
   OculusVRUtil::convertRotation(orientation, mRotEuler);

   // Sensor rotation as axis
   OculusVRUtil::calculateAxisRotation(mRot, maxAxisRadius, mRotAxis);

   mDataSet = true;
}

void OculusVRSensorData::simulateData(const F32& maxAxisRadius)
{
   // Sensor rotation
   mRot.identity();
   mRotQuat.identity();
   mRotEuler.zero();

   // Sensor rotation as axis
   OculusVRUtil::calculateAxisRotation(mRot, maxAxisRadius, mRotAxis);

   mDataSet = true;
}

U32 OculusVRSensorData::compare(OculusVRSensorData* other)
{
   S32 result = DIFF_NONE;

   // Check rotation
   if(mRotEuler.x != other->mRotEuler.x || mRotEuler.y != other->mRotEuler.y || mRotEuler.z != other->mRotEuler.z || !mDataSet)
   {
      result |= DIFF_ROT;
   }

   // Check rotation as axis
   if(mRotAxis.x != other->mRotAxis.x || !mDataSet)
   {
      result |= DIFF_ROTAXISX;
   }
   if(mRotAxis.y != other->mRotAxis.y || !mDataSet)
   {
      result |= DIFF_ROTAXISY;
   }

   return result;
}
