// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _RESIZESTREAM_H_
#define _RESIZESTREAM_H_

//Includes
#ifndef _PLATFORM_H_
#include "platform/platform.h"
#endif
#ifndef _FILTERSTREAM_H_
#include "core/filterStream.h"
#endif

class ResizeFilterStream : public FilterStream, public IStreamByteCount
{
   typedef FilterStream Parent;

   Stream* m_pStream;
   U32     m_startOffset;
   U32     m_streamLen;
   U32     m_currOffset;
   U32 m_lastBytesRead;

  public:
   ResizeFilterStream();
   ~ResizeFilterStream();

   bool    attachStream(Stream* io_pSlaveStream);
   void    detachStream();
   Stream* getStream();

   bool setStreamOffset(const U32 in_startOffset,
                        const U32 in_streamLen);

   // Mandatory overrides.
  protected:
   bool _read(const U32 in_numBytes,  void* out_pBuffer);
  public:
   U32  getPosition() const;
   bool setPosition(const U32 in_newPosition);

   U32  getStreamSize();

   // IStreamByteCount
   U32 getLastBytesRead() { return m_lastBytesRead; }
   U32 getLastBytesWritten() { return 0; }
};

#endif //_RESIZESTREAM_H_
