// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/sfxFileStream.h"
#include "core/stream/fileStream.h"
#include "console/console.h"
#include "core/util/safeDelete.h"


SFXFileStream::ExtensionsVector SFXFileStream::smExtensions( __FILE__, __LINE__ );
SFXFileStream::CreateFnsVector SFXFileStream::smCreateFns( __FILE__, __LINE__ );


void SFXFileStream::registerExtension( String ext, SFXFILESTREAM_CREATE_FN create_fn )
{
   // Register the stream creation first.
   smExtensions.push_back( ext );
   smCreateFns.push_back( create_fn );
}

void SFXFileStream::unregisterExtension( String ext )
{
   for( ExtensionsVector::iterator iter = smExtensions.begin();
        iter != smExtensions.end(); ++ iter )
      if( ( *iter ).equal( ext, String::NoCase ) )
      {
         smExtensions.erase( iter );
         return;
      }
}

SFXFileStream* SFXFileStream::create( String filename )
{
   //RDTODO: if original file has an extension, we should try that first
   
   // First strip off our current extension (validating 
   // against a list of known extensions so that we don't
   // strip off the last part of a file name with a dot in it.

   String noExtension = Platform::stripExtension( filename, smExtensions );

   SFXFileStream *sfxStream = NULL;

   for( U32 i = 0; i < smExtensions.size(); i++ ) 
   {
      String testName = noExtension + smExtensions[ i ];

      Stream *stream = FileStream::createAndOpen( testName, Torque::FS::File::Read );
      if ( !stream )
         continue;

      // Note that the creation function swallows up the 
      // resource stream and will take care of deleting it.
      sfxStream = smCreateFns[i]( stream );
      if ( sfxStream )
         return sfxStream;
   }

   return NULL;
}

bool SFXFileStream::exists( String filename )
{
   // First strip off our current extension (validating 
   // against a list of known extensions so that we don't
   // strip off the last part of a file name with a dot in it.

   String noExtension = Platform::stripExtension( filename, smExtensions );

   for( U32 i = 0; i < smExtensions.size(); i++ ) 
   {
      String testName = noExtension + smExtensions[ i ];
      if( Torque::FS::IsFile( testName ) )
         return true;
   }

   return false;
}

SFXFileStream::SFXFileStream()
   :  mStream( NULL ),
      mOwnStream( false ),
      mFormat( 0, 0, 0 ),
      mSamples( 0 )
{
}

SFXFileStream::SFXFileStream( const SFXFileStream& cloneFrom )
{
   mStream = cloneFrom.mStream->clone();
   if( !mStream )
   {
      Con::errorf( "SFXFileStream::SFXFileStream() - Failed to clone source stream" );
      return;
   }

   mOwnStream  = true;
   mFormat     = cloneFrom.mFormat;
   mSamples    = cloneFrom.mSamples;
}


SFXFileStream::~SFXFileStream()
{
   // If the stream is still open, close it now.  _close()
   // should usually be called by the destructor of derived classes,
   // but it their constructor fails, these won't even run.
   
   if( mStream && mOwnStream )
      SAFE_DELETE( mStream );
}

bool SFXFileStream::open( Stream *stream, bool ownStream )
{
   AssertFatal( stream, "SFXFileStream::open() - Got null stream!" );   

   close();

   mStream = stream;
   mOwnStream = ownStream;

   if( _readHeader() )
   {
      reset(); // Make sure we're set to read sample data.
      return true;
   }
   else
      return false;
}

void SFXFileStream::close()
{
   if ( !mStream )
      return;

   // Let the overloaded class cleanup.
   _close();

   // We only close it if we own it.
   if ( mOwnStream )
      SAFE_DELETE( mStream );

   // Reset these to make it easier to detect bugs.
   mFormat.set( 0, 0, 0 );
   mSamples = 0;
}

bool SFXFileStream::isEOS() const
{
   if ( !mStream )
      return true;

   return mStream->getStatus() != Stream::Ok;
}
