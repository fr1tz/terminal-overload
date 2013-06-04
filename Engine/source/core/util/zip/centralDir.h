// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/util/zip/fileHeader.h"

#ifndef _CENTRALDIR_H_
#define _CENTRALDIR_H_

namespace Zip
{

/// @addtogroup zipint_group
/// @ingroup zip_group
// @{

/// Internal flags used by the zip code when writing zips
enum CDIntFlags
{
   CDFileDirty = BIT(0),
   CDFileAdded = BIT(1),
   CDFileDeleted = BIT(2),
   CDFileOpen = BIT(3)
};

class CentralDir : public FileHeader
{
   typedef FileHeader Parent;

   static const U32 mCentralDirSignature = 0x02014b50;
   
   char *mFileComment;

public:
   U16 mDiskNumStart;
   
   U16 mInternalFileAttr;
   U32 mExternalFileAttr;
   
   U32 mLocalHeadOffset;
   
   U16 mVersionMadeBy;

   U32 mInternalFlags;

   CentralDir();
   CentralDir(FileHeader &fh);
   virtual ~CentralDir();

   virtual bool read(Stream *stream);
   virtual bool write(Stream *stream);

   void setFileComment(const char *comment);
};

class EndOfCentralDir
{
   static const U32 mEOCDSignature = 0x06054b50;
   /// The size of the EndOfCentralDir record in the zip file, used to locate it
   /// at the end of the file.
   static const U32 mRecordSize = 20;
   /// The number of bytes from the end of the file to start searching for the EOCD
   static const U32 mEOCDSearchSize = 64 * 1024;

public:
   U32 mHeaderSig;

   U16 mDiskNum;
   U16 mStartCDDiskNum;
   U16 mNumEntriesInThisCD;
   U16 mTotalEntriesInCD;
   U32 mCDSize;
   U32 mCDOffset;
   U16 mCommentSize;
   
   const char *mZipComment;

   EndOfCentralDir();
   virtual ~EndOfCentralDir();

   virtual bool findInStream(Stream *stream);

   virtual bool read(Stream *stream);
   virtual bool write(Stream *stream);

   virtual void setZipComment(const char *zipComment);
   virtual void setZipComment(U16 commentSize, const char *zipComment);
};

// @}

} // end namespace Zip

#endif // _CENTRALDIR_H_
