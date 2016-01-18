// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _BASE64_H_
#define _BASE64_H_

#ifndef _TORQUE_STRING_H_
#include "core/util/str.h"
#endif

String base64_encode(U8* buf, size_t size);
size_t base64_decode(const char* encodedString, U8* decodedBuf);

#endif // _BASE64_H_ 
