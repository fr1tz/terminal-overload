// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _CORE_ZIP_VOLUME_H_
#define _CORE_ZIP_VOLUME_H_

#include "core/volume.h"
#include "core/util/str.h"
#include "core/util/zip/zipArchive.h"
#include "core/util/autoPtr.h"

namespace Torque
{
   using namespace FS;
   using namespace Zip;

class ZipFileSystem: public FileSystem
{
public:
   ZipFileSystem(String& zipFilename, bool zipNameIsDir = false);
   virtual ~ZipFileSystem();

   String   getTypeStr() const { return "Zip"; }

   FileNodeRef resolve(const Path& path);

   // these are unsupported, ZipFileSystem is currently read only access
   FileNodeRef create(const Path& path,FileNode::Mode) { return 0; }
   bool remove(const Path& path) { return 0; }
   bool rename(const Path& a,const Path& b) { return 0; }

   // these are unsupported
   Path mapTo(const Path& path) { return path; }
   Path mapFrom(const Path& path) { return path; }

public:
   /// Private interface for use by unit test only. 
   StrongRefPtr<ZipArchive> getArchive() { return mZipArchive; }

private:
   void _init();

   bool mInitted;
   bool mZipNameIsDir;
   String mZipFilename;
   String mFakeRoot;
   FileStream* mZipArchiveStream;
   StrongRefPtr<ZipArchive> mZipArchive;
};

}

#endif