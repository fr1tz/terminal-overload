// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXD3D9CARDPROFILER_H_
#define _GFXD3D9CARDPROFILER_H_


#include "gfx/gfxCardProfile.h"

struct IDirect3DDevice9;
class GFXD3D9CardProfiler : public GFXCardProfiler
{
private:
   typedef GFXCardProfiler Parent;

   IDirect3DDevice9 *mD3DDevice;
   UINT mAdapterOrdinal;

public:
   GFXD3D9CardProfiler(U32 adapterIndex);
   ~GFXD3D9CardProfiler();
   void init();

protected:
   const String &getRendererString() const { static String sRS("D3D9"); return sRS; }

   void setupCardCapabilities();
   bool _queryCardCap(const String &query, U32 &foundResult);
   bool _queryFormat(const GFXFormat fmt, const GFXTextureProfile *profile, bool &inOutAutogenMips);
};

#endif
