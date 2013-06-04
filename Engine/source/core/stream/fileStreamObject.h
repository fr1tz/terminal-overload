// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FILESTREAMOBJECT_H_
#define _FILESTREAMOBJECT_H_

#ifndef _STREAMOBJECT_H_
#include "core/stream/streamObject.h"
#endif

#ifndef _FILESTREAM_H_
#include "core/stream/fileStream.h"
#endif


class FileStreamObject : public StreamObject
{
   typedef StreamObject Parent;

protected:
   FileStream mFileStream;

public:
   FileStreamObject();
   virtual ~FileStreamObject();
   DECLARE_CONOBJECT(FileStreamObject);

   virtual bool onAdd();

   //-----------------------------------------------------------------------------
   /// @brief Open a file
   /// 
   /// @param filename Name of file to open
   /// @param mode One of #Torque::FS::File::Read, #Torque::FS::File::Write, #Torque::FS::File::ReadWrite or #Torque::FS::File::WriteAppend
   /// @return true for success, false for failure
   /// @see close()
   //-----------------------------------------------------------------------------
   bool open(const char *filename, Torque::FS::File::AccessMode mode);

   //-----------------------------------------------------------------------------
   /// @brief Close the file
   /// 
   /// @see open()
   //-----------------------------------------------------------------------------
   void close();
};

#endif // _FILESTREAMOBJECT_H_
