// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _TORQUE_PLATFORM_PLATFORMCPUCOUNT_H_
#define _TORQUE_PLATFORM_PLATFORMCPUCOUNT_H_

#include "platform/platform.h"

namespace CPUInfo
{
   enum EConfig
   {
      CONFIG_UserConfigIssue,
      CONFIG_SingleCoreHTEnabled,
      CONFIG_SingleCoreHTDisabled,
      CONFIG_SingleCoreAndHTNotCapable,
      CONFIG_MultiCoreAndHTNotCapable,
      CONFIG_MultiCoreAndHTEnabled,
      CONFIG_MultiCoreAndHTDisabled,
   };

   inline bool isMultiCore( EConfig config )
   {
      switch( config )
      {
      case CONFIG_MultiCoreAndHTNotCapable:
      case CONFIG_MultiCoreAndHTEnabled:
      case CONFIG_MultiCoreAndHTDisabled:
         return true;

      default:
         return false;
      }
   }

   inline bool isHyperThreaded( EConfig config )
   {
      switch( config )
      {
      case CONFIG_SingleCoreHTEnabled:
      case CONFIG_MultiCoreAndHTEnabled:
         return true;

      default:
         return false;
      }
   }

   EConfig CPUCount( U32& totalAvailableLogical,
      U32& totalAvailableCores,
      U32& numPhysical );

} // namespace CPUInfo

#endif // _TORQUE_PLATFORM_PLATFORMCOUNT_H_

