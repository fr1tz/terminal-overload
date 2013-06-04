// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXMEMORYSTREAM_H_
#define _SFXMEMORYSTREAM_H_

#ifndef _SFXSTREAM_H_
   #include "sfx/sfxStream.h"
#endif
#ifndef _TSTREAM_H_
   #include "core/stream/tStream.h"
#endif
#ifndef _RAWDATA_H_
   #include "core/util/rawData.h"
#endif


/// A stream filter that converts sample packets from its source stream
/// to a continuous sample stream.  Useful for feeding sound from a source
/// that pushes sample data in discrete packets.
///
/// @note For the SFXMemoryStream to allow a reset(), the source input
///   stream must implement IResettable.
class SFXMemoryStream : public SFXStream,
                        public IInputStreamFilter< U8, IInputStream< RawData* >* >
{
   public:
   
      typedef SFXStream Parent;
      
   protected:
   
      ///
      SFXFormat mFormat;
   
      /// Total number of samples in the stream.  If this is U32_MAX, the stream
      /// is considered to be of indefinite size.
      U32 mNumSamplesTotal;
      
      /// Number of samples left to be read from stream.  Locked to U32_MAX for
      /// stream of indefinite size.
      U32 mNumSamplesLeft;
      
      /// The current sample data packet.
      RawData* mCurrentPacket;
      
      /// Read offset in the current sample data packet.
      U32 mCurrentPacketOffset;
         
   public:
   
      ///
      SFXMemoryStream( const SFXFormat& format, SourceStreamType* stream, U32 numSamples = U32_MAX );
      
      // SFXStream.
      const SFXFormat& getFormat() const { return mFormat; }
      U32 getSampleCount() const { return mNumSamplesTotal; }
      U32 getDataLength() const { return ( mNumSamplesTotal == U32_MAX ? U32_MAX : mFormat.getDataLength( getDuration() ) ); }
      U32 getDuration() const { return ( mNumSamplesTotal == U32_MAX ? U32_MAX : mFormat.getDuration( mNumSamplesTotal ) ); }
      bool isEOS() const { return ( mNumSamplesLeft != 0 ); }
      void reset();
      U32 read( U8 *buffer, U32 length );      
};

#endif // !_SFXMEMORYSTREAM_H_
