// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXFENCE_H_
#define _GFXFENCE_H_

#ifndef _GFXDEVICE_H_
#include "gfx/gfxDevice.h"
#endif


///
class GFXFence : public GFXResource
{
protected:

   GFXDevice *mDevice;

public:

   /// The states returned by getStatus()
   enum FenceStatus
   {
      Unset,         ///< The fence has not been set
      Pending,       ///< The fence has been set and has not been hit
      Processed,     ///< The fence has been processed
      Unsupported    ///< A non-blocking query of fence status is not supported by the implementation
   };

public:

   GFXFence( GFXDevice *device ) : mDevice( device ) {};
   virtual ~GFXFence(){};

   /// This method inserts the fence into the command buffer
   virtual void issue() = 0;

   // CodeReview: Do we need a remove() [5/10/2007 Pat]

   /// This is a non-blocking call to get the status of the fence
   /// @see GFXFence::FenceStatus
   virtual FenceStatus getStatus() const = 0;

   /// This method will not return until the fence has been processed by the GPU
   virtual void block() = 0;
};


///
class GFXGeneralFence : public GFXFence
{
protected:

   bool mInitialized;
   GFXTextureTargetRef mRenderTarget;
   GFXTexHandle mRTTexHandle;
   GFXStateBlockRef mRenderSB;

   void _init();

   /// The callback used to get texture events.
   /// @see GFXTextureManager::addEventDelegate
   void _onTextureEvent( GFXTexCallbackCode code );

public:

   GFXGeneralFence( GFXDevice *device ) 
      :  GFXFence( device ), 
         mInitialized( false ) 
   {
   }

   virtual ~GFXGeneralFence();

   virtual void issue();
   virtual FenceStatus getStatus() const { return GFXFence::Unsupported; };
   virtual void block();

   // GFXResource interface
   virtual void zombify();
   virtual void resurrect();
   /// The resource should put a description of itself (number of vertices, size/width of texture, etc.) in buffer
   virtual const String describeSelf() const;
};

#endif // _GFXFENCE_H_