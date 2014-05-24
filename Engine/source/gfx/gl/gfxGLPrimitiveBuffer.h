// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLPRIMITIVEBUFFER_H_
#define _GFXGLPRIMITIVEBUFFER_H_

#include "gfx/gfxPrimitiveBuffer.h"
#include "gfx/gl/util/glFrameAllocatorLockableHelper.h"

/// This is a primitive buffer (index buffer to GL users) which uses VBOs.
class GFXGLPrimitiveBuffer : public GFXPrimitiveBuffer
{
public:
	GFXGLPrimitiveBuffer(GFXDevice *device, U32 indexCount, U32 primitiveCount, GFXBufferType bufferType);
	~GFXGLPrimitiveBuffer();

	virtual void lock(U32 indexStart, U32 indexEnd, void **indexPtr); ///< only write lock are supported
	virtual void unlock(); ///<
	virtual void prepare();  ///< binds the buffer
   virtual void finish(); ///< We're done with this buffer

	virtual void* getBuffer(); ///< returns NULL

   // GFXResource interface
   virtual void zombify();
   virtual void resurrect();
   
private:
	/// Handle to our GL buffer object
	GLuint mBuffer;
   U32 mBufferOffset;
   U8* mZombieCache;

   U32 lockedIndexEnd, lockedIndexStart;

   FrameAllocatorLockableHelper mFrameAllocator;
};

#endif