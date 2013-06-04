// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "videoCapture.h"
#include "core/stream/fileStream.h"
#include "console/console.h"
#include "gfx/bitmap/gBitmap.h"

/// This is a very basic "encoder" that records the video as a series of numbered PNGs
/// Good if you're having problems with container-based formats and need extra flexibility.
class VideoEncoderPNG : public VideoEncoder
{
   U32 mCurrentFrame;

public:
   /// Begins accepting frames for encoding
   bool begin()
   {
      mPath += "\\";
      mCurrentFrame = 0;

      return true;
   }

   /// Pushes a new frame into the video stream
   bool pushFrame( GBitmap * bitmap )
   {
      FileStream fs;
      String framePath = mPath + String::ToString("%.6u.png", mCurrentFrame);
      if ( !fs.open( framePath, Torque::FS::File::Write ) )
      {
         Con::errorf( "VideoEncoderPNG::pushFrame() - Failed to open output file '%s'!", framePath.c_str() );
         return false;
      }

      //Increment
      mCurrentFrame++;

      bool result = bitmap->writeBitmap("png", fs, 0);
      pushProcessedBitmap(bitmap);
 
      return result;
   }

   /// Finishes the encoding and closes the video
   bool end()
   {
      return true;
   }

   void setResolution( Point2I* resolution ) 
   {      
      mResolution = *resolution; 
   }
};

REGISTER_VIDEO_ENCODER(VideoEncoderPNG, PNG)