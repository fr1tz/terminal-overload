// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include <err.h>
#include "agl.h"

#include "platform/platform.h"

//-----------------------------------------------------------------------------
// Instantiation of function pointers.

#define GL_GROUP_BEGIN(name)
#define GL_FUNCTION(name, type, args) type (XGL_DLL *name) args;
#define GL_GROUP_END()
#include "../generated/glcfn.h"
#undef GL_GROUP_BEGIN
#undef GL_FUNCTION
#undef GL_GROUP_END


#define EXECUTE_ONLY_ONCE() \
         static bool _doneOnce = false; \
         if(_doneOnce) return; \
         _doneOnce = true;

namespace GL
{

//-----------------------------------------------------------------------------
// The OpenGL Bundle is shared by all the devices.
static CFBundleRef   _openglFrameworkRef;

// Unlike WGL, AGL does not require a set of function pointers per
// context pixel format. All functions in the DLL are bound in a single
// table and shared by all contexts.
static AGLExtensionPtrs _LibraryFunctions;
static AGLExtensionFlags _ExtensionFlags;

bool hasExtension(const char *name,const char* extensions);
bool hasVersion(const char *name,const char* prefix,int major,int minor);


//-----------------------------------------------------------------------------
void* MacGetProcAddress(CFBundleRef bundle,char* name)
{
   CFStringRef cfName = CFStringCreateWithCString(kCFAllocatorDefault, name, CFStringGetSystemEncoding());
   void* ret = CFBundleGetFunctionPointerForName(bundle, cfName);
   CFRelease(cfName);
   return ret;
}


//-----------------------------------------------------------------------------
bool bindFunction(CFBundleRef bundle,void *&fnAddress, const char *name)
{
   CFStringRef cfName = CFStringCreateWithCString(0,name,CFStringGetSystemEncoding());
   fnAddress = CFBundleGetFunctionPointerForName(bundle, cfName);
   CFRelease(cfName);
   return fnAddress != 0;
}


//-----------------------------------------------------------------------------
bool gglBindCoreFunctions(CFBundleRef bundle,AGLExtensionPtrs* glp)
{
   bool bound = true;

   // Bind static functions which are quarenteed to be part of the
   // OpenGL library. In this case, OpenGL 1.0 and GLX 1.0 functions
   #define GL_GROUP_BEGIN(name)
   #define GL_GROUP_END()
   #define GL_FUNCTION(fn_name, fn_return, fn_args) \
         bound &= bindFunction(bundle,*(void**)&fn_name, #fn_name);
   #include "../generated/glcfn.h"
   #undef GL_FUNCTION
   #undef GL_GROUP_BEGIN
   #undef GL_GROUP_END

   // Try and bind all known extension functions. We'll check later to
   // see which ones are actually valid for a context.
   #define GL_GROUP_BEGIN(name)
   #define GL_FUNCTION(fn_name, fn_return, fn_args) \
            bindFunction(bundle,*(void**)&glp->_##fn_name, #fn_name);
   #define GL_GROUP_END()
   #include "../generated/glefn.h"
   #undef GL_FUNCTION
   #undef GL_GROUP_BEGIN
   #undef GL_GROUP_END

   return bound;
}


//-----------------------------------------------------------------------------
bool gglBindExtensions(GLExtensionFlags* gl)
{
   dMemset(gl,0,sizeof(GLExtensionFlags));

   // Get GL version and extensions
   const char* glExtensions = (const char*)glGetString(GL_EXTENSIONS);
   const char* glVersion = (const char*) glGetString(GL_VERSION);
   if (!glExtensions || !glVersion)
      return false;

   // Parse the GL version string "major.minor"
   const char *itr = glVersion;
   int glMajor = atoi(itr);
   while (isdigit(*itr))
      *itr++;
   int glMinor = atoi(++itr);

   // Check which extensions are available on the active context.
   // GL and GLX versions ubove 1.0 are also tested here.
   #define GL_GROUP_BEGIN(name) \
         gl->has_##name = hasVersion(#name,"GL_VERSION",glMajor,glMinor) || \
            hasExtension(#name,glExtensions);
   #define GL_FUNCTION(fn_name, fn_return, fn_args)
   #define GL_GROUP_END()
   #include "../generated/glefn.h"
   #undef GL_FUNCTION
   #undef GL_GROUP_BEGIN
   #undef GL_GROUP_END

   gl->bound = true;
   return true;
}

#define _hasGLXExtension(display,name) (display->glx.has_##name)

//-----------------------------------------------------------------------------
void gglPerformBinds()
{
   // Some of the following code is copied from the Apple Opengl Documentation.
  
   // Load and bind OpenGL bundle functions
   if (!_openglFrameworkRef) {
   
      // Load OpenGL.framework
      _openglFrameworkRef = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.opengl"));
      if (!_openglFrameworkRef) {
         warn("Could not create OpenGL Framework bundle");
         return;
      }
      if (!CFBundleLoadExecutable(_openglFrameworkRef)) {
         warn("Could not load MachO executable");
         return;
      }

      // Bind our functions.
      if (!gglBindCoreFunctions(_openglFrameworkRef, &_LibraryFunctions)) {
         warn("GLDevice: Failed to bind all core functions");
         return;
      }

      // Save the pointer to the set of opengl functions
      _GGLptr = &_LibraryFunctions;
   }
}

//-----------------------------------------------------------------------------
void gglPerformExtensionBinds(void *context)
{
   // we don't care about the passed context when binding the opengl functions,
   // we only care about the current opengl context.
	if( !_openglFrameworkRef || !_GGLptr )
	{
		gglPerformBinds();
	}
   gglBindExtensions(  &_ExtensionFlags );
   _GGLflag = &_ExtensionFlags;
}



} // Namespace

