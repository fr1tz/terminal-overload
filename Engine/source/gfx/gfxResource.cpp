// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "gfx/gfxResource.h"
#include "gfx/gfxDevice.h"

GFXResource::GFXResource()
{
   mPrevResource = mNextResource = NULL;
   mOwningDevice = NULL;
   mFlagged = false;
}

GFXResource::~GFXResource()
{
   // Make sure we're not the head of the list and referencd on the device.
   if(mOwningDevice && mOwningDevice->mResourceListHead == this)
   {
      AssertFatal(mPrevResource == NULL, 
         "GFXResource::~GFXResource - head of list but have a previous item!");
      mOwningDevice->mResourceListHead = mNextResource;
   }

   // Unlink ourselves from the list.
   if(mPrevResource)
      mPrevResource->mNextResource = mNextResource;
   if(mNextResource)
      mNextResource->mPrevResource = mPrevResource;

   mPrevResource = mNextResource = NULL;
}

void GFXResource::registerResourceWithDevice( GFXDevice *device )
{
   mOwningDevice = device;
   mNextResource = device->mResourceListHead;
   device->mResourceListHead = this;

   if(mNextResource)
      mNextResource->mPrevResource = this;
}