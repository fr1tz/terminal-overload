// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLTEXTUREOBJECT_H
#define _GFXGLTEXTUREOBJECT_H

#include "gfx/gfxTextureObject.h"
#include "gfx/gl/tGL/tGL.h"
#include "gfx/gfxStateBlock.h"

class GFXGLDevice;

class GFXGLTextureObject : public GFXTextureObject 
{
public:
   GFXGLTextureObject(GFXDevice * aDevice, GFXTextureProfile *profile); 
   ~GFXGLTextureObject();
   
   void release();
   void reInit();
   
   inline GLuint getHandle() const { return mHandle; }
   inline GLenum getBinding() const { return mBinding; }
   inline GLuint getBuffer() const { return mBuffer; }
   
   inline bool isZombie() const { return mIsZombie; }

   /// Binds the texture to the given texture unit
   /// and applies the current sampler state because GL tracks
   /// filtering and wrapper per object, while GFX tracks per sampler.
   void bind(U32 textureUnit);
   
   /// @return An array containing the texture data
   /// @note You are responsible for deleting the returned data! (Use delete[])
   U8* getTextureData();

   virtual F32 getMaxUCoord() const;
   virtual F32 getMaxVCoord() const;
   
   void reloadFromCache(); ///< Reloads texture from zombie cache, used by GFXGLTextureManager to resurrect the texture.
   
#ifdef TORQUE_DEBUG
   virtual void pureVirtualCrash() {}
#endif

   /// Get/set data from texture (for dynamic textures and render targets)
   /// @attention DO NOT READ FROM THE RETURNED RECT! It is not guaranteed to work and may incur significant performance penalties.
   virtual GFXLockedRect* lock(U32 mipLevel = 0, RectI *inRect = NULL);
   virtual void unlock(U32 mipLevel = 0 );

   virtual bool copyToBmp(GBitmap *); ///< Not implemented
   
   bool mIsNPoT2;

   // GFXResource interface
   virtual void zombify();
   virtual void resurrect();
   virtual const String describeSelf() const;

   void initSamplerState(const GFXSamplerStateDesc &ssd);
   
private:
   friend class GFXGLTextureManager;
   typedef GFXTextureObject Parent;
   /// Internal GL object
   GLuint mHandle;
   GLuint mBuffer;
   bool mNeedInitSamplerState;
   GFXSamplerStateDesc mSampler;
   GLenum mBinding;
   
   U32 mBytesPerTexel;
   GFXLockedRect mLockedRect;
   RectI mLockedRectRect;

   /// Pointer to owner device
   GFXGLDevice* mGLDevice;
   
   bool mIsZombie;
   U8* mZombieCache;
   
   void copyIntoCache();

   //FrameAllocator
   U32 mFrameAllocatorMark;
#if TORQUE_DEBUG
   U32 mFrameAllocatorMarkGuard;
#endif
   U8 *mFrameAllocatorPtr;
};

#endif