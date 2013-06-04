// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef SAFE_RELEASE
#  define SAFE_RELEASE(x) if( x != NULL ) { x->Release(); x = NULL; }
#endif