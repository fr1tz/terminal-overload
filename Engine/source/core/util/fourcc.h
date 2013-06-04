// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef MakeFourCC
#define MakeFourCC(ch0, ch1, ch2, ch3)               \
   ((U32)(U8)(ch0) | ((U32)(U8)(ch1) << 8) |         \
   ((U32)(U8)(ch2) << 16) | ((U32)(U8)(ch3) << 24 ))
#endif //defined(MakeFourCC)
