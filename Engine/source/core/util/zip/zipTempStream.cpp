// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "console/console.h"
#include "core/util/zip/zipTempStream.h"
#include "core/crc.h"

namespace Zip
{

//-----------------------------------------------------------------------------
// Public Methods
//-----------------------------------------------------------------------------
static S32 tempNum = 0;

bool ZipTempStream::open(String filename, Torque::FS::File::AccessMode mode)
{
   if(filename.isEmpty())
   {
      filename = String("_ZipTempStream_tempfile") + String::ToString(tempNum++);
      //filename = Platform::getTemporaryFileName();
      mDeleteOnClose = true;
   }

   mFilename = filename;

   if(! Parent::open(filename, mode))
      return false;

   mStreamCaps &= ~U32(StreamPosition);

   return true;
}

} // end namespace Zip
