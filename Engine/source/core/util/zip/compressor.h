// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "core/util/zip/centralDir.h"

#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

// Forward refs
class Stream;

namespace Zip
{

/// @addtogroup zipint_group
/// @ingroup zip_group
// @{

// [tom, 10/26/2006] Standard Zip compression methods
enum CompressionMethod
{
   Stored            = 0,
   Shrunk            = 1,
   ReducedL1         = 2,
   ReducedL2         = 3,
   ReducedL3         = 4,
   ReducedL4         = 5,
   Imploded          = 6,
   ReservedTokenized = 7,
   Deflated          = 8,
   EnhDefalted       = 9,
   DateCompression   = 10,
   ReservedPKWARE    = 11,
   BZip2             = 12,
   PPMd              = 98,
   AESEncrypted      = 99,    // WinZip's AES Encrypted zips use compression method 99
                              // to indicate AES encryption. The actual compression
                              // method is specified in the AES extra field.
};

class Compressor
{
   Compressor *mNext;

protected:
   const char *mName;         //!< The name of the compression method
   S32 mMethod;               //!< The compression method as in the Zip header

public:
   Compressor(S32 method, const char *name);
   virtual ~Compressor() {}

   inline const char * getName()                { return mName; }
   inline S32 getMethod()                       { return mMethod; }

   virtual Stream *createReadStream(const CentralDir *cdir, Stream *zipStream) = 0;
   virtual Stream *createWriteStream(const CentralDir *cdir, Stream *zipStream) = 0;

   // Run time lookup methods
   static Compressor *findCompressor(const char *name);
   static Compressor *findCompressor(S32 method);
};

#define ImplementCompressor(name, method)       \
   class Compressor##name : public Compressor   \
   {                                            \
   public:                                      \
      Compressor##name(S32 m, const char *n) : Compressor(m, n) {} \
      virtual Stream *createReadStream(const CentralDir *cdir, Stream *zipStream); \
      virtual Stream *createWriteStream(const CentralDir *cdir, Stream *zipStream); \
   };                                           \
   Compressor##name gCompressor##name##instance(method, #name);

#define  CompressorCreateReadStream(name) \
   Stream * Compressor##name::createReadStream(const CentralDir *cdir, Stream *zipStream)

#define  CompressorCreateWriteStream(name) \
   Stream * Compressor##name::createWriteStream(const CentralDir *cdir, Stream *zipStream)

// @}

} // end namespace Zip

#endif // _COMPRESSOR_H_
