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
      mZombieCache(NULL)
{
   PRESERVE_VERTEX_BUFFER();
	// Generate a buffer and allocate the needed memory.
	glGenBuffers(1, &mBuffer);
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
   PRESERVE_VERTEX_BUFFER();
	// Bind us, get a pointer into the buffer, then
	// offset it by vertexStart so we act like the D3D layer.
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
   glBufferData(GL_ARRAY_BUFFER, mNumVerts * mVertexSize, NULL, GFXGLBufferType[mBufferType]);
	*vertexPtr = (void*)((U8*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY) + (vertexStart * mVertexSize));
	lockedVertexStart = vertexStart;
	lockedVertexEnd   = vertexEnd;
}

void GFXGLVertexBuffer::unlock()
{
   PRESERVE_VERTEX_BUFFER();
	// Unmap the buffer and bind 0 to GL_ARRAY_BUFFER
   glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
	bool res = glUnmapBuffer(GL_ARRAY_BUFFER);
   AssertFatal(res, "GFXGLVertexBuffer::unlock - shouldn't fail!");

   lockedVertexStart = 0;
	lockedVertexEnd   = 0;
}

void GFXGLVertexBuffer::prepare()
{
	// Bind the buffer...
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

   // Loop thru the vertex format elements adding the array state...   
   for ( U32 i=0; i < glVerticesFormat.size(); i++ )
   {
      auto &e = glVerticesFormat[i];
      AssertFatal(e.attrIndex != -1, "");
      glEnableVertexAttribArray(e.attrIndex);
      glVertexAttribPointer(
         e.attrIndex,      // attribute
         e.elementCount,   // number of elements per vertex, here (r,g,b)
         e.type,           // the type of each element
         e.normalized,     // take our values as-is
         e.stride,         // no extra data between each position
         e.pointerFirst    // offset of first element
      );
   }
}

void GFXGLVertexBuffer::finish()
{
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   
   // Loop thru the vertex format elements adding the array state...   
   for ( U32 i=0; i < glVerticesFormat.size(); i++ )
   {
      auto &e = glVerticesFormat[i];
      AssertFatal(e.attrIndex != -1, "");
      glDisableVertexAttribArray(e.attrIndex);
   }
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
      auto &glElement = glVerticesFormat.last();

      if ( element.isSemantic( GFXSemantic::POSITION ) )
      {           
         glElement.attrIndex = Torque::GL_VertexAttrib_Position;
         if(glElement.attrIndex == -1)
         {
            glVerticesFormat.pop_back();
            buffer += element.getSizeInBytes();
            continue;
         }
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
         if(glElement.attrIndex == -1)     
         {
            glVerticesFormat.pop_back();
            buffer += element.getSizeInBytes();
            continue;
         }
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
         if(glElement.attrIndex == -1)     
         {
            glVerticesFormat.pop_back();
            buffer += element.getSizeInBytes();
            continue;
         }
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
         if(glElement.attrIndex == -1)     
         {
            glVerticesFormat.pop_back();
            buffer += element.getSizeInBytes();
            continue;
         }
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
         if(glElement.attrIndex == -1)     
         {
            glVerticesFormat.pop_back();
            buffer += element.getSizeInBytes();
            continue;
         }
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
         if(glElement.attrIndex == -1)     
         {
            glVerticesFormat.pop_back();
            buffer += element.getSizeInBytes();
            continue;
         }
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
         glElement.attrIndex = Torque::GL_VertexAttrib_TexCoord0 + texCoordIndex;
         if(glElement.attrIndex == -1)     
         {
            glVerticesFormat.pop_back();
            buffer += element.getSizeInBytes();
            continue;
         }
            
         glElement.normalized = false;
         glElement.type = GL_FLOAT;
         glElement.stride = mVertexSize;
         glElement.pointerFirst = buffer;

         buffer += element.getSizeInBytes();
         ++texCoordIndex;
      }
   }
}
