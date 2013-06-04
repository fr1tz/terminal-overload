// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXSTREAM_H_
#define _SFXSTREAM_H_

#ifndef _THREADSAFEREFCOUNT_H_
#  include "platform/threads/threadSafeRefCount.h"
#endif
#ifndef _SFXCOMMON_H_
#  include "sfx/sfxCommon.h"
#endif
#ifndef _TSTREAM_H_
#  include "core/stream/tStream.h"
#endif


/// The base sound data streaming interface.
///
/// @note Streams that support seeking should implement the IPositionable<U32> interface.
/// @note Since SFXStreams are byte streams, all offset/size information is in bytes and
///   not in number of samples.
class SFXStream : public ThreadSafeRefCount< SFXStream >,
                  public IInputStream< U8 >,
                  public IResettable
{
   public:

      typedef void Parent;

      /// Destructor.
      virtual ~SFXStream() {}

      /// Make a copy of this stream with its own private state, so
      /// new independent read() operations can be issued on the same
      /// data stream.
      ///
      /// @return Returns a copy of the stream or NULL.
      virtual SFXStream* clone() const { return NULL; }

      /// The format of the data in the stream.
      virtual const SFXFormat& getFormat() const = 0;

      /// The number of samples in the data stream.
      virtual U32 getSampleCount() const = 0;

      /// The data size in bytes of the decompressed PCM data.
      virtual U32 getDataLength() const = 0;

      /// The length of the sound in milliseconds.
      virtual U32 getDuration() const = 0;

      /// Returns true if we've reached the end of the stream.
      virtual bool isEOS() const = 0;

      /// Resets the stream to restart reading data from the begining.
      virtual void reset() = 0;

      /// Reads data from the stream and decompresses it into PCM samples.
      ///
      /// @param length Number of bytes to read.
      virtual U32 read( U8 *buffer, U32 length ) = 0;
};

typedef ThreadSafeRef< SFXStream > SFXStreamRef;

#endif // _SFXSTREAM_H_
