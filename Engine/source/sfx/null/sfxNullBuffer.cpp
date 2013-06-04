// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/null/sfxNullBuffer.h"
#include "sfx/sfxInternal.h"


SFXNullBuffer::SFXNullBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description )
   : Parent( stream, description, false )
{
   mStatus = STATUS_Ready;
}

SFXNullBuffer::~SFXNullBuffer()
{
}

void SFXNullBuffer::write( SFXInternal::SFXStreamPacket* const* packets, U32 num )
{
   // Should never really be called, but to be safe...

   for( U32 i = 0; i < num; ++ i )
      destructSingle( packets[ i ] );
}
