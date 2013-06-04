// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXD3D9PRIMITIVEBUFFER_H_
#define _GFXD3D9PRIMITIVEBUFFER_H_

#ifndef _GFXPRIMITIVEBUFFER_H_
#include "gfx/gfxPrimitiveBuffer.h"
#endif


struct IDirect3DIndexBuffer9;

class GFXD3D9PrimitiveBuffer : public GFXPrimitiveBuffer
{
   public:
      IDirect3DIndexBuffer9 *ib;
      StrongRefPtr<GFXD3D9PrimitiveBuffer> mVolatileBuffer;
      U32 mVolatileStart;

#ifdef TORQUE_DEBUG
   #define _PBGuardString "GFX_PRIMTIVE_BUFFER_GUARD_STRING"
   U8 *mDebugGuardBuffer;
   void *mLockedBuffer;
   U32 mLockedSize;
#endif TORQUE_DEBUG

      bool mLocked;
      bool                  mIsFirstLock;

      GFXD3D9PrimitiveBuffer( GFXDevice *device, 
                              U32 indexCount, 
                              U32 primitiveCount, 
                              GFXBufferType bufferType );

      virtual ~GFXD3D9PrimitiveBuffer();

      virtual void lock(U32 indexStart, U32 indexEnd, void **indexPtr);
      virtual void unlock();

      virtual void prepare();      

#ifdef TORQUE_DEBUG
   //GFXD3D9PrimitiveBuffer *next;
#endif

      // GFXResource interface
      virtual void zombify();
      virtual void resurrect();
};

inline GFXD3D9PrimitiveBuffer::GFXD3D9PrimitiveBuffer(   GFXDevice *device, 
                                                         U32 indexCount, 
                                                         U32 primitiveCount, 
                                                         GFXBufferType bufferType ) 
   : GFXPrimitiveBuffer( device, indexCount, primitiveCount, bufferType )
{
   mVolatileStart = 0;
   ib             = NULL;
   mIsFirstLock   = true;
   mLocked = false;
#ifdef TORQUE_DEBUG
   mDebugGuardBuffer = NULL;
   mLockedBuffer = NULL;
   mLockedSize = 0;
#endif
}

#endif
