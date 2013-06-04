// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "windowManager/platformWindow.h"
#include "gfx/gl/gfxGLDevice.h"
#include "gfx/gl/gfxGLWindowTarget.h"
#include "gfx/gl/gfxGLTextureObject.h"
#include "gfx/gl/gfxGLUtils.h"

GFXGLWindowTarget::GFXGLWindowTarget(PlatformWindow *win, GFXDevice *d)
      : GFXWindowTarget(win), mDevice(d), mContext(NULL), mFullscreenContext(NULL)
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

   PRESERVE_FRAMEBUFFER();
   
   GLuint dest;
   
   glGenFramebuffersEXT(1, &dest);
   
   glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, dest);
   glFramebufferTexture2DEXT(GL_DRAW_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, glTexture->getHandle(), 0);
   
   glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, 0);
   
   glBlitFramebufferEXT(0, 0, getSize().x, getSize().y,
      0, 0, glTexture->getWidth(), glTexture->getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
   
   glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
   
   glDeleteFramebuffersEXT(1, &dest);
}
