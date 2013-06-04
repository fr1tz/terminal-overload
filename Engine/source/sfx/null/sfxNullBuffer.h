// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _SFXNULLBUFFER_H_
#define _SFXNULLBUFFER_H_

#ifndef _SFXBUFFER_H_
   #include "sfx/sfxBuffer.h"
#endif


class SFXNullBuffer : public SFXBuffer
{
      friend class SFXNullDevice;
      typedef SFXBuffer Parent;

   protected:

      SFXNullBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description );

      // SFXBuffer.
      virtual void write( SFXInternal::SFXStreamPacket* const* packets, U32 num );
      virtual void _flush() {}

   public:

      virtual ~SFXNullBuffer();
};

#endif // _SFXNULLBUFFER_H_