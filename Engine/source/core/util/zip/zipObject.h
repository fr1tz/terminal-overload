// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "console/simBase.h"
#include "core/util/zip/zipArchive.h"
#include "core/util/tVector.h"
#include "core/stream/streamObject.h"
#include "core/util/str.h"

#ifndef _ZIPOBJECT_H_
#define _ZIPOBJECT_H_

/// @addtogroup zip_group
// @{

//-----------------------------------------------------------------------------
/// @brief Script wrapper for Zip::ZipArchive.
//-----------------------------------------------------------------------------
class ZipObject : public SimObject
{
   typedef SimObject Parent;

protected:
   Zip::ZipArchive *mZipArchive;

   // StreamObjects are pooled and reused to avoid creating tons of SimObjects
   Vector<StreamObject *> mStreamPool;

   StreamObject *createStreamObject(Stream *stream);

public:
   ZipObject();
   virtual ~ZipObject();
   DECLARE_CONOBJECT(ZipObject);

   // Methods for accessing the archive
   /// @see Zip::ZipArchive::openArchive()
   bool openArchive(const char *filename, Zip::ZipArchive::AccessMode mode = Zip::ZipArchive::Read);
   /// @see Zip::ZipArchive::closeArchive()
   void closeArchive();

   // Stream based file system style interface
   /// @see Zip::ZipArchive::openFile()
   StreamObject *openFileForRead(const char *filename);
   /// @see Zip::ZipArchive::openFile()
   StreamObject *openFileForWrite(const char *filename);
   /// @see Zip::ZipArchive::closeFile()
   void closeFile(StreamObject *stream);

   // Alternative archiver style interface
   /// @see Zip::ZipArchive::addFile()
   bool addFile(const char *filename, const char *pathInZip, bool replace = true);
   /// @see Zip::ZipArchive::extractFile()
   bool extractFile(const char *pathInZip, const char *filename);
   /// @see Zip::ZipArchive::deleteFile()
   bool deleteFile(const char *filename);


   // Methods for access the list of files
   S32 getFileEntryCount();
   String getFileEntry(S32 idx);
};

// @}

#endif // _ZIPOBJECT_H_
