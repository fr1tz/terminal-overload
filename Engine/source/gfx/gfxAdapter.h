// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _GFXADAPTER_H_
#define _GFXADAPTER_H_

#ifndef _GFXSTRUCTS_H_
#include "gfx/gfxStructs.h"
#endif

#ifndef _TVECTOR_H_
#include "core/util/tVector.h"
#endif

#ifndef _UTIL_DELEGATE_H_
#include "core/util/delegate.h"
#endif

struct GFXAdapter 
{
public:
   typedef Delegate<GFXDevice* (U32 adapterIndex)> CreateDeviceInstanceDelegate;     

   enum
   {
      MaxAdapterNameLen = 512,
   };

   char mName[MaxAdapterNameLen];

   /// The name of the display output device for the adapter, if any.
   /// For example under Windows, this could be: \\.\DISPLAY1
   char mOutputName[MaxAdapterNameLen];

   /// List of available full-screen modes. Windows can be any size,
   /// so we do not enumerate them here.
   Vector<GFXVideoMode> mAvailableModes;

   /// Supported shader model. 0.f means none supported.
   F32 mShaderModel;

   const char * getName() const { return mName; }
   const char * getOutputName() const { return mOutputName; }
   GFXAdapterType mType;
   U32            mIndex;
   CreateDeviceInstanceDelegate mCreateDeviceInstanceDelegate;

   GFXAdapter()
   {
      VECTOR_SET_ASSOCIATION( mAvailableModes );

      mName[0] = 0;
      mOutputName[0] = 0;
      mShaderModel = 0.f;
      mIndex = 0;
   }

   ~GFXAdapter()
   {
      mAvailableModes.clear();
   }
private:
   // Disallow copying to prevent mucking with our data above.
   GFXAdapter(const GFXAdapter&);
};

#endif // _GFXADAPTER_H_
