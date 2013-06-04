// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef GL_GGL_H
#define GL_GGL_H

#ifndef _MPOINT3_H_
#include "math/mPoint3.h"
#endif

//-----------------------------------------------------------------------------
// Configuration file which defines which parts of GL to include

#ifndef DOXYGEN
#include "gfx/gl/ggl/gglConfig.h"


//-----------------------------------------------------------------------------

#if defined(__CYGWIN__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32)
   #define XGL_DLL __stdcall
#else
   #define XGL_DLL
#endif


//-----------------------------------------------------------------------------
// Include core (OpenGL 1.1) definitions

#include "gfx/gl/ggl/generated/glc.h"
#include "gfx/gl/ggl/generated/gle.h"


//-----------------------------------------------------------------------------
// All core functionality is implemented as function pointers.

#define GL_GROUP_BEGIN(name)
#define GL_FUNCTION(name, type, args) extern type (XGL_DLL *name) args;
#define GL_GROUP_END()
#include "gfx/gl/ggl/generated/glcfn.h"
#undef GL_GROUP_BEGIN
#undef GL_FUNCTION
#undef GL_GROUP_END

/// OpenGL interface.
namespace GL
{

//-----------------------------------------------------------------------------
// Extensions use indirection in order to support multiple contexts

struct GLExtensionPtrs {
   bool bound;

   // Include all OpenGL extensions for all platform
   #define GL_GROUP_BEGIN(name)
   #define GL_FUNCTION(name, type, args) type (XGL_DLL *_##name) args;
   #define GL_GROUP_END()
   #include "gfx/gl/ggl/generated/glefn.h"
   #undef GL_GROUP_BEGIN
   #undef GL_FUNCTION
   #undef GL_GROUP_END

   GLExtensionPtrs() { bound = false; }
};

struct GLExtensionFlags {
   bool bound;

   // Define extension "has" variables
   #define GL_GROUP_BEGIN(name) bool has_##name;
   #define GL_FUNCTION(name, type, args)
   #define GL_GROUP_END()
   #include "gfx/gl/ggl/generated/glefn.h"
   #undef GL_GROUP_BEGIN
   #undef GL_FUNCTION
   #undef GL_GROUP_END

   GLExtensionFlags() { bound = false; }
};

// Extension loading has been reimplemented on each platform, and each platform
// has a different version of GLExtensionPtrs and GLExtensionFlags.  When binding
// extensions for that platform, you MUST use these pointers.  From there the XGL_FUNCPTR
// define will handle converting a gl*EXT call into the proper member function call.
extern GLExtensionPtrs* _GGLptr;
#define XGL_FUNCPTR(name) (GL::_GGLptr->_##name)
#endif // Doxygen

extern GLExtensionFlags* _GGLflag;
#define gglHasExtension(name) (GL::_GGLflag->has_##name)



} // Namespace

#endif

