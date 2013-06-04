// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef BYTESWAP
#define BYTESWAP(x, y) x = x ^ y; y = x ^ y; x = x ^y;
#endif //defined(BYTESWAP)