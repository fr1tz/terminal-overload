// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _NOTC_HTTPOBJECT_H_
#define _NOTC_HTTPOBJECT_H_

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif
#ifndef _TCPOBJECT_H_
#include "app/net/tcpObject.h"
#endif

class FileStream;

class notcHttpFileDownloader : public TCPObject
{
public:
   DECLARE_CALLBACK(void, onDownloadComplete, ());
private:
   typedef TCPObject Parent;
protected:
   enum ParseState {
      ParsingStatusLine,
      ParsingHeader,
      ParsingChunkHeader,
      ProcessingBody,
      ProcessingDone,
   };
   ParseState mParseState;
   U32 mTotalBytes;
   U32 mBytesRemaining;
 public:
   U32 mStatus;
   F32 mVersion;
   S32 mContentLength;
   bool mChunkedEncoding;
   U32 mChunkSize;
   const char *mContentType;
   char *mHostName;
   char *mPath;
   char *mQuery;
   char *mPost;
   U8 *mBufferSave;
   U32 mBufferSaveSize;
   FileStream* mFileStream;
public:
   static void expandPath(char *dest, const char *path, U32 destSize);
   bool download(const char *hostName, const char *urlName, const char* file, const char *query);
   notcHttpFileDownloader();
   ~notcHttpFileDownloader();

   virtual U32 onDataReceive(U8 *buffer, U32 bufferLen);
   virtual U32 onReceive(U8 *buffer, U32 bufferLen); // process a buffer of raw packet data
   virtual void onConnected();
   virtual void onConnectFailed();
   virtual void onDisconnect();
   bool processLine(UTF8 *line);

   DECLARE_CONOBJECT(notcHttpFileDownloader);
};


#endif  // _NOTC_HTTPOBJECT_H_
