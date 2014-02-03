// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _OCULUSVRSENSORDEVICE_H_
#define _OCULUSVRSENSORDEVICE_H_

#include "core/util/str.h"
#include "math/mQuat.h"
#include "math/mPoint2.h"
#include "math/mPoint3.h"
#include "math/mPoint4.h"
#include "platform/input/oculusVR/oculusVRConstants.h"
#include "platform/types.h"
#include "OVR.h"

struct OculusVRSensorData;

class OculusVRSensorDevice
{
public:
   enum SimulationTypes {
      ST_RIFT_PREVIEW,
   };

public:
   // Action codes
   static U32 OVR_SENSORROT[OculusVRConstants::MaxSensors];       // SI_ROT

   static U32 OVR_SENSORROTANG[OculusVRConstants::MaxSensors];    // SI_POS but is EulerF

   static U32 OVR_SENSORROTAXISX[OculusVRConstants::MaxSensors];  // SI_AXIS
   static U32 OVR_SENSORROTAXISY[OculusVRConstants::MaxSensors];

   static U32 OVR_SENSORACCELERATION[OculusVRConstants::MaxSensors];    // SI_POS
   static U32 OVR_SENSORANGVEL[OculusVRConstants::MaxSensors];          // SI_POS but is EulerF
   static U32 OVR_SENSORMAGNETOMETER[OculusVRConstants::MaxSensors];    // SI_POS

protected:
   bool mIsValid;

   bool mIsSimulation;

   OVR::SensorDevice* mDevice;

   OVR::SensorFusion mSensorFusion;

   // From OVR::DeviceInfo
   String   mProductName;
   String   mManufacturer;
   U32      mVersion;

   // From OVR::SensorInfo
   U16      mVendorId;
   U16      mProductId;
   String   mSerialNumber;

   // Has yaw correction been disabled by the control panel
   bool     mYawCorrectionDisabled;

   // Assigned by the OculusVRDevice
   S32 mActionCodeIndex;

   // Buffers to store data for sensor
   OculusVRSensorData* mDataBuffer[2];

   // Points to the buffer that holds the previously collected data
   // for the sensor
   OculusVRSensorData* mPrevData;

protected:
   void createSimulatedPreviewRift(S32 actionCodeIndex);

public:
   OculusVRSensorDevice();
   virtual ~OculusVRSensorDevice();

   static void buildCodeTable();

   void cleanUp();

   // Set the sensor properties based on information from the OVR device
   void set(OVR::SensorDevice* sensor, OVR::SensorInfo& info, S32 actionCodeIndex);

   // Set the sensor properties based on a simulation of the given type
   void createSimulation(SimulationTypes simulationType, S32 actionCodeIndex);

   bool isValid() const {return mIsValid;}
   bool isSimulated() {return mIsSimulation;}

   bool process(U32 deviceType, bool generateRotAsAngAxis, bool generateRotAsEuler, bool generateRotationAsAxisEvents, F32 maxAxisRadius, bool generateRawSensor);

   void reset();

   // Get the prediction time for the sensor fusion.  The time is in seconds.
   F32 getPredictionTime() const;

   // Set the prediction time for the sensor fusion.  The time is in seconds.
   void setPredictionTime(F32 dt);

   // Is gravity correction enabled for pitch and roll
   bool getGravityCorrection() const;

   // Set the pitch and roll gravity correction
   void setGravityCorrection(bool state);

   // Has yaw correction been disabled using the control panel
   bool getYawCorrectionUserDisabled() const { return mYawCorrectionDisabled; }

   // Is yaw correction enabled
   bool getYawCorrection() const;

   // Set the yaw correction. Note: if magnetometer calibration data is not present,
   // or user has disabled yaw correction in the control panel, this method will
   // not enable it.
   void setYawCorrection(bool state);

   // Is magnetometer calibration data available for this sensor
   bool getMagnetometerCalibrationAvailable() const;

   const char* getProductName() { return mProductName.c_str(); }
   const char* getManufacturer() { return mManufacturer.c_str(); }
   U32 getVersion() { return mVersion; }
   U16 getVendorId() { return mVendorId; }
   U16 getProductId() { return mProductId; }
   const char* getSerialNumber() { return mSerialNumber; }

   // Get the current rotation of the sensor.  Uses prediction if set.
   EulerF getEulerRotation();

   // Get the current rotation of the sensor.
   EulerF getRawEulerRotation();

   // Get the current absolute acceleration reading, in m/s^2
   VectorF getAcceleration();

   // Get the current angular velocity reading, in rad/s
   EulerF getAngularVelocity();

   // Get the current magnetometer reading (direction and field strength), in Gauss.
   // Uses magnetometer calibration if set.
   VectorF getMagnetometer();

   // Get the current raw magnetometer reading (direction and field strength), in Gauss
   VectorF getRawMagnetometer();
};

#endif   // _OCULUSVRSENSORDEVICE_H_
