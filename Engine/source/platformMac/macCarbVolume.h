// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _MACCARBVOLUME_H_
#define _MACCARBVOLUME_H_

#ifndef _POSIXVOLUME_H_
   #include "platformPOSIX/posixVolume.h"
#endif
#ifndef _TVECTOR_H_
   #include "core/util/tVector.h"
#endif


class MacFileSystem;


/// File system change notifications on Mac.
class MacFileSystemChangeNotifier : public Torque::FS::FileSystemChangeNotifier
{
   public:
   
      typedef Torque::FS::FileSystemChangeNotifier Parent;
      
      struct Event;

   protected:   
   
      /// Array of FSEventStream events set up.  Uses pointers to dynamically
      /// allocated memory rather than allocating inline with the array to be
      /// able to pass around pointers without colliding with array reallocation.
      Vector< Event* > mEvents;
   
      // FileSystemChangeNotifier.
      virtual void internalProcessOnce();
      virtual bool internalAddNotification( const Torque::Path& dir );
      virtual bool internalRemoveNotification( const Torque::Path& dir );
         
   public:
   
      MacFileSystemChangeNotifier( MacFileSystem* fs );
      
      virtual ~MacFileSystemChangeNotifier();
};

/// Mac filesystem.
class MacFileSystem : public Torque::Posix::PosixFileSystem
{
   public:
   
      typedef Torque::Posix::PosixFileSystem Parent;
      
      MacFileSystem( String volume )
         : Parent( volume )
      {
         mChangeNotifier = new MacFileSystemChangeNotifier( this );
      }
};

#endif // !_MACCARBVOLUME_H_
