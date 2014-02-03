// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLTEXTUREMANAGER_H
#define _GFXGLTEXTUREMANAGER_H

#include "gfx/gfxDevice.h"
#include "gfx/gfxTextureManager.h"
#include "gfx/gl/gfxGLTextureObject.h"
#include "gfx/gl/tGL/tGL.h"

class GFXGLTextureManager : public GFXTextureManager
{   
public:
   GFXGLTextureManager();
   ~GFXGLTextureManager();
   
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
   friend class GFXGLTextureObject;
   
   /// Creates internal GL texture
   void innerCreateTexture(GFXGLTextureObject *obj, U32 height, U32 width, U32 depth, GFXFormat format, GFXTextureProfile *profile, U32 numMipLevels, bool forceMips = false);
};

#endif