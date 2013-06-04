// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _OGGVORBISDECODER_H_
#define _OGGVORBISDECODER_H_

#ifndef _OGGINPUTSTREAM_H_
   #include "core/ogg/oggInputStream.h"
#endif
#ifndef _TSTREAM_H_
   #include "core/stream/tStream.h"
#endif
#ifndef _RAWDATA_H_
   #include "core/util/rawData.h"
#endif
#include "vorbis/codec.h"


/// Decodes a Vorbis substream into sample packets.
///
/// Vorbis samples are always 16bits.
class OggVorbisDecoder : public OggDecoder,
                         public IInputStream< RawData* >
{
   public:
   
      typedef OggDecoder Parent;
      
   protected:
      
      ///
      vorbis_info mVorbisInfo;
      
      ///
      vorbis_comment mVorbisComment;
      
      ///
      vorbis_dsp_state mVorbisDspState;
      
      ///
      vorbis_block mVorbisBlock;
      
      #ifdef TORQUE_DEBUG
      U32 mLock;
      #endif

      // OggDecoder.
      virtual bool _detect( ogg_page* startPage );
      virtual bool _init();
      virtual bool _packetin( ogg_packet* packet );
   
   public:
   
      ///
      OggVorbisDecoder( const ThreadSafeRef< OggInputStream >& stream );
      
      ~OggVorbisDecoder();
      
      ///
      U32 getNumChannels() const { return mVorbisInfo.channels; }
      
      ///
      U32 getSamplesPerSecond() const { return mVorbisInfo.rate; }
      
      // OggDecoder.
      virtual const char* getName() const { return "Vorbis"; }
      
      // IInputStream.
      virtual U32 read( RawData** buffer, U32 num );
};

#endif // !_OGGVORBISDECODER_H_
