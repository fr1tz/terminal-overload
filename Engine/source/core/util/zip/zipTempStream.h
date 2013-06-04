// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/util/zip/zipArchive.h"
#include "core/util/str.h"

#ifndef _ZIPTEMPSTREAM_H_
#define _ZIPTEMPSTREAM_H_

namespace Zip
{

/// @addtogroup zipint_group
/// @ingroup zip_group
// @{

class ZipTempStream : public FileStream
{
   typedef FileStream Parent;

protected:
   CentralDir *mCD;
   bool mDeleteOnClose;
   String mFilename;

public:
   ZipTempStream() : mCD(NULL), mDeleteOnClose(false) {}
   ZipTempStream(CentralDir *cd) : mCD(cd), mDeleteOnClose(false) {}
   virtual ~ZipTempStream() { close(); }

   void setCentralDir(CentralDir *cd)     { mCD = cd; }
   CentralDir *getCentralDir()            { return mCD; }

   void setDeleteOnClose(bool del)        { mDeleteOnClose = del; }

   virtual bool open(String filename, Torque::FS::File::AccessMode mode);
   
   /// Open a temporary file in ReadWrite mode. The file will be deleted when the stream is closed.
   virtual bool open()
   {
      return open(String(), Torque::FS::File::ReadWrite);
   }

   virtual void close()
   {
      Parent::close();

      if(mDeleteOnClose)
         Torque::FS::Remove(mFilename);
      
   }

   /// Disallow setPosition() 
   virtual bool setPosition(const U32 i_newPosition)        { return false; }

   /// Seek back to the start of the file.
   /// This is used internally by the zip code and should never be called whilst
   /// filters are attached (e.g. when reading or writing in a zip file)
   bool rewind()
   {
      mStreamCaps |= U32(StreamPosition);
      bool ret = Parent::setPosition(0);
      mStreamCaps &= ~U32(StreamPosition);

      return ret;
   }
};

// @}

} // end namespace Zip

#endif // _ZIPTEMPSTREAM_H_
