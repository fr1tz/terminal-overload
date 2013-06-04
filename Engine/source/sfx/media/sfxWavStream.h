// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXWAVSTREAM_H_
#define _SFXWAVSTREAM_H_

#ifndef _SFXFILESTREAM_H_
   #include "sfx/sfxFileStream.h"
#endif
#include "core/util/safeDelete.h"


/// An SFXFileStream that loads sample data from a WAV file.
class SFXWavStream : public SFXFileStream,
                     public IPositionable< U32 >
{
   public:

      typedef SFXFileStream Parent;

   protected:

      /// The file position of the start of
      /// the PCM data for fast reset().
      U32 mDataStart;

      // SFXFileStream
      virtual bool _readHeader();
      virtual void _close();

   public:

      ///
      static SFXWavStream* create( Stream *stream );

      ///
	   SFXWavStream();

      ///
      SFXWavStream( const SFXWavStream& cloneFrom );

      /// Destructor.
      virtual ~SFXWavStream();

      // SFXStream
      virtual void reset();
      virtual U32 read( U8 *buffer, U32 length );
      virtual SFXStream* clone() const
      {
         SFXWavStream* stream = new SFXWavStream( *this );
         if( !stream->mStream )
            SAFE_DELETE( stream );
         return stream;
      }

      // IPositionable
      virtual U32 getPosition() const;
      virtual void setPosition( U32 offset );
};

#endif  // _SFXWAVSTREAM_H_
