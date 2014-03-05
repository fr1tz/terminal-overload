// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "windowManager/platformWindow.h"
#include "gfx/gl/gfxGLDevice.h"
#include "gfx/gl/gfxGLWindowTarget.h"
#include "gfx/gl/gfxGLTextureObject.h"
#include "gfx/gl/gfxGLUtils.h"
#include "postFx/postEffect.h"

GFX_ImplementTextureProfile( BackBufferDepthProfile,
                             GFXTextureProfile::DiffuseMap,
                             GFXTextureProfile::PreserveSize |
                             GFXTextureProfile::NoMipmap |
                             GFXTextureProfile::ZTarget |
                             GFXTextureProfile::Pooled,
                             GFXTextureProfile::NONE );

GFXGLWindowTarget::GFXGLWindowTarget(PlatformWindow *win, GFXDevice *d)
      : GFXWindowTarget(win), mDevice(d), mContext(NULL), mFullscreenContext(NULL)
      , mCopyFBO(0), mBackBufferFBO(0)
{      
   win->appEvent.notify(this, &GFXGLWindowTarget::_onAppSignal);
}

void GFXGLWindowTarget::resetMode()
{
   if(mWindow->getVideoMode().fullScreen != mWindow->isFullscreen())
   {
      _teardownCurrentMode();
      _setupNewMode();
   }
}

void GFXGLWindowTarget::_onAppSignal(WindowId wnd, S32 event)
{
   if(event != WindowHidden)
      return;
      
   // TODO: Investigate this further.
   // Opening and then closing the console results in framerate dropping at an alarming rate down to 3-4 FPS and then
   // rebounding to it's usual level.  Clearing all the volatile VBs prevents this behavior, but I can't explain why.
   // My fear is there is something fundamentally wrong with how we share objects between contexts and this is simply 
   // masking the issue for the most common case.
   static_cast<GFXGLDevice*>(mDevice)->mVolatileVBs.clear();
}

void GFXGLWindowTarget::resolveTo(GFXTextureObject* obj)
{
   AssertFatal(dynamic_cast<GFXGLTextureObject*>(obj), "GFXGLTextureTarget::resolveTo - Incorrect type of texture, expected a GFXGLTextureObject");
   GFXGLTextureObject* glTexture = static_cast<GFXGLTextureObject*>(obj);

   if( gglHasExtension(ARB_copy_image) )
   {
      if(mBackBufferColorTex.getWidth() == glTexture->getWidth()
         && mBackBufferColorTex.getHeight() == glTexture->getHeight()
         && mBackBufferColorTex.getFormat() == glTexture->getFormat())
      {
         glCopyImageSubData(
           static_cast<GFXGLTextureObject*>(mBackBufferColorTex.getPointer())->getHandle(), GL_TEXTURE_2D, 0, 0, 0, 0,
           glTexture->getHandle(), GL_TEXTURE_2D, 0, 0, 0, 0,
           getSize().x, getSize().y, 1);
         return;
      }
   }

   PRESERVE_FRAMEBUFFER();

   if(!mCopyFBO)
   {
      glGenFramebuffersEXT(1, &mCopyFBO);
   }
   
   glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, mCopyFBO);
   glFramebufferTexture2DEXT(GL_DRAW_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, glTexture->getHandle(), 0);
   
   glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, mBackBufferFBO);
   
   glBlitFramebufferEXT(0, 0, getSize().x, getSize().y,
      0, 0, glTexture->getWidth(), glTexture->getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

inline void GFXGLWindowTarget::_setupAttachments()
{
   glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, mBackBufferFBO);
   const Point2I dstSize = getSize();
   mBackBufferColorTex.set(dstSize.x, dstSize.y, getFormat(), &PostFxTargetProfile, "backBuffer");
   GFXGLTextureObject *color = static_cast<GFXGLTextureObject*>(mBackBufferColorTex.getPointer());
   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, color->getHandle(), 0);
   mBackBufferDepthTex.set(dstSize.x, dstSize.y, GFXFormatD24S8, &BackBufferDepthProfile, "backBuffer");
   GFXGLTextureObject *depth = static_cast<GFXGLTextureObject*>(mBackBufferDepthTex.getPointer());
   glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depth->getHandle(), 0);
}

void GFXGLWindowTarget::makeActive()
{
   if(mBackBufferFBO)
   {
      glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, mBackBufferFBO);
   }
   else
   {
      glGenFramebuffersEXT(1, &mBackBufferFBO);
      _setupAttachments();
      CHECK_FRAMEBUFFER_STATUS();
   }
}

bool GFXGLWindowTarget::present()
{
    PRESERVE_FRAMEBUFFER();

   const Point2I srcSize = mBackBufferColorTex.getWidthHeight();
   const Point2I dstSize = getSize();

   glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
   glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, mBackBufferFBO);

   // OpenGL render upside down for make render more similar to DX.
   // Final screen are corrected here
   glBlitFramebufferEXT(
      0, 0, srcSize.x, srcSize.y,
      0, dstSize.y, dstSize.x, 0, // Y inverted
      GL_COLOR_BUFFER_BIT, GL_NEAREST);

   _WindowPresent();

   if(srcSize != dstSize || mBackBufferDepthTex.getWidthHeight() != dstSize)
      _setupAttachments();

   return true;
}
