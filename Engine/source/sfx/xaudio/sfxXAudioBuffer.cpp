// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "sfx/xaudio/sfxXAudioBuffer.h"
#include "sfx/xaudio/sfxXAudioVoice.h"


//#define DEBUG_SPEW


SFXXAudioBuffer* SFXXAudioBuffer::create( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description )
{
   SFXXAudioBuffer *buffer = new SFXXAudioBuffer( stream, description );
   return buffer;
}

SFXXAudioBuffer::SFXXAudioBuffer( const ThreadSafeRef< SFXStream >& stream, SFXDescription* description )
   : Parent( stream, description )
{
   VECTOR_SET_ASSOCIATION( mBufferQueue );
}

SFXXAudioBuffer::~SFXXAudioBuffer()
{
   _flush();
}

void SFXXAudioBuffer::write( SFXInternal::SFXStreamPacket* const* packets, U32 num )
{
   AssertFatal( SFXInternal::isSFXThread(), "SFXXAudioBuffer::write() - not on SFX thread" );

   using namespace SFXInternal;

   // Unqueue processed packets.

   if( isStreaming() )
   {
      EnterCriticalSection( &_getUniqueVoice()->mLock );

      XAUDIO2_VOICE_STATE state;
      _getUniqueVoice()->mXAudioVoice->GetState( &state );

      U32 numProcessed = mBufferQueue.size() - state.BuffersQueued;
      for( U32 i = 0; i < numProcessed; ++ i )
      {
         destructSingle< SFXStreamPacket* >( mBufferQueue.first().mPacket );
         mBufferQueue.pop_front();

         #ifdef DEBUG_SPEW
         Platform::outputDebugString( "[SFXXAudioBuffer] Unqueued packet" );
         #endif
      }

      LeaveCriticalSection( &_getUniqueVoice()->mLock );
   }

   // Queue new packets.

   for( U32 i = 0; i < num; ++ i )
   {
      SFXStreamPacket* packet = packets[ i ];
      Buffer buffer;

      if( packet->mIsLast )
         buffer.mData.Flags = XAUDIO2_END_OF_STREAM;

      buffer.mPacket = packet;
      buffer.mData.AudioBytes = packet->mSizeActual;
      buffer.mData.pAudioData = packet->data;

      mBufferQueue.push_back( buffer );

      #ifdef DEBUG_SPEW
      Platform::outputDebugString( "[SFXXAudioBuffer] Queued packet" );
      #endif

      // If this is a streaming buffer, submit the packet to the
      // voice queue right away.

      if( isStreaming() )
      {
         EnterCriticalSection( &_getUniqueVoice()->mLock );

         IXAudio2SourceVoice* voice = _getUniqueVoice()->mXAudioVoice;
         voice->SubmitSourceBuffer( &buffer.mData );

         LeaveCriticalSection( &_getUniqueVoice()->mLock );
      }
   }
}

void SFXXAudioBuffer::_flush()
{
   #ifdef DEBUG_SPEW
   Platform::outputDebugString( "[SFXXAudioBuffer] Flushing buffer" );
   #endif

   if( _getUniqueVoice() )
      _getUniqueVoice()->_stop();

   while( !mBufferQueue.empty() )
   {
      destructSingle( mBufferQueue.last().mPacket );
      mBufferQueue.pop_back();
   }
}
