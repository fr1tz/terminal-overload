// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _VITCBITSTREAMOBJECT_H_
#define _VITCBITSTREAMOBJECT_H_

#ifndef _SIMBASE_H_
#include "console/simBase.h"
#endif

#ifndef _BITSTREAM_H_
#include "core/stream/bitStream.h"
#endif

class vitcBitStreamObject : public SimObject
{
   typedef SimObject Parent;

   BitStream* mStream;
   U8* mBuffer;
   size_t mBufferSize;

public:
   vitcBitStreamObject();
   virtual ~vitcBitStreamObject();

   void initBuffer(size_t size);
   void initBufferFromBase64(const char* string);

   BitStream* getBitStream() { return mStream; }

   // SimObject
   DECLARE_CONOBJECT( vitcBitStreamObject );
   DECLARE_CATEGORY( "Core" );
   DECLARE_DESCRIPTION( "A console object that wraps a BitStream object." );
};

#endif // _VITCBITSTREAMOBJECT_H_