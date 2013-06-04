// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/util/byteBuffer.h"


namespace Torque
{

class PrivateBBData
{
public:
   PrivateBBData()
      :  refCount( 1 ),
         dataSize( 0 ),
         data( NULL )
   {
   }

   U32   refCount;   ///< Reference count
   U32   dataSize;   ///< Length of buffer
   U8    *data;      ///< Our data buffer
};

//--------------------------------------

ByteBuffer::ByteBuffer()
{
   _data = new PrivateBBData;
   _data->dataSize = 0;
   _data->data = NULL;
}

ByteBuffer::ByteBuffer(U8 *dataPtr, U32 bufferSize)
{
   _data = new PrivateBBData;
   _data->dataSize = bufferSize;
   _data->data = new U8[bufferSize];

   dMemcpy( _data->data, dataPtr, bufferSize );
}

ByteBuffer::ByteBuffer(U32 bufferSize)
{
   _data = new PrivateBBData;
   _data->dataSize = bufferSize;
   _data->data = new U8[bufferSize];
}

ByteBuffer::ByteBuffer(const ByteBuffer &theBuffer)
{
   _data = theBuffer._data;
   _data->refCount++;
}

ByteBuffer  &ByteBuffer::operator=(const ByteBuffer &theBuffer)
{
   _data = theBuffer._data;
   _data->refCount++;

   return *this;
}

ByteBuffer::~ByteBuffer()
{
   if (!--_data->refCount)
   {
      delete [] _data->data;
      delete _data;

      _data = NULL;
   }
}

void ByteBuffer::setBuffer(U8 *dataPtr, U32 bufferSize, bool copyData)
{
   U8 *newData = dataPtr;

   if ( copyData )
   {
      newData = new U8[bufferSize];

      dMemcpy( newData, dataPtr, bufferSize );
   }

   delete [] _data->data;

   _data->data = newData;
   _data->dataSize = bufferSize;
}

void ByteBuffer::resize(U32 newBufferSize)
{
   U8    *newData = new U8[newBufferSize];

   U32   copyLen = getMin( newBufferSize, _data->dataSize );
   
   dMemcpy( newData, _data->data, copyLen );

   delete [] _data->data;

   _data->data = newData;
   _data->dataSize = newBufferSize;
}

void ByteBuffer::appendBuffer(const U8 *dataBuffer, U32 bufferSize)
{
   U32 start = _data->dataSize;
   resize(start + bufferSize);
   dMemcpy(_data->data + start, dataBuffer, bufferSize);
}

U32 ByteBuffer::getBufferSize() const
{
   return _data->dataSize;
}

U8 *ByteBuffer::getBuffer()
{
   return _data->data;
}

const U8 *ByteBuffer::getBuffer() const
{
   return _data->data;
}

ByteBuffer  ByteBuffer::getCopy() const
{
   return ByteBuffer( _data->data, _data->dataSize );
}

void ByteBuffer::clear()
{
   dMemset(_data->data, 0, _data->dataSize);
}


}
