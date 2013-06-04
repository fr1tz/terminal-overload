// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _WINVOLUME_H_
#define _WINVOLUME_H_

#ifndef _VOLUME_H_
#include "core/volume.h"
#endif

namespace Torque
{
using namespace FS;

namespace Win32
{

//-----------------------------------------------------------------------------

class Win32FileSystem: public FileSystem
{
public:
   Win32FileSystem(String volume);
   ~Win32FileSystem();

   String   getTypeStr() const { return "Win32"; }

   FileNodeRef resolve(const Path& path);
   FileNodeRef create(const Path& path,FileNode::Mode);
   bool remove(const Path& path);
   bool rename(const Path& from,const Path& to);
   Path mapTo(const Path& path);
   Path mapFrom(const Path& path);

private:
   String mVolume;
};


//-----------------------------------------------------------------------------
/// Win32 stdio file access.
/// This class makes use the fopen, fread and fwrite for buffered io.
class Win32File: public File
{
public:
   ~Win32File();

   Path getName() const;
   Status getStatus() const;
   bool getAttributes(Attributes*);
   U64 getSize();

   U32 getPosition();
   U32 setPosition(U32,SeekMode);

   bool open(AccessMode);
   bool close();

   U32 read(void* dst, U32 size);
   U32 write(const void* src, U32 size);

private:
   friend class Win32FileSystem;

   U32 calculateChecksum();

   Path     mPath;
   String   mName;
   void     *mHandle;
   Status   mStatus;

   Win32File(const Path &path, String name);

   bool _updateInfo();
   void _updateStatus();
};


//-----------------------------------------------------------------------------

class Win32Directory: public Directory
{
public:
   ~Win32Directory();

   Path getName() const;
   Status getStatus() const;
   bool getAttributes(Attributes*);

   bool open();
   bool close();
   bool read(Attributes*);

private:
   friend class Win32FileSystem;

   U32 calculateChecksum();

   Path     mPath;
   String   mName;
   void     *mHandle;
   Status   mStatus;

   Win32Directory(const Path &path,String name);

   void _updateStatus();
};

} // Namespace
} // Namespace
#endif
