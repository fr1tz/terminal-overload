//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef TORQUE_GFX_GL_GFXGLUTILS_H_
#define TORQUE_GFX_GL_GFXGLUTILS_H_

#include "core/util/preprocessorHelpers.h"
#include "gfx/gl/gfxGLEnumTranslate.h"

inline U32 getMaxMipmaps(U32 width, U32 height, U32 depth)
{
   return getMax( getBinLog2(depth), getMax(getBinLog2(width), getBinLog2(height)));
}

static inline GLenum minificationFilter(U32 minFilter, U32 mipFilter, U32 /*mipLevels*/)
{
   // the compiler should interpret this as array lookups
   switch( minFilter ) 
   {
      case GFXTextureFilterLinear:
         switch( mipFilter ) 
         {
         case GFXTextureFilterLinear:
            return GL_LINEAR_MIPMAP_LINEAR;
         case GFXTextureFilterPoint:
            return GL_LINEAR_MIPMAP_NEAREST;
         default: 
            return GL_LINEAR;
         }
      default:
         switch( mipFilter ) {
      case GFXTextureFilterLinear:
         return GL_NEAREST_MIPMAP_LINEAR;
      case GFXTextureFilterPoint:
         return GL_NEAREST_MIPMAP_NEAREST;
      default:
         return GL_NEAREST;
         }
   }
}

/// Simple class which preserves a given GL integer.
/// This class determines the integer to preserve on construction and restores 
/// it on destruction.
class GFXGLPreserveInteger
{
public:
   typedef void(STDCALL *BindFn)(GLenum, GLuint);

   /// Preserve the integer.
   /// @param binding The binding which should be set on destruction.
   /// @param getBinding The parameter to be passed to glGetIntegerv to determine
   /// the integer to be preserved.
   /// @param binder The gl function to call to restore the integer.
   GFXGLPreserveInteger(GLenum binding, GLint getBinding, BindFn binder) :
      mBinding(binding), mPreserved(0), mBinder(binder)
   {
      AssertFatal(mBinder, "GFXGLPreserveInteger - Need a valid binder function");
      glGetIntegerv(getBinding, &mPreserved);
   }
   
   /// Restores the integer.
   ~GFXGLPreserveInteger()
   {
      mBinder(mBinding, mPreserved);
   }

private:
   GLenum mBinding;
   GLint mPreserved;
   BindFn mBinder;
};

/// Helper macro to preserve the current VBO binding.
#define PRESERVE_VERTEX_BUFFER() \
GFXGLPreserveInteger TORQUE_CONCAT(preserve_, __LINE__) (GL_ARRAY_BUFFER, GL_ARRAY_BUFFER_BINDING, (GFXGLPreserveInteger::BindFn)glBindBuffer)

/// Helper macro to preserve the current element array binding.
#define PRESERVE_INDEX_BUFFER() \
GFXGLPreserveInteger TORQUE_CONCAT(preserve_, __LINE__) (GL_ELEMENT_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER_BINDING, (GFXGLPreserveInteger::BindFn)glBindBuffer)

/// Helper macro to preserve the current 1D texture binding.
#define PRESERVE_1D_TEXTURE() \
GFXGLPreserveInteger TORQUE_CONCAT(preserve_, __LINE__) (GL_TEXTURE_1D, GL_TEXTURE_BINDING_1D, (GFXGLPreserveInteger::BindFn)glBindTexture)

/// Helper macro to preserve the current 2D texture binding.
#define PRESERVE_2D_TEXTURE() \
GFXGLPreserveInteger TORQUE_CONCAT(preserve_, __LINE__) (GL_TEXTURE_2D, GL_TEXTURE_BINDING_2D, (GFXGLPreserveInteger::BindFn)glBindTexture)

/// Helper macro to preserve the current 3D texture binding.
#define PRESERVE_3D_TEXTURE() \
GFXGLPreserveInteger TORQUE_CONCAT(preserve_, __LINE__) (GL_TEXTURE_3D, GL_TEXTURE_BINDING_3D, (GFXGLPreserveInteger::BindFn)glBindTexture)

#define _GET_TEXTURE_BINDING(binding) \
binding == GL_TEXTURE_2D ? GL_TEXTURE_BINDING_2D : (binding == GL_TEXTURE_3D ?  GL_TEXTURE_BINDING_3D : GL_TEXTURE_BINDING_1D )

#define PRESERVE_TEXTURE(binding) \
GFXGLPreserveInteger TORQUE_CONCAT(preserve_, __LINE__) (binding, _GET_TEXTURE_BINDING(binding), (GFXGLPreserveInteger::BindFn)glBindTexture)

#define PRESERVE_FRAMEBUFFER() \
GFXGLPreserveInteger TORQUE_CONCAT(preserve_, __LINE__) (GL_READ_FRAMEBUFFER_EXT, GL_READ_FRAMEBUFFER_BINDING_EXT, (GFXGLPreserveInteger::BindFn)glBindFramebufferEXT);\
GFXGLPreserveInteger TORQUE_CONCAT(preserve2_, __LINE__) (GL_DRAW_FRAMEBUFFER_EXT, GL_DRAW_FRAMEBUFFER_BINDING_EXT, (GFXGLPreserveInteger::BindFn)glBindFramebufferEXT)

// Handy macro for checking the status of a framebuffer.  Framebuffers can fail in 
// all sorts of interesting ways, these are just the most common.  Further, no existing GL profiling 
// tool catches framebuffer errors when the framebuffer is created, so we actually need this.
#define CHECK_FRAMEBUFFER_STATUS()\
{\
GLenum status;\
status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);\
switch(status) {\
case GL_FRAMEBUFFER_COMPLETE_EXT:\
break;\
case GL_FRAMEBUFFER_UNSUPPORTED_EXT:\
AssertFatal(false, "Unsupported FBO");\
break;\
case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:\
AssertFatal(false, "Incomplete FBO Attachment");\
break;\
case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:\
AssertFatal(false, "Incomplete FBO dimensions");\
break;\
case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:\
AssertFatal(false, "Incomplete FBO formats");\
default:\
/* programming error; will fail on all hardware */\
AssertFatal(false, "Something really bad happened with an FBO");\
}\
}

#endif
