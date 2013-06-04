// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _PNG_UTILS_H_
#define _PNG_UTILS_H_

#ifndef _GFXENUMS_H_
#include "gfx/gfxEnums.h"
#endif

struct DeferredPNGWriterData; // This is used to avoid including png.h in this header
class GBitmap;
class Stream;

/// This class is used to write PNGs in row batches
class DeferredPNGWriter {
protected:
   DeferredPNGWriterData *mData;
   bool mActive;

public:
   DeferredPNGWriter();
   ~DeferredPNGWriter();

   bool begin( GFXFormat format, S32 width, S32 height, Stream &stream, U32 compressionLevel );      
   void append( GBitmap* bitmap, U32 rows );
   void end();
};

#endif