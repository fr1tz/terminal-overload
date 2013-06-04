// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "lighting/lightingInterfaces.h"


void AvailableSLInterfaces::registerSystem(SceneLightingInterface* si)
{   
   mAvailableSystemInterfaces.push_back(si);
   mDirty = true;
}

void AvailableSLInterfaces::initInterfaces()
{
   if ( !mDirty )
      return;

   mAvailableObjectTypes = mClippingMask = mZoneLightSkipMask = 0;

   SceneLightingInterface** sitr = mAvailableSystemInterfaces.begin();
   for ( ; sitr != mAvailableSystemInterfaces.end(); sitr++ )
   {
      SceneLightingInterface* si = (*sitr);
      si->init();
      mAvailableObjectTypes |= si->addObjectType();
      mClippingMask |= si->addToClippingMask();
      mZoneLightSkipMask |= si->addToZoneLightSkipMask();
   }

   mDirty = false;
}