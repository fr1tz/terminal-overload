#include "gui/core/guiCanvas.h"
#include "console/engineAPI.h"
#include "gfx/gfxDebugEvent.h"

#include "gfx/D3D9/pc/gfxPCD3D9Device.h"
#include "gfx/D3D9/pc/gfxPCD3D9Target.h"
#include <d3d.h>

#include "gfx/gfxProfiler.h"

#ifndef TORQUE_BASIC_GPU_PROFILER
   //#define TORQUE_BASIC_GPU_PROFILER
#endif

class D3DTimer
{
public:      

   void begin()
   {
      mStart->Issue(D3DISSUE_END);
   }

   void end()
   {
      mEnd->Issue(D3DISSUE_END);
   }

   F64 getTime()
   {
      bool disjoint;
      U64 timeStart, timeEnd;

      while(S_FALSE == mData->disjointQuery->GetData( &disjoint, 
                                     sizeof(bool), D3DGETDATA_FLUSH )
                                     );

      if(disjoint)
         return false;

      U64 freq;

      while(S_FALSE == mData->frequencyQuery->GetData( &freq, 
                                     sizeof(U64), D3DGETDATA_FLUSH )
                                     );

      while(S_FALSE == mStart->GetData( &timeStart, 
                                 sizeof(U64), D3DGETDATA_FLUSH )
                                 );

      while(S_FALSE == mEnd->GetData( &timeEnd, 
                              sizeof(U64), D3DGETDATA_FLUSH )
                              );

      return static_cast<F64>(timeEnd - timeStart)/freq*1000;
   }

   

   class Data
   {
   public:
      IDirect3DQuery9* disjointQuery;
      IDirect3DQuery9* frequencyQuery;
      Data() : disjointQuery(NULL), frequencyQuery(NULL) {}

      void init()
      {

      }

      void onBeginFrame()
      {
         if(!frequencyQuery)
         {
            static_cast<GFXPCD3D9Device*>(GFX)->getDevice()->CreateQuery(D3DQUERYTYPE_TIMESTAMPDISJOINT, &disjointQuery);
            static_cast<GFXPCD3D9Device*>(GFX)->getDevice()->CreateQuery(D3DQUERYTYPE_TIMESTAMPFREQ, &frequencyQuery);
         }

         disjointQuery->Issue(D3DISSUE_BEGIN);
         frequencyQuery->Issue(D3DISSUE_END);
      }

      void onEndFrame()
      {
         disjointQuery->Issue(D3DISSUE_END);
      }
   };

   typedef Data DataType;

    D3DTimer(GFXDevice *device, Data &data) : mStart(NULL), mEnd(NULL), mData(&data)
   {
      IDirect3DDevice9 *d3d = static_cast<GFXPCD3D9Device*>(GFX)->getDevice();
      d3d->CreateQuery(D3DQUERYTYPE_TIMESTAMP, &mStart);
      d3d->CreateQuery(D3DQUERYTYPE_TIMESTAMP, &mEnd);
   }

    D3DTimer() : mStart(NULL), mEnd(NULL), mData(NULL)
    {

    }

    D3DTimer& operator=(const D3DTimer &b)
    {
       mStart = b.mStart;
       mEnd = b.mEnd;
       mData = b.mData;
       mName = b.mName;
       return *this;
    }

    StringTableEntry mName; 

protected:
   IDirect3DQuery9 *mStart, *mEnd;
   Data *mData;
   
};


GFXProfiler<D3DTimer> gfxProfiler;

DefineConsoleFunction(printGFXD3DTimers, void,(), ,"")
{
   gfxProfiler.printTimes();
}

bool initD3D9PCProfiler(GFXDevice::GFXDeviceEventType ev)
{
   if(ev != GFXDevice::GFXDeviceEventType::deInit || GFX->getAdapterType() != Direct3D9)        
      return true;

   Con::evaluatef("GlobalActionMap.bindCmd(keyboard, \"alt F4\", \"printGFXD3DTimers();\");");
   return true;
}

void GFXPCD3D9Device::enterDebugEvent(ColorI color, const char *_name)
{
   // BJGFIX
   WCHAR  eventName[260];
   MultiByteToWideChar( CP_ACP, 0, _name, -1, eventName, 260 );

   D3DPERF_BeginEvent(D3DCOLOR_ARGB(color.alpha, color.red, color.green, color.blue),
      (LPCWSTR)&eventName);

#ifdef TORQUE_BASIC_GPU_PROFILER
   gfxProfiler.enterDebugEvent(color, _name);
#endif
}

//------------------------------------------------------------------------------
void GFXPCD3D9Device::leaveDebugEvent()
{
   D3DPERF_EndEvent();

#ifdef TORQUE_BASIC_GPU_PROFILER
   gfxProfiler.leaveDebugEvent();
#endif
}

void GFXPCD3D9Device::setDebugMarker(ColorI color, const char *name)
{
   // BJGFIX
   WCHAR  eventName[260];
   MultiByteToWideChar( CP_ACP, 0, name, -1, eventName, 260 );

   D3DPERF_SetMarker(D3DCOLOR_ARGB(color.alpha, color.red, color.green, color.blue), 
      (LPCWSTR)&eventName);
}

#ifdef TORQUE_BASIC_GPU_PROFILER

AFTER_MODULE_INIT(Sim)
{
   // GFXGLDevice Profiler
   GuiCanvas::getGuiCanvasFrameSignal().notify(&gfxProfiler, &GFXProfiler<D3DTimer>::onEndFrame);
   GFXDevice::getDeviceEventSignal().notify( &initD3D9PCProfiler );   
}
#endif