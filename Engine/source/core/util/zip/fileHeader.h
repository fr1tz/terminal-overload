// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/util/zip/extraField.h"
#include "core/util/tVector.h"

#ifndef _FILEHEADER_H_
#define _FILEHEADER_H_

// Forward Refs
class Stream;

namespace Zip
{

/// @addtogroup zipint_group
/// @ingroup zip_group
// @{

enum FileFlags
{
   Encrypted = BIT(0),

   // For implode compression
   Implode8KDictionary = BIT(1),
   Implode3ShannonFanoTrees = BIT(2),

   // For deflate compression
   DeflateTypeMask = BIT(1) | BIT(2),

   FileInfoInDirectory = BIT(3),

   // Note that much of the following flag bits are unsupported for various reasons
   ReservedEnhDeflate = BIT(4),
   PatchData = BIT(5),
   StrongEncryption = BIT(6),

   UnusedReserved1 = BIT(7),
   UnusedReserved2 = BIT(8),
   UnusedReserved3 = BIT(9),
   UnusedReserved4 = BIT(10),
   UnusedReserved5 = BIT(11),

   ReservedPKWARE1 = BIT(12),

   EncryptedDirectory = BIT(13),

   ReservedPKWARE2 = BIT(14),
   ReservedPKWARE3 = BIT(15),
};

class FileHeader
{
   static const U32 mFileHeaderSignature = 0x04034b50;

protected:
   bool readExtraFields(Stream *stream, U16 efLen);

public:
   U32 mHeaderSig;

   U16 mExtractVer;
   U16 mFlags;
   U16 mCompressMethod;

   U16 mModTime;
   U16 mModDate;

   U32 mCRC32;

   U32 mCompressedSize;
   U32 mUncompressedSize;

   String mFilename;

   Vector<ExtraField *> mExtraFields;

   FileHeader();
   virtual ~FileHeader();

   virtual bool read(Stream *stream);
   virtual bool write(Stream *stream);

   ExtraField *findExtraField(U16 id);

   void setFilename(String filename);
};

// @}

} // end namespace Zip

#endif
