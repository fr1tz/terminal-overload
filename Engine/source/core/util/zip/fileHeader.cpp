// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/frameAllocator.h"
#include "core/stream/stream.h"

#include "core/util/zip/fileHeader.h"
#include "core/util/zip/compressor.h"

#include "core/util/safeDelete.h"

#include "core/resizeStream.h"
#include "core/strings/stringFunctions.h"
#include "core/frameAllocator.h"

namespace Zip
{

//-----------------------------------------------------------------------------
// Constructor/Destructor
//-----------------------------------------------------------------------------

FileHeader::FileHeader()
{
   mHeaderSig = mFileHeaderSignature;

   mExtractVer = 20;
   mFlags = 0;
   mCompressMethod = Stored;

   mModTime = 0;
   mModDate = 0;

   mCRC32 = 0;

   mCompressedSize = 0;
   mUncompressedSize = 0;

   mFilename = "";
}

FileHeader::~FileHeader()
{
   for(S32 i = 0;i < mExtraFields.size();i++)
   {
      SAFE_DELETE(mExtraFields[i]);
   }
}

//-----------------------------------------------------------------------------
// Protected Methods
//-----------------------------------------------------------------------------

bool FileHeader::readExtraFields(Stream *stream, U16 efLen)
{
   bool ret = true;

   U32 pos = stream->getPosition();
   U32 end = pos + efLen;

   while(stream->getPosition() < end)
   {
      U16 fieldSig, fieldSize;

      ret = false;

      ret |= stream->read(&fieldSig);
      ret |= stream->read(&fieldSize);
      if(! ret)
         break;

      pos = stream->getPosition();

      ExtraField *ef = ExtraField::create(fieldSig);
      if(ef)
      {
         ret |= ef->read(stream);

         if(! ret)
            delete ef;
         else
            mExtraFields.push_back(ef);
      }

      stream->setPosition(pos + fieldSize);
   }
   
   return ret;
}

//-----------------------------------------------------------------------------
// Public Methods
//-----------------------------------------------------------------------------

bool FileHeader::read(Stream *stream)
{
   stream->read(&mHeaderSig);
   if(mHeaderSig != mFileHeaderSignature)
      return false;

   stream->read(&mExtractVer);
   stream->read(&mFlags);
   stream->read(&mCompressMethod);
   stream->read(&mModTime);
   stream->read(&mModDate);
   stream->read(&mCRC32);
   stream->read(&mCompressedSize);
   stream->read(&mUncompressedSize);
   
   U16 fnLen, efLen;
   stream->read(&fnLen);
   stream->read(&efLen);

   char *fn = new char[fnLen + 1];
   stream->read(fnLen, fn);
   fn[fnLen] = 0;
   mFilename = fn;
   SAFE_DELETE_ARRAY(fn);
   

   return readExtraFields(stream, efLen);
}

bool FileHeader::write(Stream *stream)
{
   mHeaderSig = mFileHeaderSignature;

   stream->write(mHeaderSig);
   
   stream->write(mExtractVer);
   stream->write(mFlags);
   stream->write(mCompressMethod);
   stream->write(mModTime);
   stream->write(mModDate);
   stream->write(mCRC32);
   stream->write(mCompressedSize);
   stream->write(mUncompressedSize);

   U16 fnLen = mFilename.length(),
      efLen = 0;
   stream->write(fnLen);
   stream->write(efLen);

   if(fnLen)
      stream->write(fnLen, mFilename);

   // FIXME [tom, 1/23/2007] Write extra fields here

   return true;
}

//-----------------------------------------------------------------------------

ExtraField *FileHeader::findExtraField(U16 id)
{
   for(S32 i = 0;i < mExtraFields.size();++i)
   {
      if(mExtraFields[i]->getID() == id)
         return mExtraFields[i];
   }

   return NULL;
}

//-----------------------------------------------------------------------------

void FileHeader::setFilename(String filename)
{
   mFilename = filename;
}

} // end namespace Zip
