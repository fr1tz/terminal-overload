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

#include "platform/platform.h"
#include "gfx/gl/gfxGLVertexBuffer.h"

#include "gfx/gl/gfxGLDevice.h"
#include "gfx/gl/gfxGLEnumTranslate.h"
#include "gfx/gl/gfxGLUtils.h"
#include "gfx/gl/gfxGLVertexAttribLocation.h"


GFXGLVertexBuffer::GFXGLVertexBuffer(  GFXDevice *device, 
                                       U32 numVerts, 
                                       const GFXVertexFormat *vertexFormat, 
                                       U32 vertexSize, 
                                       GFXBufferType bufferType )
   :  GFXVertexBuffer( device, numVerts, vertexFormat, vertexSize, bufferType ), 
      mZombieCache(NULL),
      mFrameAllocatorMark(0),
      mFrameAllocatorPtr(NULL),
      mVertexAttribActiveMask(0)
{
   // Generate a buffer
   mDivisor = 0;
   glGenBuffers(1, &mBuffer);

   //and allocate the needed memory
   PRESERVE_VERTEX_BUFFER();
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
   glBufferData(GL_ARRAY_BUFFER, numVerts * vertexSize, NULL, GFXGLBufferType[bufferType]);
   
   _initVerticesFormat();
}

GFXGLVertexBuffer::~GFXGLVertexBuffer()
{
	// While heavy handed, this does delete the buffer and frees the associated memory.
   glDeleteBuffers(1, &mBuffer);

   if( mZombieCache )
      delete [] mZombieCache;
}

void GFXGLVertexBuffer::lock( U32 vertexStart, U32 vertexEnd, void **vertexPtr )
{
   PROFILE_SCOPE(GFXGLVertexBuffer_lock);

   AssertFatal(!mFrameAllocatorMark && !mFrameAllocatorPtr, "");
   mFrameAllocatorMark = FrameAllocator::getWaterMark();
   mFrameAllocatorPtr = (U8*)FrameAllocator::alloc( mNumVerts * mVertexSize );
#if TORQUE_DEBUG
   mFrameAllocatorMarkGuard = FrameAllocator::getWaterMark();
#endif

   lockedVertexPtr = (void*)(mFrameAllocatorPtr + (vertexStart * mVertexSize));
   *vertexPtr = lockedVertexPtr;

	lockedVertexStart = vertexStart;
	lockedVertexEnd   = vertexEnd;
}

void GFXGLVertexBuffer::unlock()
{
   PROFILE_SCOPE(GFXGLVertexBuffer_unlock);

   U32 offset = lockedVertexStart * mVertexSize;
   U32 length = (lockedVertexEnd - lockedVertexStart) * mVertexSize;
   
   PRESERVE_VERTEX_BUFFER();
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
   glBufferSubData(GL_ARRAY_BUFFER, offset, length, mFrameAllocatorPtr + offset );   

   lockedVertexStart = 0;
	lockedVertexEnd   = 0;
   lockedVertexPtr = NULL;

#if TORQUE_DEBUG
   AssertFatal(mFrameAllocatorMarkGuard == FrameAllocator::getWaterMark(), "");
#endif
   FrameAllocator::setWaterMark(mFrameAllocatorMark);
   mFrameAllocatorMark = 0;
   mFrameAllocatorPtr = NULL;
}

void GFXGLVertexBuffer::prepare()
{
   PROFILE_SCOPE(GFXGLVertexBuffer_prepare);

	// Bind the buffer...
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
   GFXGL->getOpenglCache()->setCacheBinded(GL_ARRAY_BUFFER, mBuffer);

   // Loop thru the vertex format elements adding the array state...   
   for ( U32 i=0; i < glVerticesFormat.size(); i++ )
   {
      // glEnableVertexAttribArray are called and cache in GFXGLDevice::preDrawPrimitive

      glVertexDecl &e = glVerticesFormat[i];
      
      glVertexAttribPointer(
         e.attrIndex,      // attribute
         e.elementCount,   // number of elements per vertex, here (r,g,b)
         e.type,           // the type of each element
         e.normalized,     // take our values as-is
         e.stride,         // stride between each position
         e.pointerFirst    // offset of first element
      );
      glVertexAttribDivisor( e.attrIndex, mDivisor );
   }
}

void GFXGLVertexBuffer::finish()
{
   // glDisableVertexAttribArray are called and cache in GFXGLDevice::preDrawPrimitive
}

GLvoid* GFXGLVertexBuffer::getBuffer()
{
	// NULL specifies no offset into the hardware buffer
	return (GLvoid*)NULL;
}

void GFXGLVertexBuffer::zombify()
{
   if(mZombieCache || !mBuffer)
      return;
      
   mZombieCache = new U8[mNumVerts * mVertexSize];
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
   glGetBufferSubData(GL_ARRAY_BUFFER, 0, mNumVerts * mVertexSize, mZombieCache);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glDeleteBuffers(1, &mBuffer);
   mBuffer = 0;
}

void GFXGLVertexBuffer::resurrect()
{
   if(!mZombieCache)
      return;
   
   glGenBuffers(1, &mBuffer);
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
   glBufferData(GL_ARRAY_BUFFER, mNumVerts * mVertexSize, mZombieCache, GFXGLBufferType[mBufferType]);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   
   delete[] mZombieCache;
   mZombieCache = NULL;
}

void GFXGLVertexBuffer::_initVerticesFormat()
{
   U8* buffer = (U8*)getBuffer();

   // Loop thru the vertex format elements adding the array state...
   U32 texCoordIndex = 0;
   for ( U32 i=0; i < mVertexFormat.getElementCount(); i++ )
   {
      const GFXVertexElement &element = mVertexFormat.getElement( i );
      glVerticesFormat.increment();
      glVertexDecl &glElement = glVerticesFormat.last();

      if ( element.isSemantic( GFXSemantic::POSITION ) )
      {           
         glElement.attrIndex = Torque::GL_VertexAttrib_Position;
         glElement.elementCount = element.getSizeInBytes() / 4;
         glElement.normalized = false;
         glElement.type = GL_FLOAT;
         glElement.stride = mVertexSize;
         glElement.pointerFirst = buffer;

         buffer += element.getSizeInBytes();
      }
      else if ( element.isSemantic( GFXSemantic::NORMAL ) )
      {
         glElement.attrIndex = Torque::GL_VertexAttrib_Normal;
         glElement.elementCount = 3;
         glElement.normalized = false;
         glElement.type = GL_FLOAT;
         glElement.stride = mVertexSize;
         glElement.pointerFirst = buffer;

         buffer += element.getSizeInBytes();
      }
      else if ( element.isSemantic( GFXSemantic::TANGENT ) )
      {
         glElement.attrIndex = Torque::GL_VertexAttrib_Tangent;
         glElement.elementCount = 3;
         glElement.normalized = false;
         glElement.type = GL_FLOAT;
         glElement.stride = mVertexSize;
         glElement.pointerFirst = buffer;

         buffer += element.getSizeInBytes();
      }
      else if ( element.isSemantic( GFXSemantic::TANGENTW ) )
      {
         glElement.attrIndex = Torque::GL_VertexAttrib_TangentW;
         glElement.elementCount = 3;
         glElement.normalized = false;
         glElement.type = GL_FLOAT;
         glElement.stride = mVertexSize;
         glElement.pointerFirst = buffer;

         buffer += element.getSizeInBytes();
      }
      else if ( element.isSemantic( GFXSemantic::BINORMAL ) )
      {
         glElement.attrIndex = Torque::GL_VertexAttrib_Binormal;
         glElement.elementCount = 3;
         glElement.normalized = false;
         glElement.type = GL_FLOAT;
         glElement.stride = mVertexSize;
         glElement.pointerFirst = buffer;

         buffer += element.getSizeInBytes();
      }
      else if ( element.isSemantic( GFXSemantic::COLOR ) )
      {
         glElement.attrIndex = Torque::GL_VertexAttrib_Color;
         glElement.elementCount = element.getSizeInBytes();
         glElement.normalized = true;
         glElement.type = GL_UNSIGNED_BYTE;
         glElement.stride = mVertexSize;
         glElement.pointerFirst = buffer;

         buffer += element.getSizeInBytes();
      }
      else // Everything else is a texture coordinate.
      {
         String name = element.getSemantic();
         glElement.elementCount = element.getSizeInBytes() / 4;
         texCoordIndex = getMax(texCoordIndex, element.getSemanticIndex());
         glElement.attrIndex = Torque::GL_VertexAttrib_TexCoord0 + texCoordIndex;
            
         glElement.normalized = false;
         glElement.type = GL_FLOAT;
         glElement.stride = mVertexSize;
         glElement.pointerFirst = buffer;

         buffer += element.getSizeInBytes();
         ++texCoordIndex;
      }

      AssertFatal(!( mVertexAttribActiveMask & BIT(glElement.attrIndex) ), "GFXGLVertexBuffer::_initVerticesFormat - Duplicate vertex attrib index");
      mVertexAttribActiveMask |= BIT(glElement.attrIndex);
   }

   AssertFatal(mVertexSize == (U8)buffer, "");
}
