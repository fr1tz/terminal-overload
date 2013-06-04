// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/sfxMemoryStream.h"
#include "platform/typetraits.h"
#include "console/console.h"


SFXMemoryStream::SFXMemoryStream( const SFXFormat& format,
                                  SourceStreamType* stream,
                                  U32 numSamples )
   : IInputStreamFilter< U8, SourceStreamType* >( stream ),
     mFormat( format ),
     mNumSamplesTotal( numSamples ),
     mNumSamplesLeft( numSamples ),
     mCurrentPacket( NULL ),
     mCurrentPacketOffset( 0 )
{
}

void SFXMemoryStream::reset()
{
   if( dynamic_cast< IResettable* >( getSourceStream() ) )
   {
      reinterpret_cast< IResettable* >( getSourceStream() )->reset();
      
      if( mCurrentPacket )
         destructSingle( mCurrentPacket );
         
      mCurrentPacket = NULL;
      mCurrentPacketOffset = 0;
      mNumSamplesLeft = mNumSamplesTotal;
   }
   else
      Con::errorf( "SFXMemoryStream - cannot reset source stream" );
}

U32 SFXMemoryStream::read( U8* buffer, U32 length )
{
   U32 bufferOffset = 0;
   
   // Determine how much we're supposed to read.
   
   U32 numBytesToCopy = length;
   if( mNumSamplesLeft != U32_MAX )
      numBytesToCopy = getMin( length, mNumSamplesLeft * mFormat.getBytesPerSample() );
   numBytesToCopy -= numBytesToCopy % mFormat.getBytesPerSample();
      
   // Copy the data.
   
   U32 numBytesLeftToCopy = numBytesToCopy;
   while( numBytesLeftToCopy )
   {
      // If we have a current packet, use its data.
      
      if( mCurrentPacket )
      {
         U32 numBytesLeftInCurrentPacket = mCurrentPacket->size - mCurrentPacketOffset;
         
         // Copy data.
         
         if( numBytesLeftInCurrentPacket )
         {
            const U32 numBytesToCopy = getMin( numBytesLeftInCurrentPacket, numBytesLeftToCopy );
            dMemcpy( &buffer[ bufferOffset ], &mCurrentPacket->data[ mCurrentPacketOffset ], numBytesToCopy );
            
            bufferOffset                  += numBytesToCopy;
            mCurrentPacketOffset          += numBytesToCopy;
            numBytesLeftInCurrentPacket   -= numBytesToCopy;
            numBytesLeftToCopy            -= numBytesToCopy;
         }
         
         // Discard the packet if there's no data left.
         
         if( !numBytesLeftInCurrentPacket )
         {
            destructSingle( mCurrentPacket );
            mCurrentPacket = NULL;
            mCurrentPacketOffset = 0;
         }
      }
      else
      {
         // Read a new packet.
         
         if( !getSourceStream()->read( &mCurrentPacket, 1 ) )
            break;
      }
   }
   
   // Update count of remaining samples.
   
   U32 numBytesCopied = numBytesToCopy - numBytesLeftToCopy;
   if( mNumSamplesLeft != U32_MAX )
      mNumSamplesLeft -= ( numBytesCopied / mFormat.getBytesPerSample() );
      
   return numBytesCopied;
}
