// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.
#ifndef _MEMVOLUME_H_
#define _MEMVOLUME_H_

#ifndef _VOLUME_H_
#include "core/volume.h"
#endif

#ifndef _TDICTIONARY_H_
#include "core/util/tDictionary.h"
#endif 

namespace Torque
{
   using namespace FS;

   namespace Mem
   {

      struct MemFileData;
      struct MemDirectoryData;
      class MemDirectory;

      //-----------------------------------------------------------------------------
      class MemFileSystem: public FileSystem
      {
      public:
         MemFileSystem(String volume);
         ~MemFileSystem();

         String   getTypeStr() const { return "Mem"; }

         FileNodeRef resolve(const Path& path);
         FileNodeRef create(const Path& path,FileNode::Mode);
         bool remove(const Path& path);
         bool rename(const Path& from,const Path& to);
         Path mapTo(const Path& path);
         Path mapFrom(const Path& path);

      private:
         String mVolume;
         MemDirectoryData* mRootDir;

         MemDirectory* getParentDir(const Path& path, FileNodeRef& parentRef);
      };

      //-----------------------------------------------------------------------------
      /// Mem stdio file access.
      /// This class makes use the fopen, fread and fwrite for buffered io.
      class MemFile: public File
      {
      public:
         MemFile(MemFileSystem* fs, MemFileData* fileData);
         virtual ~MemFile();

         Path getName() const;
         NodeStatus getStatus() const;
         bool getAttributes(Attributes*);

         U32 getPosition();
         U32 setPosition(U32,SeekMode);

         bool open(AccessMode);
         bool close();

         U32 read(void* dst, U32 size);
         U32 write(const void* src, U32 size);

      private:
         U32 calculateChecksum();

         MemFileSystem* mFileSystem;
         MemFileData* mFileData;
         NodeStatus   mStatus;
         U32 mCurrentPos;

         bool _updateInfo();
         void _updateStatus();
      };


      //-----------------------------------------------------------------------------

      class MemDirectory: public Directory
      {
      public:
         MemDirectory(MemFileSystem* fs, MemDirectoryData* dir);
         ~MemDirectory();

         Path getName() const;
         NodeStatus getStatus() const;
         bool getAttributes(Attributes*);

         bool open();
         bool close();
         bool read(Attributes*);

      private:
         friend class MemFileSystem;
         MemFileSystem* mFileSystem;
         MemDirectoryData* mDirectoryData;

         U32 calculateChecksum();         
         
         NodeStatus   mStatus;
         U32 mSearchIndex;         
      };

   } // Namespace
} // Namespace

#endif