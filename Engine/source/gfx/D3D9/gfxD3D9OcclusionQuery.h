// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFX_D3D9_OCCLUSIONQUERY_H_
#define _GFX_D3D9_OCCLUSIONQUERY_H_

#ifndef _GFXOCCLUSIONQUERY_H_
#include "gfx/gfxOcclusionQuery.h"
#endif

#ifdef TORQUE_GATHER_METRICS
   #ifndef _PLATFORM_PLATFORMTIMER_H_
   #include "platform/platformTimer.h"
   #endif
#endif

struct IDirect3DQuery9;


class GFXD3D9OcclusionQuery : public GFXOcclusionQuery
{
private:
   mutable IDirect3DQuery9 *mQuery;

#ifdef TORQUE_GATHER_METRICS
   U32 mBeginFrame;
   U32 mTimeSinceEnd;
   PlatformTimer *mTimer;
#endif

public:
   GFXD3D9OcclusionQuery( GFXDevice *device );
   virtual ~GFXD3D9OcclusionQuery();

   virtual bool begin();
   virtual void end();   
   virtual OcclusionQueryStatus getStatus( bool block, U32 *data = NULL );

   // GFXResource
   virtual void zombify();   
   virtual void resurrect();
   virtual const String describeSelf() const;
};

#endif // _GFX_D3D9_OCCLUSIONQUERY_H_