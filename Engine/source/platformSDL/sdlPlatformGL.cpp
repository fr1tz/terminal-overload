#include <SDL.h>
#include "windowManager/sdl/sdlWindow.h"
#include "console/console.h"

namespace PlatformGL
{

   void* CreateContextGL( PlatformWindow *window )
   {
       PlatformWindowSDL* windowSdl = dynamic_cast<PlatformWindowSDL*>(window);
       AssertFatal(windowSdl, "");

       if( !windowSdl )
           return NULL;

       SDL_ClearError();
       SDL_GLContext ctx = SDL_GL_CreateContext( windowSdl->getSDLWindow() );
       if( !ctx )
       {
           const char *err = SDL_GetError();
           Con::printf( err );
           AssertFatal(0, err );
       }

       return ctx;
   }

   void MakeCurrentGL( PlatformWindow *window, void *glContext )
   {
       PlatformWindowSDL* windowSdl = dynamic_cast<PlatformWindowSDL*>(window);
       AssertFatal( windowSdl && glContext, "" );

       SDL_ClearError();
       SDL_GL_MakeCurrent( windowSdl->getSDLWindow(), glContext );

       const char *err = SDL_GetError();
       if( err && err[0] )
       {
           Con::printf( err );
           AssertFatal(0, err );
       }
   }

}
