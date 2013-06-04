// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _ZIPSUBSTREAM_H_
#define _ZIPSUBSTREAM_H_

//Includes
#ifndef _FILTERSTREAM_H_
#include "core/filterStream.h"
#endif

struct z_stream_s;

class ZipSubRStream : public FilterStream, public IStreamByteCount
{
   typedef FilterStream Parent;
   static const U32 csm_streamCaps;
   static const U32 csm_inputBufferSize;

   Stream* m_pStream;
   U32     m_uncompressedSize;
   U32     m_currentPosition;
   bool     m_EOS;
   z_stream_s*  m_pZipStream;
   U8*          m_pInputBuffer;
   U32          m_originalSlavePosition;
   U32 m_lastBytesRead;

   U32 fillBuffer(const U32 in_attemptSize);
public:
   virtual U32 getLastBytesRead() { return m_lastBytesRead; }
   virtual U32 getLastBytesWritten() { return 0; }
   

  public:
   ZipSubRStream();
   virtual ~ZipSubRStream();

   // Overrides of NFilterStream
  public:
   bool    attachStream(Stream* io_pSlaveStream);
   void    detachStream();
   Stream* getStream();

   void setUncompressedSize(const U32);

   // Mandatory overrides.  By default, these are simply passed to
   //  whatever is returned from getStream();
  protected:
   bool _read(const U32 in_numBytes,  void* out_pBuffer);
  public:
   bool hasCapability(const Capability) const;

   U32  getPosition() const;
   bool setPosition(const U32 in_newPosition);

   U32  getStreamSize();
};

class ZipSubWStream : public FilterStream, public IStreamByteCount
{
   typedef FilterStream Parent;
   static const U32 csm_streamCaps;
   static const U32 csm_bufferSize;

   Stream*      m_pStream;
   z_stream_s*  m_pZipStream;
   U32          m_currPosition;  // Indicates number of _uncompressed_ bytes written
   U8*          m_pOutputBuffer;
   U8*          m_pInputBuffer;
   U32 m_lastBytesRead;
   U32 m_lastBytesWritten;

public:
   virtual U32 getLastBytesRead() { return m_lastBytesRead; }
   virtual U32 getLastBytesWritten() { return m_lastBytesWritten; }

  public:
   ZipSubWStream();
   virtual ~ZipSubWStream();

   // Overrides of NFilterStream
  public:
   bool    attachStream(Stream* io_pSlaveStream);
   void    detachStream();
   Stream* getStream();

   // Mandatory overrides.  By default, these are simply passed to
   //  whatever is returned from getStream();
  protected:
   bool _read(const U32 in_numBytes,  void* out_pBuffer);
   bool _write(const U32 in_numBytes, const void* in_pBuffer);
  public:
   bool hasCapability(const Capability) const;

   U32  getPosition() const;
   bool setPosition(const U32 in_newPosition);

   U32  getStreamSize();
};

#endif //_ZIPSUBSTREAM_H_
