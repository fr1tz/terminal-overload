#ifndef PLATFORM_GL_H
#define PLATFORM_GL_H

class PlatformWindow;

namespace PlatformGL
{
   void* CreateContextGL( PlatformWindow *window );

   void MakeCurrentGL( PlatformWindow *window, void *glContext );
}

#endif //PLATFORM_GL_H
