// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXGLVERTEXBUFFER_H_
#define _GFXGLVERTEXBUFFER_H_

#ifndef _GFXVERTEXBUFFER_H_
#include "gfx/gfxVertexBuffer.h"
#endif
#ifndef GL_GGL_H
#include "gfx/gl/ggl/ggl.h"
#endif

/// This is a vertex buffer which uses GL_ARB_vertex_buffer_object.
class GFXGLVertexBuffer : public GFXVertexBuffer 
{
public:
	GFXGLVertexBuffer(   GFXDevice *device, 
                        U32 numVerts, 
                        const GFXVertexFormat *vertexFormat, 
                        U32 vertexSize, 
                        GFXBufferType bufferType );

	~GFXGLVertexBuffer();

	virtual void lock(U32 vertexStart, U32 vertexEnd, void **vertexPtr); ///< calls glMapBuffer and offsets the pointer by vertex start
	virtual void unlock(); ///< calls glUnmapBuffer, unbinds the buffer
	virtual void prepare(); ///< Binds the buffer
   virtual void finish(); ///< We're done here

	GLvoid* getBuffer(); ///< returns NULL

   // GFXResource interface
   virtual void zombify();
   virtual void resurrect();
   
private:
   friend class GFXGLDevice;
	/// GL buffer handle
	GLuint mBuffer;
   
   U8* mZombieCache;
};

#endif
