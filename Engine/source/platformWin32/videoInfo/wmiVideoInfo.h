// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _WMI_CARDINFO_H_
#define _WMI_CARDINFO_H_

#include "platform/platformVideoInfo.h"

struct IWbemLocator;
struct IWbemServices;

struct IDXGIFactory;
struct IDxDiagProvider;

class WMIVideoInfo : public PlatformVideoInfo
{
private:
   IWbemLocator *mLocator;
   IWbemServices *mServices;
   bool mComInitialized;

   void*             mDXGIModule;
   IDXGIFactory*     mDXGIFactory;
   IDxDiagProvider*  mDxDiagProvider;

   bool _initializeDXGI();
   bool _initializeDxDiag();
   bool _initializeWMI();

   bool _queryPropertyDXGI( const PVIQueryType queryType, const U32 adapterId, String *outValue );
   bool _queryPropertyDxDiag( const PVIQueryType queryType, const U32 adapterId, String *outValue );
   bool _queryPropertyWMI( const PVIQueryType queryType, const U32 adapterId, String *outValue );

protected:
   static WCHAR *smPVIQueryTypeToWMIString [];
   bool _queryProperty( const PVIQueryType queryType, const U32 adapterId, String *outValue );
   bool _initialize();

public:
   WMIVideoInfo();
   ~WMIVideoInfo();
};

#endif