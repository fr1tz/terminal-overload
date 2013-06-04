// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#include "platform/types.h"
#include "platform/platformDlibrary.h"
#include <dlfcn.h>

class MacDLibrary : public DLibrary
{
   void* _handle;
public:
   MacDLibrary();
   ~MacDLibrary();
   bool open(const char* file);
   void close();
   void* bind(const char* name);
};

MacDLibrary::MacDLibrary()
{
   _handle = NULL;
}

MacDLibrary::~MacDLibrary()
{
   close();
}

bool MacDLibrary::open(const char* file)
{
   Platform::getExecutablePath();
   _handle = dlopen(file, RTLD_LAZY | RTLD_LOCAL);
   return _handle != NULL;
}

void* MacDLibrary::bind(const char* name)
{
   return _handle ? dlsym(_handle, name) : NULL;
}

void MacDLibrary::close()
{
   if(_handle)
      dlclose(_handle);
   
   _handle = NULL;
}

DLibraryRef OsLoadLibrary(const char* file)
{
   MacDLibrary* library = new MacDLibrary();
   if(!library->open(file))
   {
      delete library;
      return NULL;
   }
   
   return library;
}
