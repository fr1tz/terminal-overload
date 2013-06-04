// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLCUBEMAP_H_
#define _GFXGLCUBEMAP_H_

#ifndef _GFXCUBEMAP_H_
#include "gfx/gfxCubemap.h"
#endif
#ifndef __RESOURCE_H__
#include "core/resource.h"
#endif


class GFXGLCubemap : public GFXCubemap
{
public:
   GFXGLCubemap();
   virtual ~GFXGLCubemap();

   virtual void initStatic( GFXTexHandle *faces );
   virtual void initStatic( DDSFile *dds );
   virtual void initDynamic( U32 texSize, GFXFormat faceFormat = GFXFormatR8G8B8A8 );
   virtual U32 getSize() const { return mWidth; }
   virtual GFXFormat getFormat() const { return mFaceFormat; }

   // Convenience methods for GFXGLTextureTarget
   U32 getWidth() { return mWidth; }
   U32 getHeight() { return mHeight; }
   U32 getNumMipLevels() { return mMipLevels; }
   U32 getHandle() { return mCubemap; }
   
   // GFXResource interface
   virtual void zombify();
   virtual void resurrect();
   
   /// Called by texCB; this is to ensure that all textures have been resurrected before we attempt to res the cubemap.
   void tmResurrect();
   
   static GLenum getEnumForFaceNumber(U32 face) { return faceList[face]; } ///< Performs lookup to get a GLenum for the given face number

protected:

   friend class GFXDevice;
   friend class GFXGLDevice;

   /// The callback used to get texture events.
   /// @see GFXTextureManager::addEventDelegate
   void _onTextureEvent( GFXTexCallbackCode code );
   
   GLuint mCubemap; ///< Internal GL handle
   U32 mDynamicTexSize; ///< Size of faces for a dynamic texture (used in resurrect)
   
   // Self explanatory
   U32 mWidth;
   U32 mHeight;
   U32 mMipLevels;
   GFXFormat mFaceFormat;
      
   GFXTexHandle mTextures[6]; ///< Keep refs to our textures for resurrection of static cubemaps
   
   /// The backing DDSFile uses to restore the faces
   /// when the surface is lost.
   Resource<DDSFile> mDDSFile;

   // should only be called by GFXDevice
   virtual void setToTexUnit( U32 tuNum ); ///< Binds the cubemap to the given texture unit
   virtual void bind(U32 textureUnit) const; ///< Notifies our owning device that we want to be set to the given texture unit (used for GL internal state tracking)
   void fillCubeTextures(GFXTexHandle* faces); ///< Copies the textures in faces into the cubemap
   
   static GLenum faceList[6]; ///< Lookup table
};

#endif
