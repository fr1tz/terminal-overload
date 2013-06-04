// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BITMAPUTILS_H_
#define _BITMAPUTILS_H_

#ifndef _TORQUE_TYPES_H_
#include "platform/types.h"
#endif

extern void (*bitmapExtrude5551)(const void *srcMip, void *mip, U32 height, U32 width);
extern void (*bitmapExtrudeRGB)(const void *srcMip, void *mip, U32 height, U32 width);
extern void (*bitmapExtrudeRGBA)(const void *srcMip, void *mip, U32 height, U32 width);
extern void (*bitmapConvertRGB_to_5551)(U8 *src, U32 pixels);
extern void (*bitmapConvertRGB_to_1555)(U8 *src, U32 pixels);
extern void (*bitmapConvertRGB_to_RGBX)( U8 **src, U32 pixels );
extern void (*bitmapConvertRGBX_to_RGB)( U8 **src, U32 pixels );
extern void (*bitmapConvertA8_to_RGBA)( U8 **src, U32 pixels );

void bitmapExtrudeRGB_c(const void *srcMip, void *mip, U32 height, U32 width);

#endif //_BITMAPUTILS_H_
