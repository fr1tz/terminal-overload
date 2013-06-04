// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PLATFORMVFS_H_
#define _PLATFORMVFS_H_

namespace Zip
{
   class ZipArchive;
}

extern Zip::ZipArchive *openEmbeddedVFSArchive();
extern void closeEmbeddedVFSArchive();

#endif // _PLATFORMVFS_H_
