// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "core/util/zip/compressor.h"

#include "core/util/zip/zipSubStream.h"

namespace Zip
{

ImplementCompressor(Deflate, Deflated);

CompressorCreateReadStream(Deflate)
{
   ZipSubRStream *stream = new ZipSubRStream;
   stream->attachStream(zipStream);
   stream->setUncompressedSize(cdir->mUncompressedSize);

   return stream;
}

CompressorCreateWriteStream(Deflate)
{
   ZipSubWStream *stream = new ZipSubWStream;
   stream->attachStream(zipStream);

   return stream;
}

} // end namespace Zip
