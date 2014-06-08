// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef ALDEVICELIST_H
#define ALDEVICELIST_H

#pragma warning(disable: 4786)  //disable warning "identifier was truncated to '255' characters in the browser information"
#include "core/util/tVector.h"
#include "core/stringTable.h"
#include "sfx/openal/sfxALCaps.h"
#include "LoadOAL.h"

typedef struct
{
	char           strDeviceName[256];
	S32				iMajorVersion;
	S32				iMinorVersion;
   U32	uiSourceCount;
	S32 iCapsFlags;
	bool			bSelected;
} ALDEVICEINFO, *LPALDEVICEINFO;

class ALDeviceList
{
private:
	OPENALFNTABLE	ALFunction;
	Vector<ALDEVICEINFO> vDeviceInfo;
	S32 defaultDeviceIndex;
	S32 filterIndex;

public:
	ALDeviceList ( const OPENALFNTABLE &oalft );
	~ALDeviceList ();
	S32 GetNumDevices();
	const char *GetDeviceName(S32 index);
	void GetDeviceVersion(S32 index, S32 *major, S32 *minor);
   U32 GetMaxNumSources(S32 index);
	bool IsExtensionSupported(S32 index, SFXALCaps caps);
	S32 GetDefaultDevice();
	void FilterDevicesMinVer(S32 major, S32 minor);
	void FilterDevicesMaxVer(S32 major, S32 minor);
	void FilterDevicesExtension(SFXALCaps caps);
	void ResetFilters();
	S32 GetFirstFilteredDevice();
	S32 GetNextFilteredDevice();

private:
	U32 GetMaxNumSources();
};

#endif // ALDEVICELIST_H
