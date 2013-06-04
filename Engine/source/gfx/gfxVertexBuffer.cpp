// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gfx/gfxVertexBuffer.h"

#include "core/strings/stringFunctions.h"
#include "gfx/gfxDevice.h"


void GFXVertexBufferHandleBase::set(   GFXDevice *theDevice,
                                       U32 numVerts, 
                                       const GFXVertexFormat *vertexFormat,
                                       U32 vertexSize, 
                                       GFXBufferType type )
{
   StrongRefPtr<GFXVertexBuffer>::operator=( theDevice->allocVertexBuffer( numVerts, vertexFormat, vertexSize, type ) );
}

const String GFXVertexBuffer::describeSelf() const
{
   const char *bufType;

   switch(mBufferType)
   {
   case GFXBufferTypeStatic:
      bufType = "Static";
      break;
   case GFXBufferTypeDynamic:
      bufType = "Dynamic";
      break;
   case GFXBufferTypeVolatile:
      bufType = "Volatile";
      break;
   default:
      bufType = "Unknown";
      break;
   }

   return String::ToString("numVerts: %i vertSize: %i bufferType: %s", mNumVerts, mVertexSize, bufType);   
}