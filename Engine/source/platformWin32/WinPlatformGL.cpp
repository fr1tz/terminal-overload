#if TORQUE_OPENGL

#include "platform/platformGL.h"
#include "gfx/gl/tGL/tWGL.h"

void PlatformGL::setVSync(const int i)
{
   wglSwapIntervalEXT( i );
}

#endif