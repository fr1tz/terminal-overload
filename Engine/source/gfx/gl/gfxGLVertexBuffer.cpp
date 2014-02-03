// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

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
   // Generate a buffer
   glGenBuffers(1, &mBuffer);
   mBufferData.setSize(mNumVerts * mVertexSize);

   //and allocate the needed memory
   if( gglHasExtension(EXT_direct_state_access) )
   {      
      glNamedBufferDataEXT(mBuffer, mNumVerts * mVertexSize, NULL, GFXGLBufferType[mBufferType]);    
   }
   else
   {
      PRESERVE_VERTEX_BUFFER();
	    
	   glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
	   glBufferData(GL_ARRAY_BUFFER, numVerts * vertexSize, NULL, GFXGLBufferType[bufferType]);
   }
   
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
   lockedVertexPtr = (void*)((U8*)mBufferData.address() + (vertexStart * mVertexSize));
   *vertexPtr = lockedVertexPtr;

	lockedVertexStart = vertexStart;
	lockedVertexEnd   = vertexEnd;
}

void GFXGLVertexBuffer::unlock()
{
   PROFILE_SCOPE(GFXGLVertexBuffer_unlock);

   U32 offset = lockedVertexStart * mVertexSize;
   U32 length = (lockedVertexEnd - lockedVertexStart) * mVertexSize;

   if( gglHasExtension(EXT_direct_state_access) )
   {
      if(lockedVertexStart == 0 && lockedVertexEnd == 0)      
         glNamedBufferDataEXT(mBuffer, length, mBufferData.address(), GFXGLBufferType[mBufferType] );      
      else
         glNamedBufferSubDataEXT(mBuffer, offset, length, mBufferData.address() + offset );
   }
   else
   {
      PRESERVE_VERTEX_BUFFER();
      glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
      glBufferSubData(GL_ARRAY_BUFFER, offset, length, mBufferData.address() + offset );
   }

   lockedVertexStart = 0;
	lockedVertexEnd   = 0;
   lockedVertexPtr = NULL;
}

void GFXGLVertexBuffer::prepare()
{
   PROFILE_SCOPE(GFXGLVertexBuffer_prepare);

	// Bind the buffer...
	glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

   // Loop thru the vertex format elements adding the array state...   
   for ( U32 i=0; i < glVerticesFormat.size(); i++ )
   {
      glVertexDecl &e = glVerticesFormat[i];
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
   PROFILE_SCOPE(GFXGLVertexBuffer_finish);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   for ( U32 i=0; i < glVerticesFormat.size(); i++ )
      glDisableVertexAttribArray(glVerticesFormat[i].attrIndex);
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
