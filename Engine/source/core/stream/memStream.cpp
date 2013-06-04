// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "core/stream/memStream.h"


MemStream::MemStream( U32 growSize,
                      bool allowRead,
                      bool allowWrite )
   :  mGrowSize( growSize ),
      mBufferSize( 0 ),
      mStreamSize( 0 ),
      mBufferBase( NULL ),
      mInstCaps( 0 ),
      mCurrentPosition( 0 )
{
   AssertFatal( allowRead || allowWrite, "Either write or read must be allowed" );

   if ( allowRead )
      mInstCaps |= Stream::StreamRead;
   if ( allowWrite )
      mInstCaps |= Stream::StreamWrite;

   mOwnsMemory = true;
   setStatus( mGrowSize > 0 ? Ok : EOS );
}

MemStream::MemStream( U32 bufferSize,
                      void *buffer,
                      bool allowRead,
                      bool allowWrite)
 : mGrowSize( 0 ),
   mBufferSize( bufferSize ),
   mStreamSize( bufferSize ),
   mBufferBase( buffer ),
   mInstCaps( 0 ),
   mCurrentPosition( 0 ),
   mOwnsMemory( false )
{
   AssertFatal( bufferSize > 0,  "Invalid buffer size");
   AssertFatal( allowRead || allowWrite, "Either write or read must be allowed");

   if ( allowRead )
      mInstCaps |= Stream::StreamRead;
   if ( allowWrite )
      mInstCaps |= Stream::StreamWrite;

   if ( !buffer )
   {
      mOwnsMemory = true;
      mBufferBase = dMalloc( mBufferSize );
   }

   setStatus( Ok );
}

MemStream::~MemStream()
{
   if ( mOwnsMemory )
      dFree( mBufferBase );

   mBufferBase     = NULL;
   mCurrentPosition = 0;

   setStatus( Closed );
}

U32 MemStream::getStreamSize()
{
   AssertFatal( getStatus() != Closed, "Stream not open, size undefined" );

   return mStreamSize;
}

bool MemStream::hasCapability(const Capability in_cap) const
{
   // Closed streams can't do anything
   //
   if (getStatus() == Closed)
      return false;

   U32 totalCaps = U32(Stream::StreamPosition) | mInstCaps;

   return (U32(in_cap) & totalCaps) != 0;
}

U32 MemStream::getPosition() const
{
   AssertFatal(getStatus() != Closed, "Position of a closed stream is undefined");

   return mCurrentPosition;
}

bool MemStream::setPosition(const U32 in_newPosition)
{
   AssertFatal(getStatus() != Closed, "SetPosition of a closed stream is not allowed");
   AssertFatal(in_newPosition <= mStreamSize, "Invalid position");

   mCurrentPosition = in_newPosition;
   if (mCurrentPosition > mStreamSize) {
      // Never gets here in debug version, this is for the release builds...
      //
      setStatus(UnknownError);
      return false;
   } else if (mCurrentPosition == mStreamSize) {
      setStatus(EOS);
   } else {
      setStatus(Ok);
   }

   return true;
}

bool MemStream::_read(const U32 in_numBytes, void *out_pBuffer)
{
   AssertFatal(getStatus() != Closed, "Attempted read from a closed stream");

   if (in_numBytes == 0)
      return true;

   AssertFatal(out_pBuffer != NULL, "Invalid output buffer");

   if (hasCapability(StreamRead) == false) {
      AssertWarn(false, "Reading is disallowed on this stream");
      setStatus(IllegalCall);
      return false;
   }

   bool success     = true;
   U32  actualBytes = in_numBytes;
   if ((mCurrentPosition + in_numBytes) > mStreamSize) {
      success = false;
      actualBytes = mStreamSize - mCurrentPosition;
   }

   // Obtain a current pointer, and do the copy
   const void* pCurrent = (const void*)((const U8*)mBufferBase + mCurrentPosition);
   dMemcpy(out_pBuffer, pCurrent, actualBytes);

   // Advance the stream position
   mCurrentPosition += actualBytes;

   if (!success)
      setStatus(EOS);
   else
      setStatus(Ok);

   return success;
}

bool MemStream::_write(const U32 in_numBytes, const void *in_pBuffer)
{
   AssertFatal(getStatus() != Closed, "Attempted write to a closed stream");

   if (in_numBytes == 0)
      return true;

   if (hasCapability(StreamWrite) == false) 
   {
      AssertWarn(0, "Writing is disallowed on this stream");
      setStatus(IllegalCall);
      return false;
   }

   bool success     = true;
   U32  actualBytes = in_numBytes;
   if ((mCurrentPosition + in_numBytes) > mBufferSize) 
   {
      if ( mGrowSize > 0 ) 
      {
         U32 growSize = (mCurrentPosition + in_numBytes) - mBufferSize;
         mBufferSize += growSize + ( mGrowSize - ( growSize % mGrowSize ) );
         mBufferBase = dRealloc( mBufferBase, mBufferSize );
      } 
      else
      {
         success = false;
         actualBytes = mBufferSize - mCurrentPosition;
      }
   }

   AssertFatal(in_pBuffer != NULL, "Invalid input buffer");

   // Obtain a current pointer, and do the copy
   void* pCurrent = (void*)((U8*)mBufferBase + mCurrentPosition);
   dMemcpy(pCurrent, in_pBuffer, actualBytes);

   // Advance the stream position
   mCurrentPosition += actualBytes;
   if (mCurrentPosition > mStreamSize)
      mStreamSize = mCurrentPosition;

   if (mCurrentPosition == mStreamSize)
      setStatus(EOS);
   else
      setStatus(Ok);

   return success;
}

void *MemStream::takeBuffer()
{
   void *buffer = mBufferBase;
   
   mBufferBase = NULL;
   mBufferSize = 0;
   mStreamSize = 0;
   mCurrentPosition = 0;

   setStatus(EOS);

   return buffer;
}
