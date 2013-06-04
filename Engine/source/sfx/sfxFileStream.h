// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXFILESTREAM_H_
#define _SFXFILESTREAM_H_

#ifndef _SFXSTREAM_H_
#  include "sfx/sfxStream.h"
#endif
#ifndef _TVECTOR_H_
#  include "core/util/tVector.h"
#endif
#ifndef _TORQUE_STRING_H_
#  include "core/util/str.h"
#endif


class Stream;
class SFXFileStream;

///
typedef SFXFileStream* ( *SFXFILESTREAM_CREATE_FN )( Stream *stream );

/// An SFXStream that streams from a file.
class SFXFileStream : public SFXStream
{
   protected:
      typedef Vector< String > ExtensionsVector;
      typedef Vector< SFXFILESTREAM_CREATE_FN > CreateFnsVector;

      static ExtensionsVector smExtensions;
      static CreateFnsVector smCreateFns;

      /// The file stream we're reading from.
      Stream *mStream;

      /// If true then we're responsible for closing the stream.
      bool mOwnStream;

      /// The format of the data in the stream.
      SFXFormat mFormat;    

      /// The number of samples in the data stream.
      U32 mSamples;

      /// Constructs the stream in an uninitilized state.
      SFXFileStream();

      ///
      SFXFileStream( const SFXFileStream& cloneFrom );

      /// Overloaded in the derived classes to read 
      /// the file header.  It should initialize 
      /// mFormat and mSamples.
      virtual bool _readHeader() = 0;

      /// Overloaded for cleanup of file format 
      /// specific structures.
      virtual void _close() = 0;

   public:

      ///
      static void registerExtension( String ext, SFXFILESTREAM_CREATE_FN create_fn );

      ///
      static void unregisterExtension( String ext );
   
      /// This is a helper function used to create an appropriate SFXStream
      /// for the requested sound file.
      ///
      /// @param filename The sound file path with or without extension.
      ///
      static SFXFileStream* create( String filename );

      ///
      static bool exists( String filename );

      /// Destructor.
      virtual ~SFXFileStream();

      /// Opens and optionally takes ownership of the stream.
	   bool open( Stream *stream, bool ownStream = false );

      /// Closes the stream.
      void close();

      // SFXStream.
      const SFXFormat& getFormat() const { return mFormat; }
      U32 getSampleCount() const { return mSamples; }
      U32 getDataLength() const { return mSamples * mFormat.getBytesPerSample(); }
      U32 getDuration() const { return mFormat.getDuration( mSamples ); }
      bool isEOS() const;
};

#endif // _SFXFILESTREAM_H_
