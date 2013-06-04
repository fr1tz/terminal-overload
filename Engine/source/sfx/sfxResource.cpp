// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/sfxResource.h"
#include "sfx/sfxFileStream.h"
#include "core/util/fourcc.h"
#include "core/resourceManager.h"



// Ugly workaround to keep the constructor protected.
struct SFXResource::_NewHelper
{
   static SFXResource* New( String fileName, const ThreadSafeRef< SFXStream >& stream )
   {
      return new SFXResource( fileName, stream );
   }
};


template<>
void* Resource< SFXResource >::create( const Torque::Path& path )
{
   String fullPath = path.getFullPath();

   // Try to open the stream.
   ThreadSafeRef< SFXStream > stream = SFXFileStream::create( fullPath );
   if( !stream )
      return NULL;

   // We have a valid stream... create the resource.
   SFXResource* res = SFXResource::_NewHelper::New( fullPath, stream );

   return res;
}

template<>
ResourceBase::Signature Resource< SFXResource >::signature()
{
   return MakeFourCC( 's', 'f', 'x', 'r' );
}

Resource< SFXResource > SFXResource::load( String filename )
{
   return ResourceManager::get().load( filename );
}

SFXResource::SFXResource( String fileName, SFXStream *stream )
   : mFileName( fileName ),
     mFormat( stream->getFormat() ),
     mDuration( stream->getDuration() )
{
}

bool SFXResource::exists( String filename )
{
   return SFXFileStream::exists( filename );
}

SFXStream* SFXResource::openStream()
{
   return SFXFileStream::create( mFileName );
}
