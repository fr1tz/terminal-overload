// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BYTEBUFFER_H_
#define _BYTEBUFFER_H_

#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif

namespace Torque
{

class PrivateBBData;

class ByteBuffer
{
public:
   ByteBuffer();

   /// Create a ByteBuffer from a chunk of memory.
   ByteBuffer(U8 *dataPtr, U32 bufferSize);

   /// Create a ByteBuffer of the specified size.
   ByteBuffer(U32 bufferSize);

   /// Copy constructor
   ByteBuffer(const ByteBuffer &theBuffer);
   
   ByteBuffer  &operator=(const ByteBuffer &theBuffer);

   ~ByteBuffer();

   /// Set the ByteBuffer to point to a new chunk of memory.
   void setBuffer(U8 *dataPtr, U32 bufferSize, bool copyData);

   /// Resize the buffer.
   void resize(U32 newBufferSize);

   /// Appends the specified buffer to the end of the byte buffer.
   void appendBuffer(const U8 *dataBuffer, U32 bufferSize);

   /// Appends the specified ByteBuffer to the end of this byte buffer.
   void appendBuffer(const ByteBuffer &theBuffer)
   {
      appendBuffer(theBuffer.getBuffer(), theBuffer.getBufferSize());
   }

   U32 getBufferSize() const;

   U8 *getBuffer();
   const U8 *getBuffer() const;

   /// Copy the data in the buffer.
   ByteBuffer  getCopy() const;

   /// Clear the buffer.
   void clear();

private:
   PrivateBBData  *_data;
};

}

#endif
