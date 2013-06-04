// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _IDISPLAYDEVICE_H_
#define _IDISPLAYDEVICE_H_

#include "console/consoleTypes.h"

// Defines a custom display device that requires particular rendering settings
// in order for a scene to display correctly.

class IDisplayDevice
{
public:
   virtual bool providesYFOV() const = 0;
   virtual F32 getYFOV() const = 0;

   virtual bool providesEyeOffset() const = 0;
   virtual const Point3F& getEyeOffset() const = 0;

   virtual bool providesProjectionOffset() const = 0;
   virtual const Point2F& getProjectionOffset() const = 0;
};

#endif   // _IDISPLAYDEVICE_H_
