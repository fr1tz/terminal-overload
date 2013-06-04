// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ZIPCRYPTSTREAM_H_
#define _ZIPCRYPTSTREAM_H_

#ifndef _FILTERSTREAM_H_
#include "core/filterStream.h"
#endif

class ZipCryptRStream : public FilterStream
{
   typedef FilterStream Parent;

   Stream *mStream;

   S32 mStreamStartPos;
   S32 mFileStartPos;
   S32 mFileEndPos;
   
   U32 mKeys[3]; // mKeys and it's usage is very unclear and has a ton of magic numbers -patw
   
   const char *mPassword;

   U32 fillBuffer(const U32 in_attemptSize, void *pBuffer);

public:
   ZipCryptRStream();
   virtual ~ZipCryptRStream();

   void setPassword(const char *password);
   inline void setFileEndPos(S32 pos)        { mFileEndPos = pos; }

   // Overrides of FilterStream
   bool attachStream(Stream* io_pSlaveStream);
   void detachStream();
   Stream *getStream()                       { return mStream; }

   U32  getPosition() const;
   bool setPosition(const U32 in_newPosition);

protected:
   bool _read(const U32 in_numBytes,  void* out_pBuffer);

   void updateKeys(const U8 c);
   U8 decryptByte();
};

#endif // _ZIPCRYPTSTREAM_H_
