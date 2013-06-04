// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXD3DTEXTUREMANAGER_H_
#define _GFXD3DTEXTUREMANAGER_H_

#include "gfx/D3D9/gfxD3D9TextureObject.h"
#include "core/util/safeRelease.h"

// #define D3D_TEXTURE_SPEW


//*****************************************************************************
// GFX D3D Texture Manager
//*****************************************************************************
class GFXD3D9TextureManager : public GFXTextureManager 
{
   friend class GFXD3D9TextureObject;

   U32 mAdapterIndex;

public:
   GFXD3D9TextureManager( LPDIRECT3DDEVICE9 d3ddevice, U32 adapterIndex );
   virtual ~GFXD3D9TextureManager();

protected:

   // GFXTextureManager
   GFXTextureObject *_createTextureObject(   U32 height, 
                                             U32 width,
                                             U32 depth,
                                             GFXFormat format,
                                             GFXTextureProfile *profile,
                                             U32 numMipLevels,
                                             bool forceMips = false,
                                             S32 antialiasLevel = 0,
                                             GFXTextureObject *inTex = NULL );
   bool _loadTexture(GFXTextureObject *texture, DDSFile *dds);
   bool _loadTexture(GFXTextureObject *texture, GBitmap *bmp);
   bool _loadTexture(GFXTextureObject *texture, void *raw);
   bool _refreshTexture(GFXTextureObject *texture);
   bool _freeTexture(GFXTextureObject *texture, bool zombify = false);

private:
   U32 mCurTexSet[TEXTURE_STAGE_COUNT];

   LPDIRECT3DDEVICE9 mD3DDevice;
   D3DCAPS9 mDeviceCaps;

   void _innerCreateTexture(GFXD3D9TextureObject *obj, U32 height, U32 width, 
      U32 depth, GFXFormat format, GFXTextureProfile *profile, U32 numMipLevels, 
      bool forceMips = false, S32 antialiasLevel = 0);
};

#endif
