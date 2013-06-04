// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _FILESTREAM_H_
#define _FILESTREAM_H_

#ifndef _VOLUME_H_
#include "core/volume.h"
#endif
#ifndef _STREAM_H_
#include "core/stream/stream.h"
#endif

class FileStream : public Stream
{
public:
   enum
   {
      BUFFER_SIZE = 8 * 1024,       // this can be changed to anything appropriate [in k]
      BUFFER_INVALID = 0xffffffff   // file offsets must all be less than this
   };

public:
   FileStream();                       // default constructor
   virtual ~FileStream();              // destructor

   // This function will allocate a new FileStream and open it.
   //  If it fails to allocate or fails to open, it will return NULL.
   //  The caller is responsible for deleting the instance.
   static FileStream *createAndOpen(const String &inFileName, Torque::FS::File::AccessMode inMode);

   // mandatory methods from Stream base class...
   virtual bool hasCapability(const Capability i_cap) const;

   virtual U32  getPosition() const;
   virtual bool setPosition(const U32 i_newPosition);
   virtual U32  getStreamSize();

   // additional methods needed for a file stream...
   virtual bool open(const String &inFileName, Torque::FS::File::AccessMode inMode);
   virtual void close();

   bool flush();
   FileStream* clone() const;

protected:
   // more mandatory methods from Stream base class...
   virtual bool _read(const U32 i_numBytes, void *o_pBuffer);
   virtual bool _write(const U32 i_numBytes, const void* i_pBuffer);

   void init();
   bool fillBuffer(const U32 i_startPosition);
   void clearBuffer();
   static void calcBlockHead(const U32 i_position, U32 *o_blockHead);
   static void calcBlockBounds(const U32 i_position, U32 *o_blockHead, U32 *o_blockTail);
   void setStatus();

   U32  mStreamCaps;                   // dependent on access mode

private:
   Torque::FS::FileRef mFile;          // file being streamed

   U8   mBuffer[BUFFER_SIZE];
   U32  mBuffHead;                     // first valid position of buffer (from start-of-file)
   U32  mBuffPos;                      // next read or write will occur here
   U32  mBuffTail;                     // last valid position in buffer (inclusive)
   bool mDirty;                        // whether buffer has been written to
   bool mEOF;                          // whether disk reads have reached the end-of-file

   FileStream(const FileStream &i_fileStrm);             // disable copy constructor
   FileStream& operator=(const FileStream &i_fileStrm);  // disable assignment operator
};

#endif // _FILE_STREAM_H
