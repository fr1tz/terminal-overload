// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _POSIXVOLUME_H_
#define _POSIXVOLUME_H_

#ifndef _VOLUME_H_
#include "core/volume.h"
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

namespace Torque
{
using namespace FS;

namespace Posix
{

//-----------------------------------------------------------------------------

class PosixFileSystem: public FileSystem
{
   String _volume;

public:
   PosixFileSystem(String volume);
   ~PosixFileSystem();

   String   getTypeStr() const { return "POSIX"; }

   FileNodeRef resolve(const Path& path);
   FileNodeRef create(const Path& path,FileNode::Mode);
   bool remove(const Path& path);
   bool rename(const Path& from,const Path& to);
   Path mapTo(const Path& path);
   Path mapFrom(const Path& path);
};


//-----------------------------------------------------------------------------
/// Posix stdio file access.
/// This class makes use the fopen, fread and fwrite for buffered io.
class PosixFile: public File
{
   friend class PosixFileSystem;
   Path _path;
   String _name;
   FILE* _handle;
   Status _status;

   PosixFile(const Path& path,String name);
   bool _updateInfo();
   void _updateStatus();

public:
   ~PosixFile();

   Path getName() const;
   Status getStatus() const;
   bool getAttributes(Attributes*);

   U32 getPosition();
   U32 setPosition(U32,SeekMode);

   bool open(AccessMode);
   bool close();

   U32 read(void* dst, U32 size);
   U32 write(const void* src, U32 size);

private:
   U32 calculateChecksum();
};


//-----------------------------------------------------------------------------

class PosixDirectory: public Directory
{
   friend class PosixFileSystem;
   Path _path;
   String _name;
   DIR* _handle;
   Status _status;

   PosixDirectory(const Path& path,String name);
   void _updateStatus();

public:
   ~PosixDirectory();

   Path getName() const;
   Status getStatus() const;
   bool getAttributes(Attributes*);

   bool open();
   bool close();
   bool read(Attributes*);

private:
   U32 calculateChecksum();
};


} // Namespace
} // Namespace
#endif
