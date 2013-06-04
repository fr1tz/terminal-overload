// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MEMSTREAM_H_
#define _MEMSTREAM_H_

#ifndef _STREAM_H_
#include "core/stream/stream.h"
#endif


/// The MemStream class is used to read and write to a memory buffer.
class MemStream : public Stream
{
   typedef Stream Parent;

   protected:

      /// The amount to grow the buffer when we run out of
      /// space writing to the stream.
      U32 mGrowSize;

      /// The actual size of the memory buffer.  It is always
      /// greater than or equal to the mStreamSize.
      U32 mBufferSize;

      /// The size of the data in the stream. It is always
      /// less than or equal to the mBufferSize.
      U32 mStreamSize;

      /// The memory buffer.
      void *mBufferBase;

      /// If true the memory is owned by the steam and it
      /// will be deleted in the destructor.
      bool mOwnsMemory;

      ///
      U32 mInstCaps;

      /// Our current read/write position within the buffer.
      U32 mCurrentPosition;

   public:

      /// This constructs an empty memory stream that will grow 
      /// in increments as needed.
      MemStream(  U32 growSize,
                  bool allowRead  = true,
                  bool allowWrite = true );

      /// This constructs the stream with a fixed size memory buffer.  If
      /// buffer is null then it will be allocated for you.
      MemStream(  U32 bufferSize,
                  void *buffer,
                  bool allowRead  = true,
                  bool allowWrite = true );

      /// The destructor.
      virtual ~MemStream();

   protected:

      // Stream
      bool _read( const U32 in_numBytes,  void *out_pBuffer );
      bool _write( const U32 in_numBytes, const void *in_pBuffer );

   public:

      // Stream
      bool hasCapability( const Capability caps ) const;
      U32 getPosition() const;
      bool setPosition( const U32 in_newPosition );
      U32 getStreamSize();

      /// Returns the memory buffer.
      void *getBuffer() { return mBufferBase; }
      const void *getBuffer() const { return mBufferBase; }

      /// Takes the memory buffer reseting the stream.
      void *takeBuffer();

};

#endif //_MEMSTREAM_H_
