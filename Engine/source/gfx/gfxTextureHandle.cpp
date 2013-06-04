// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/platform.h"
#include "gfx/gfxTextureHandle.h"

#include "gfx/gfxDevice.h"
#include "gfx/gfxTextureManager.h"


GFXTexHandle GFXTexHandle::ZERO;
GFXTexHandle GFXTexHandle::ONE;
GFXTexHandle GFXTexHandle::ZUP;


GFXTexHandle::GFXTexHandle( GFXTextureObject *obj )
{
   StrongObjectRef::set( obj );
}

GFXTexHandle::GFXTexHandle( const GFXTexHandle &handle, const String &desc )
{
   StrongObjectRef::set( handle.getPointer() );
   
   #ifdef TORQUE_DEBUG
      if ( getPointer() )
         getPointer()->mDebugDescription = desc;
   #endif   
}

GFXTexHandle::GFXTexHandle( const String &texName, GFXTextureProfile *profile, const String &desc )
{
   set( texName, profile, desc );
}

bool GFXTexHandle::set( const String &texName, GFXTextureProfile *profile, const String &desc )
{
   // Clear the existing texture first, so that
   // its memory is free for the new allocation.
   free();
   
   // Create and set the new texture.
   AssertFatal( texName.isNotEmpty(), "Texture name is empty" );
   StrongObjectRef::set( TEXMGR->createTexture( texName, profile ) );
   
   #ifdef TORQUE_DEBUG
      if ( getPointer() )
         getPointer()->mDebugDescription = desc;
   #endif
   
   return isValid();
}

GFXTexHandle::GFXTexHandle( GBitmap *bmp, GFXTextureProfile *profile, bool deleteBmp, const String &desc )
{
   set( bmp, profile, deleteBmp, desc );
}

bool GFXTexHandle::set( GBitmap *bmp, GFXTextureProfile *profile, bool deleteBmp, const String &desc  )
{
   // Clear the existing texture first, so that
   // its memory is free for the new allocation.
   free();
   
   // Create and set the new texture.
   AssertFatal( bmp, "Bitmap is NULL" );
   StrongObjectRef::set( TEXMGR->createTexture( bmp, String(), profile, deleteBmp ) );

   #ifdef TORQUE_DEBUG
      if ( getPointer() )
         getPointer()->mDebugDescription = desc;
   #endif

   return isValid();
}

GFXTexHandle::GFXTexHandle( DDSFile *dds, GFXTextureProfile *profile, bool deleteDDS, const String &desc )
{
   set( dds, profile, deleteDDS, desc );
}

bool GFXTexHandle::set( DDSFile *dds, GFXTextureProfile *profile, bool deleteDDS, const String &desc )
{
   // Clear the existing texture first, so that
   // its memory is free for the new allocation.
   free();

   // Create and set the new texture.
   AssertFatal( dds, "Bitmap is NULL" );
   StrongObjectRef::set( TEXMGR->createTexture( dds, profile, deleteDDS ) );

   #ifdef TORQUE_DEBUG
      if ( getPointer() )
         getPointer()->mDebugDescription = desc;
   #endif

   return isValid();
}

GFXTexHandle::GFXTexHandle( U32 width, U32 height, GFXFormat format, GFXTextureProfile *profile, const String &desc, U32 numMipLevels, S32 antialiasLevel)
{
   set( width, height, format, profile, desc, numMipLevels, antialiasLevel );
}

bool GFXTexHandle::set( U32 width, U32 height, GFXFormat format, GFXTextureProfile *profile, const String &desc, U32 numMipLevels, S32 antialiasLevel)
{
   // Clear the existing texture first, so that
   // its memory is free for the new allocation.
   free();

   // Create and set the new texture.
   StrongObjectRef::set( TEXMGR->createTexture( width, height, format, profile, numMipLevels, antialiasLevel ) );

   #ifdef TORQUE_DEBUG
      if ( getPointer() )
         getPointer()->mDebugDescription = desc;
   #endif

   return isValid();
}

bool GFXTexHandle::set( U32 width, U32 height, U32 depth, void *pixels, GFXFormat format, GFXTextureProfile *profile, const String &desc, U32 numMipLevels )
{
   // Clear the existing texture first, so that
   // its memory is free for the new allocation.
   free();

   // Create and set the new texture.
   StrongObjectRef::set( TEXMGR->createTexture( width, height, depth, pixels, format, profile ) );

   #ifdef TORQUE_DEBUG
      if ( getPointer() )
         getPointer()->mDebugDescription = desc;
   #endif

   return isValid();
}

void GFXTexHandle::refresh()
{
   TEXMGR->reloadTexture( getPointer() );
}
