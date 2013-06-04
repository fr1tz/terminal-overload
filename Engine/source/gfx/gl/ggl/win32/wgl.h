// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef GFX_WGL_H
#define GFX_WGL_H

#ifndef GFX_GGL_H
   #include "../ggl.h"
#endif
#ifndef _PLATFORMDLIBRARY_H
   #include "platform/platformDlibrary.h"
#endif

#ifndef _WIN32_WINNT
   #define _WIN32_WINNT 0x0500
#endif
#include <windows.h>


namespace GL
{

//-----------------------------------------------------------------------------
// Include WGL 1.0 definitions

#ifndef DOXYGEN
#include "../generated/wgle.h"


//-----------------------------------------------------------------------------
// All core functionality is implemented as function pointers.

#define GL_GROUP_BEGIN(name)
#define GL_FUNCTION(name, type, args) extern type (XGL_DLL *name) args;
#define GL_GROUP_END()
#include "../generated/wglfn.h"
#undef GL_GROUP_BEGIN
#undef GL_FUNCTION
#undef GL_GROUP_END


//-----------------------------------------------------------------------------
// Extensions use indirection in order to support multiple contexts

struct WGLExtensionPtrs: public GLExtensionPtrs {
   // Include all OpenGL extensions for all platform
   #define GL_GROUP_BEGIN(name)
   #define GL_FUNCTION(name, type, args) type (XGL_DLL *_##name) args;
   #define GL_GROUP_END()
   #include "../generated/wglefn.h"
   #undef GL_GROUP_BEGIN
   #undef GL_FUNCTION
   #undef GL_GROUP_END
};

struct WGLExtensionFlags: public GLExtensionFlags {
   // Define extension "has" variables
   #define GL_GROUP_BEGIN(name) bool has_##name;
   #define GL_FUNCTION(name, type, args)
   #define GL_GROUP_END()
   #include "../generated/wglefn.h"
   #undef GL_GROUP_BEGIN
   #undef GL_FUNCTION
   #undef GL_GROUP_END
};
#endif // Doyxygen


//-----------------------------------------------------------------------------

bool gglBindExtensions(DLibrary*,WGLExtensionPtrs*,WGLExtensionFlags*,HDC);

#undef XGL_FUNCPTR
#define XGL_FUNCPTR(name) (((GL::WGLExtensionPtrs*)GL::_GGLptr)->_##name)

#undef gglHasExtension
#define gglHasExtension(name) (((GL::WGLExtensionFlags*)GL::_GGLflag)->has_##name)


} // Namespace

#endif

