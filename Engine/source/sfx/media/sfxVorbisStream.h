// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXVORBISSTREAM_H_
#define _SFXVORBISSTREAM_H_

#ifdef TORQUE_OGGVORBIS

#ifndef _SFXFILESTREAM_H_
#  include "sfx/sfxFileStream.h"
#endif
#include "core/util/safeDelete.h"
#include "vorbis/vorbisfile.h"


/// An SFXFileStream that loads sample data from a Vorbis file.
class SFXVorbisStream : public SFXFileStream,
                        public IPositionable< U32 >
{
   public:

      typedef SFXFileStream Parent;

   protected:

      /// The vorbis file.
	   OggVorbis_File *mVF;

      /// The current bitstream index.
      S32 mBitstream;
      
      /// Total number of bytes read from the Vorbis stream so far.
      U32 mBytesRead;

      ///
      bool _openVorbis();

      // The ov_callbacks.
      static size_t _read_func( void *ptr, size_t size, size_t nmemb, void *datasource );
      static int _seek_func( void *datasource, ogg_int64_t offset, int whence );
      static long _tell_func( void *datasource );

      // SFXStream
      virtual bool _readHeader();
      virtual void _close();

   public:

      ///
      static SFXVorbisStream* create( Stream *stream );

      ///
	   SFXVorbisStream();

      ///
      SFXVorbisStream( const SFXVorbisStream& cloneFrom );

      virtual ~SFXVorbisStream();

      ///
      const vorbis_info* getInfo( S32 link = -1 );

      ///
      const vorbis_comment* getComment( S32 link = -1 );

      ///
      // TODO: Deal with error cases... like for unseekable streams!
      U64 getPcmTotal( S32 link = -1 );

      ///
      S32 read(   U8 *buffer, 
                  U32 length, 
                  S32 *bitstream );

      // SFXStream
      virtual void reset();
      virtual U32 read( U8 *buffer, U32 length );
      virtual bool isEOS() const;
      virtual SFXStream* clone() const
      {
         SFXVorbisStream* stream = new SFXVorbisStream( *this );
         if( !stream->mVF )
            SAFE_DELETE( stream );
         return stream;
      }

      // IPositionable
      virtual U32 getPosition() const;
      virtual void setPosition( U32 offset );
};

#endif // TORQUE_OGGVORBIS
#endif // _SFXVORBISSTREAM_H_
