// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFX_D3D_VIDEOCAPTURED3D9_H_
#define _GFX_D3D_VIDEOCAPTURED3D9_H_

#ifndef _VIDEOCAPTURE_H_
#include "gfx/video/videoCapture.h"
#endif

#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif


class VideoFrameGrabberD3D9 : public VideoFrameGrabber
{
protected:   
   enum CaptureStage {
      eReadyToCapture,         
      eInVideoMemory,       
      eInSystemMemory,
      eNumStages
   };

   // Contains all elements involved in single frame capture and
   // is used to spread the multiple "stages" needed to capture a bitmap
   // over various frames to keep GPU resources from locking the CPU.
   struct CaptureResource {
      GFXTexHandle vidMemTex; //Video memory texture
      GFXTexHandle sysMemTex; //System memory texture
      CaptureStage stage;     //This resource's capture stage

      CaptureResource() : stage(eReadyToCapture) {};
      ~CaptureResource()
      {
         vidMemTex.free();         
         sysMemTex.free();
      }
   };

   // Capture resource array. One item for each capture pipeline stage
   CaptureResource mCapture[eNumStages];

   // Current capture index
   S32 mCurrentCapture;
   
   // Copies a capture's video memory content to system memory
   void copyToSystemMemory(CaptureResource &capture);

   // Copies a capture's syste memory content to a new bitmap
   void copyToBitmap(CaptureResource &capture);

   bool _handleGFXEvent(GFXDevice::GFXDeviceEventType event);
      
   //------------------------------------------------
   // Overloaded from VideoFrameGrabber
   //------------------------------------------------
   void captureBackBuffer();
   void makeBitmap();
   void releaseTextures();

public:
   VideoFrameGrabberD3D9();
   ~VideoFrameGrabberD3D9();
};

#endif // _GFX_D3D_VIDEOCAPTURED3D9_H_
